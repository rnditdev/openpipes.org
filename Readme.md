
![](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.001.png)


[**General Component Overview](#_jtclcdmnchy8)	**3**

[2 manual simple model](#_wvbw1qwb1oyi)	3

[**1.Cabinet](#_lmenqbukjjc5)	**4**

[2 manual simple model](#_xbyco7qo22da)	4

[1.1 Furniture boards](#_cyn0idyl5w5u)	4

[1.2 Kreg screws](#_1y62zlyjxjxu)	4

[1.3 Corner support](#_8poi4ixyvzm6)	4

[1.4 Base Foots](#_4weh9eut1fzo)	4

[1.4 Pedal Mechanisms](#_ojpr9ibqjbic)	4

[1.5 AC connection module](#_c8wng7psjurv)	4

[**2. Sound Generator](#_cszie4lpwn5o)	**5**

[2.1 Main Architecture options](#_oeml7gp5xn57)	5

[Raspberry Pi](#_wmru4rcdttia)	5

[X86 standard mainboards](#_4xq9ejntr71w)	5

[Orange Pi](#_6r40cessumr8)	5

[2.2 Sound output](#_vm0e8oeutw6j)	5

[USB DAC](#_hy7giobmbvy3)	5

[**3. External Sound System](#_fv2nrk7j9xa2)	**7**

[**4. Power Source](#_z04cl4ad4geh)	**8**

[**5. Operation Peripherals](#_u3cfc72ei66q)	**9**

[MIDI Controller board](#_m7de142v6pz4)	10

[Extension board 1](#_vcoyk94imxj8)	13

[Double array button board](#_3hgbb09f9544)	16



# General Component Overview
## 2 manual simple model
![](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.002.png)
# 1.Cabinet
## 2 manual simple model
![](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.003.png)
### 1.1 Furniture boards
### 1.2 Kreg screws
### 1.3 Corner support
### 1.4 Base Foots
### 1.4 Pedal Mechanisms
### 1.5 AC connection module
# 2. Sound Generator
## 2.1 Main Architecture options
### 2.1.1Raspberry Pi
![](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.004.png)

(Recommeded 4GB/8GB)

![](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.005.png)
### 2.1.2 X86 standard mainboards
### 2.1.2 Orange Pi
## 2.2 Sound output
### USB DAC
Pcm2704



![](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.006.png)

![](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.007.png)
# 3. External Sound System
![](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.008.png)
# 4. Power Source
![](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.009.png)

# 5. Operation Peripherals
![](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.010.png)


## MIDI Controller board
This PCB has the system controller, the MIDI transceiver circuit, and the ports to which the keys will be attached. The PCB was made to be 63mm x 60mm. the SMD switches was added to enable further daisy chain connection for the NeoPixels resulting in using less pins in controlling the LEDs, and that is optional because each port is connected to a dedicated pin that controls the NeoPixels. Analog Pins was pinned out for further usage.

![Graphical user interface Description automatically generated](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.011.png)

*Figure 1: 3D view of the MIDI controller board*


Controller Pinout

![](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.012.png)





The schematic illustrates more how things are connected to each other.

![Diagram, schematic Description automatically generated](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.013.png)

*Figure 2:MIDI Controller schematic capture.*

… And here is the final layout.

![Schematic Description automatically generated with low confidence](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.014.jpeg)

*Figure 3: MIDI controller PCB layout.*
##
## Extension board 1


![](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.015.jpeg)


![](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.016.jpeg)


This board has the multiplexer IC 74HC4067 that passes the state of the selected channel, connected to it 8 keys out of 16, also mounted to the board WS2812 Neopixel LEDs connected in a daisy chain manner. The board has the bridge pin header connector to attach the second extension board. The board has auxiliary pins for debugging the states.

![Graphical user interface Description automatically generated](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.017.png)

*Figure 4:3D view of the main extension board*

![Diagram, schematic Description automatically generated](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.018.png)

*Figure 5: Schematic capture for the main extension board.*

![A screenshot of a computer Description automatically generated with medium confidence](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.019.png)

*Figure 6: PCB layout for the main extension board.*

**Extension board 2**

This board has the other 8 keys and Neopixels with auxiliary pins. It’s connected to the main extension board through female header.

![Graphical user interface Description automatically generated](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.020.png)

*Figure 7: 3D view of the secondary extension board.*

![Diagram Description automatically generated](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.021.png)

*Figure 8: Schematic capture for the secondary extension board.*

![A screenshot of a computer Description automatically generated with low confidence](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.022.png)

*Figure 9: PCB layout of the secondary extension board.*
##
## Double array button board
This board has all 16 buttons on it connected to the multiplexer, with 8 NeoPixel LEDs connected in daisy chain, it also has a 10-pin IDC to be connected to the MIDI controller board. All channels were pinned out for debugging purposes.

![A picture containing text, electronics Description automatically generated](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.023.jpeg)

*Figure 10: 3D view of the double array button board.*

![Diagram, schematic Description automatically generated](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.024.png)

*Figure 11: Schematic capture of the double array button board.*

![A picture containing text, electronics Description automatically generated](Aspose.Words.3c323598-a867-410d-b564-bc64f0fbbe43.025.png)

*Figure 12: PCB layout of the double array button board.*

Links to open-source files and manufacturing files ...

MIDI controller:

Main Extension board:

Secondary Extension board:

Double array button board:


