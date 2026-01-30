# Pocket-Dice
It's a dice, barely bigger than a coin cell (CR2016), based upon the ATtiny1616, with 7 orange 0603 LEDs . With the press duration being recorded, it should display a near truly random generated number, unlike pseudo random number generator algorithms.

# Key features:
- 7x 0603 LEDs (orange LEDs)
-  extremely **low power consumption** (max 4mA continuous goal) ⇒ long battery life (CR2016), but dim LEDs...
- **Attiny1616** MCU: 16Kb Flash, Power Down sleep, extraordinary current consumption (VDD = 3V : 300µA running @1MHz, and 100nA in PWR down mode)
- based on **Xoshiro128+** TRNG algorithm
- button **press duration recorded** ⇒ entropy source for TRNG (along with micros() and analog noise on floating pin)

- programmation of the MCU via **UPDI**

# Sofware:
Arduino code using SpenceKonde MegaTinyCore

# PCB design:
2 Layer PCB designed in EASYEDA (Pro edition). 26 by 26mm square, panelized in a 3 by 3 panel.
.8mm board thickness

# schematic:
