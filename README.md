# Pocket Dice
It's a dice, barely bigger than a coin cell (CR2016), based upon the ATtiny1616, with 7 orange 0603 LEDs . With the press duration being recorded, it should display a near truly random generated number, unlike pseudo random number generator algorithms.

This pocket-sized dice will be my everyday companions for tabletop games or any 6D dice requiring game.

<br><br>
<p align="center">
  <img alt="RENDER 1 Banner" src="https://github.com/user-attachments/assets/c211962b-5a39-4d98-9aed-3e9bfd04f616" width="44.65%" />
  <img alt="PCB Banner" src="https://github.com/user-attachments/assets/f0334381-cef0-48db-9a11-e1367e60ca51" width="44%"/>
</p>
<br><br>


# Key features:
- 7x 0603 LEDs (orange LEDs)
- extremely **low power consumption** (2mA average while displaying) ⇒ long battery life (CR2016), but dimmer LEDs... yet still visible enoough indoor
- **Attiny1616** MCU: 16Kb Flash, Power Down sleep, extraordinarily low current consumption (VDD = 3V: 300µA running @1MHz, and 100nA in PWR down mode)
- based on **Xoshiro128+** TRNG algorithm
- button **press duration recorded** ⇒ entropy source for TRNG (along with `micros()` and analog noise on floating pin)
- Sleek design: 7mm thick, 30mm by 30mm
- 3d printed enclosure: I used JLC3DP 3D printing service, with Nylon PA12 (MJF), to get a premium case, but it works too with an FDM printer or with SLA too
- 1mm acrylic sheet on top that can be pressed (a bit of flex) to press the button underneath
- MCU programmable via **UPDI**

# Sofware:
Arduino code using SpenceKonde **MegaTinyCore** and **Xoshiro128+** TRNG algorithm

# PCB design:
2 Layer PCB designed in EASYEDA (Pro edition). 26 by 26mm square, panelized in a 3 by 3 panel. 0.8mm board thickness

# Schematic:
<img src="Pocket_Dice_Schematic.svg" alt="SCHEMATIC" width="2300"/>

# PCB Layout:

<img alt="PCB Top Layer" src="https://github.com/user-attachments/assets/21bb0260-7778-49f2-8317-fd30a74fad34" width="100%"/>
<img alt="PCB PANEL Layout" src="https://github.com/user-attachments/assets/3d046bef-3495-4dda-8bc2-4fc819d615d8" width="100%"/>
<img alt="PCB PANEL back Layout" src="https://github.com/user-attachments/assets/b28681fd-c321-4540-99b9-98c6d601cf26" width="100%"/>
<img alt="PCB PANEL 2D" src="https://github.com/user-attachments/assets/8c2ca4d8-5f3e-4b8a-98cc-3154106c1b0b" width="100%"/>
<img alt="PCB PANEL 2D back" src="https://github.com/user-attachments/assets/52c39f66-4cc7-4cc6-8622-7f5b972c8a95" width="100%"/>

<img alt="PCB 3 back 3d" src="https://github.com/user-attachments/assets/c85e3643-dc89-4faa-bf1c-1ffddf6aa1b9"  width="100%"/>


# CAD and Renders:

<img alt="PCB 3d render 1" src="https://github.com/user-attachments/assets/bd2b6fee-571b-45f7-b478-f9f7d432a7fd"  width="100%"/>
<img alt="PCB 3d render 2" src="https://github.com/user-attachments/assets/1ca8c030-0904-4916-8a90-2e6822709fb4"  width="100%"/>
<img alt="PCB 3d render 3" src="https://github.com/user-attachments/assets/73231c73-6159-4820-947d-129cb9245e8c"  width="100%"/>

<img alt="RENDER 1" src="https://github.com/user-attachments/assets/59ce360c-36a7-4671-8f5d-8ea4d9bfc965"  width="100%"/>
<img alt="RENDER 2" src="https://github.com/user-attachments/assets/afa2c711-d2a6-49f9-ac99-8359f1a7261a"  width="100%"/>
<img alt="RENDER 3" src="https://github.com/user-attachments/assets/da772d6f-1569-43b1-b008-da5a0a6a6695"  width="100%"/>
<img alt="RENDER 4" src="https://github.com/user-attachments/assets/415eab99-a659-480f-a0b6-5c6b2d0502c1"  width="100%"/>
<img alt="RENDER 6" src="https://github.com/user-attachments/assets/c7d71b85-10a4-421b-8457-357ab919a68e"  width="100%"/>
<img alt="RENDER 5" src="https://github.com/user-attachments/assets/eb0606d3-132a-487c-a1c7-787f2973a8d3"  width="100%"/>

#BOM:

Qty	| Part	| Value | link
- | | |
1 | ATtiny1616-MNR | | https://www.lcsc.com/product-detail/C507118.html
1 | CR2016 Cell SMD metal holder | | https://www.lcsc.com/product-detail/C2979176.html
1 | MLCC 0805 | 10µF | https://www.lcsc.com/product-detail/C1713.html
1 | Tactile Switch TS-1075S-A1B2-D4 | | https://www.lcsc.com/product-detail/C492872.html
2 | MLCC 0603 | 100nF | https://www.lcsc.com/product-detail/C66501.html
1 | Resistor 0402| 200k | https://www.lcsc.com/product-detail/C2906866.html
7 | Resistor 0402| 1k | https://www.lcsc.com/product-detail/C2906864.html
7 | Orange LED 0603 XL-1608UOC-06 | Vf=2.3V | https://www.lcsc.com/product-detail/C965800.html
1	| Custom PCB | |
- | | |
1 | 1mm thick acrylic sheet | transparent |
1 | 3D printed case | MJF - PA12S-HP Nylon | 
1 | CR2016 Coin Cell | | 







