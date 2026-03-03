/* This is the current code (V2) for the Pocket Dice
 * Dieu de l'Elec - C. GAILLARD
 * 03.03.2026
 */ 

#include <avr/sleep.h>
#include <avr/interrupt.h>

#define BUTTON PIN_PB2

unsigned long timeCapture = 0;
volatile unsigned long timeIntCapture = 0;

byte prevDice = 0;
byte outcome = 1;
byte randomOutcome = 1;

int counterInt = 0;
volatile unsigned long counterIntTime = 0;

bool stateBtn = false;
volatile bool intAttribute = 1;       // interrupt attribute : 0 => button released (roll), 1 => button pressed (wake up)
// useful to know wether the intterupt means 'button pressed' or 'button released'

uint8_t LEDPins [7] {PIN_PA3, PIN_PA4, PIN_PA5, PIN_PC1, PIN_PB1, PIN_PB0, PIN_PC0};
uint8_t floatingPins [9] {PIN_PA2, PIN_PA6, PIN_PA7, PIN_PB5, PIN_PB4, PIN_PA1, PIN_PC3, PIN_PC2, PIN_PB3};
bool stateLED [7] {0, 0, 0, 0, 0, 0, 0};

void setup() {

  //delay (25000);
  //pinMode (PIN_PA0, OUTPUT
  pinMode(BUTTON, INPUT);

  for (int p = 0; p <= 6; p++) {
    pinMode (LEDPins[p], OUTPUT);
  }

  sei();
  PORTB.PIN2CTRL = PORT_ISC_RISING_gc;
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  timeCapture = millis();
}

void loop() {
  PORTB.PIN2CTRL = PORT_ISC_RISING_gc;

  if (intAttribute == 1) {             //                   // MCU woke up, but the button is still pressed
    randomOutcome = random(1, 7);      //                   // generate a dice outcome (rolling the dice)
    while (outcome == randomOutcome) { //                   // generate another one if it's the same outcome (just like a real dice that keeps rolling)
      randomOutcome = random(1, 7);    //
    }                                  //
    outcome = randomOutcome;           // just randomly rolling the dice for fun while the button hasn't been released
    displayDice(outcome);              //
    refreshDisplay (120);              //

    if (digitalRead (BUTTON) == 0) {
      counterIntTime = 0;
    }

    if ((millis () - counterIntTime >= 500) & (counterIntTime != 0)) {
      intAttribute = 0;
    }

  }
  if (intAttribute == 0) {                                   // if interrupt has been flagged (button released)
    PORTB.PIN2CTRL = PORT_ISC_INTDISABLE_gc;                 // disabling interrupts so it don't disturb

    unsigned long bufferTimeCapture = timeIntCapture;
    unsigned long duration = millis () - bufferTimeCapture; //bufferTimeCapture - timeCapture;
    //timeCapture = timeIntCapture;
    if (duration <= 800) {             // if short press => display previous outcome
      displayPrev();
      MCUSleep();
      return;
    }
    else {
      prevDice = generateOutcome(duration, micros());
      
      randomOutcome = random(1, 7);      //                   // generate a dice outcome (rolling the dice)
      while (outcome == randomOutcome) { //                   // generate another one if it's the same outcome (just like a real dice that keeps rolling)
        randomOutcome = random(1, 7);    //         Just dummy rolls to look more like a dice, slowing down
      }                                  //
      outcome = randomOutcome;           // just randomly rolling the dice for fun while the button hasn't been released
      displayDice(outcome);              //
      refreshDisplay (260);              //

      randomOutcome = random(1, 7);      //                   // generate a dice outcome (rolling the dice)
      while (outcome == randomOutcome) { //                   // generate another one if it's the same outcome (just like a real dice that keeps rolling)
        randomOutcome = random(1, 7);    //
      }                                  //
      outcome = randomOutcome;           // just randomly rolling the dice for fun while the button hasn't been released
      displayDice(outcome);              //
      refreshDisplay (400);              //         Just dummy rolls to look more like a dice, slowing down

      displayDiceOutcome(prevDice);
      MCUSleep();
      return;
    }
  }
}

void MCUSleep()  {
  PORTB.PIN2CTRL = PORT_ISC_INTDISABLE_gc;                 // disabling interrupts so it don't disturb
  for (int p = 0; p <= 6; p++) {          // LED GPIOs OFF
    digitalWrite (LEDPins[p], LOW);//pinMode (LEDPins[p], INPUT);
  }
  for (int p = 0; p <= 8; p++) {          // LED GPIOs OFF
    pinMode (floatingPins[p], OUTPUT); //INPUT?
  }

  ADC0.CTRLA &= ~ADC_ENABLE_bm;
  PORTA.PIN2CTRL = PORT_ISC_INTDISABLE_gc;//{PIN_PA2, PIN_PA6, PIN_PA7, PIN_PB5, PIN_PB4, PIN_PA1, PIN_PC3, PIN_PC2, PIN_PB3};
  PORTA.PIN6CTRL = PORT_ISC_INTDISABLE_gc;
  PORTA.PIN7CTRL = PORT_ISC_INTDISABLE_gc;
  PORTB.PIN5CTRL = PORT_ISC_INTDISABLE_gc;
  PORTB.PIN4CTRL = PORT_ISC_INTDISABLE_gc;
  PORTA.PIN1CTRL = PORT_ISC_INTDISABLE_gc;
  PORTC.PIN3CTRL = PORT_ISC_INTDISABLE_gc;
  PORTC.PIN2CTRL = PORT_ISC_INTDISABLE_gc;
  PORTB.PIN3CTRL = PORT_ISC_INTDISABLE_gc;

  PORTB.PIN2CTRL = PORT_ISC_FALLING_gc;     // | re-enabling Button interrupt
  PORTB.INTFLAGS = PIN2_bm;                 // |
  sleep_enable();
  sei();
  sleep_cpu();
  for (int p = 0; p <= 6; p++) {          // LED GPIOs OFF
    pinMode (LEDPins[p], OUTPUT); //digitalWrite (LEDPins[p], LOW);
  }

  ADC0.CTRLA |= ADC_ENABLE_bm;
  sleep_disable();
}

ISR (PORTB_PORT_vect) {
  PORTB.INTFLAGS = PIN2_bm;
  if (digitalRead (BUTTON) == 0) {    // interrupt when button pressed (wake up)
    timeIntCapture = millis();
    intAttribute = 1;
  }
  else {                              // interrupt when button released (roll dice)
    //intAttribute = 0;
    counterIntTime = millis();
  }
}

void displayPrev() {
  for (int i = 0; i < 4; i++) {
    displayDice (prevDice);                     // display previous outcome
    refreshDisplay(600);                        //    for 4 seconds total
    displayDice (0);                     // display previous outcome
    refreshDisplay(400);
  }
}

byte generateOutcome(unsigned long bcSeed, unsigned long prSeed) {
  setSeed(bcSeed, prSeed);
  byte value = roll_die();
  return value;

}

void displayDiceOutcome(byte diceValue) {
  displayDice (diceValue);                    // display outcome
  refreshDisplay(4000);                       //    for 4 seconds
}

void displayDice (int value) {
  switch (value) {
    case 0 :
      stateLED [0] = 0;
      stateLED [1] = 0;
      stateLED [2] = 0;
      stateLED [3] = 0;
      stateLED [4] = 0;
      stateLED [5] = 0;
      stateLED [6] = 0;
      break;
    case 1 :
      stateLED [0] = 0;
      stateLED [1] = 0;
      stateLED [2] = 0;
      stateLED [3] = 1;
      stateLED [4] = 0;
      stateLED [5] = 0;
      stateLED [6] = 0;
      break;
    case 2 :
      stateLED [0] = 0;
      stateLED [1] = 0;
      stateLED [2] = 1;
      stateLED [3] = 0;
      stateLED [4] = 0;
      stateLED [5] = 0;
      stateLED [6] = 1;
      break;
    case 3 :
      stateLED [0] = 0;
      stateLED [1] = 0;
      stateLED [2] = 1;
      stateLED [3] = 1;
      stateLED [4] = 0;
      stateLED [5] = 0;
      stateLED [6] = 1;
      break;
    case 4 :
      stateLED [0] = 1;
      stateLED [1] = 0;
      stateLED [2] = 1;
      stateLED [3] = 0;
      stateLED [4] = 1;
      stateLED [5] = 0;
      stateLED [6] = 1;
      break;
    case 5 :
      stateLED [0] = 1;
      stateLED [1] = 0;
      stateLED [2] = 1;
      stateLED [3] = 1;
      stateLED [4] = 1;
      stateLED [5] = 0;
      stateLED [6] = 1;
      break;
    case 6 :
      stateLED [0] = 1;
      stateLED [1] = 1;
      stateLED [2] = 1;
      stateLED [3] = 0;
      stateLED [4] = 1;
      stateLED [5] = 1;
      stateLED [6] = 1;
      break;
  }
}


void refreshDisplay (unsigned long duration) {
  unsigned long startTime = millis();
  while (millis() - startTime <= duration) {
    digitalWrite (LEDPins [0], stateLED[0]);
    delayMicroseconds (10);
    for (int l = 0; l <= 6; l++) {
      int n = (l + 1) % 7;
      digitalWrite (LEDPins [l], stateLED[l]);
      digitalWrite (LEDPins [n], stateLED[n]);
      delayMicroseconds (10);
      digitalWrite (LEDPins [l], 0);
    }
    digitalWrite (LEDPins [6], 0);
  }
}

/*************** Xoshiro128+ TRNG algorithm ***************/

void setSeed (unsigned long bcSeed, unsigned long prSeed) {
  uint32_t seed = bcSeed ^ micros() ^ prSeed ^ analogRead(2);       // adding entropy: floating analog pin reading, press duration, and micros()
  for (int i = 0; i < 4; i++) {
    seed ^= prSeed << (i * 8);
    seed ^= bcSeed;
  }
  xoshiro_seed(seed);
}

uint32_t s[4];
static inline uint32_t rotl(const uint32_t x, int k) {
  return (x << k) | (x >> (32 - k));
}

uint32_t xoshiro128plus() {
  uint32_t result = s[0] + s[3];
  uint32_t t = s[1] << 9;

  s[2] ^= s[0];
  s[3] ^= s[1];
  s[1] ^= s[2];
  s[0] ^= s[3];

  s[2] ^= t;
  s[3] = rotl(s[3], 11);
  return result;
}

void xoshiro_seed(uint32_t seed) {
  uint64_t z = seed + 0x9E3779B97F4A7C15ULL;
  for (int i = 0; i < 4; i++) {
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
    z = z ^ (z >> 31);
    s[i] = (uint32_t)z;
  }
}

// Roll a fair 1-6 using rejection sampling to avoid bias
int roll_die() {
  uint32_t r;
  do {
    r = xoshiro128plus() & 0xFFFFFFFFUL;  // use full 32 bits
  } while (r >= 0xFFFFFFFFUL - (0xFFFFFFFFUL % 6));
  return (r % 6) + 1;
}

/***************           * * *            ***************/
