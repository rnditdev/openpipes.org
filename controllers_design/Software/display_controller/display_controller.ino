/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/tca9548a-i2c-multiplexer-esp32-esp8266-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MIDIUSB.h>

#define i2c_Address1 0x3C
#define i2c_Address2 0x3C
const byte sysexStart = 0xF0;
const byte sysexEnd = 0xF7;
const byte manufacturerId = 0x7D;
const byte messageType = 0x01;

byte data[39];
int index = 0;
bool isReadingSysex = false;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, 32 , &Wire, -1);



// Select I2C BUS
void TCA9548A(uint8_t bus, int address){
  Wire.beginTransmission(0x70 + address);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}


 
void setup() {
  Serial.begin(9600);
  for (int i=0; i<8;i++){
  for (int j=0; j<8;j++){
  TCA9548A(i, j);
  if(!display.begin(SSD1306_SWITCHCAPVCC, i2c_Address2)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.drawPixel(10, 5*i, SSD1306_WHITE);
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(10, 10);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.println(i);
  display.setCursor(10, 20);
  display.println(j);
  display.display();
}
}
}

void displaySysexMessage() {
  byte panelIdLSB = data[3];
  byte panelIdMSB = data[4];
  byte colorCode = data[5];
  char text[33];
  memcpy(text, &data[6], 32);
  text[32] = '\0';

  Serial.print("Panel ID: ");
  Serial.print(panelIdMSB);
  Serial.print(", Color code: ");
  Serial.print(colorCode);
  Serial.print(", Text: ");
  Serial.println(text);

for (int i=0; i<8;i++){
if ((panelIdMSB < i * 8) &&  (panelIdMSB < (i+1) * 8))   {
  TCA9548A(panelIdMSB, i);
  display.clearDisplay();

  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.println(text);
  display.display();
}}
}
 
void loop() {
  midiEventPacket_t rx = MidiUSB.read();
  if (rx.header != 0) {
    if (rx.byte1 == sysexStart && rx.byte2 == manufacturerId && rx.byte3 == messageType) {
      index = 3;
      data[0] = rx.byte1;
      data[1] = rx.byte2;
      data[2] = rx.byte3;
      isReadingSysex = true;
    } else if (isReadingSysex) {
      data[index++] = rx.byte1;
      if (index < 39) data[index++] = rx.byte2;
      if (index < 39) data[index++] = rx.byte3;
      
      if (rx.byte1 == sysexEnd || rx.byte2 == sysexEnd || rx.byte3 == sysexEnd) {
        displaySysexMessage();
        isReadingSysex = false;
      }
    }
  }
}