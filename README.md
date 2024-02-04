This project aims to convert flex sensor installed on fingers signs Into binary values that will be
translated based on customized dictionary to strings that are pronounced by peripheral device. 

don't forget to change slave address in (LDCI2C_CFG.h).. in the prouteos simulation LCD adress was 0x020 
but for the physical LCD i used (PCF8574T-I2C-1602-16X2-LCD) address was 0x27
 
layers:

![Image Alt text](deaf_gloves/images/LAYERS.png)

activity diagram:

![Image Alt text](deaf_gloves/images/activity_diagram.jpg)

sequence diagram:

![Image Alt text](deaf_gloves/images/sequence_diagram.jpg)

this image represents the connections:

![Image Alt text](deaf_gloves/images/B1C5843y972AVTE0Re.pdf1.png)

FLEX SENSORS Are represented as resistors (they actually are.)
but one of them is a potentiometer so you can simulate 
how changing resistance change the behaviour 

DO NOT FORGET TO Invert RXD AND TXD Pins 
if you are using USB to TTL as in the simulation i'm connecting two ports
yet in real life you'll be using one port (usb to ttl) and the data recieved from 
TXD(usb) should go to pin RXD(micro_controller)
data sent through TXD(micro_controller) should go to pin RXD(usb)


the UART reviever python code:

![Image Alt text](deaf_gloves/Screenshot_(2083).png)


I will update more information on a PDF file that explains everything later (after the porject discussion)
so wish me luck
