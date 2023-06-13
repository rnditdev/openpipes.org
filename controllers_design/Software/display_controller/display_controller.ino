/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/tca9548a-i2c-multiplexer-esp32-esp8266-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_SSD1306.h>
#include <MIDIUSB.h>

#define i2c_Address 0x3c

const byte sysexStart = 0xF0;
const byte sysexEnd = 0xF7;
const byte manufacturerId = 0x7D;
const byte messageType = 0x01;

byte data[39];
int index = 0;
bool isReadingSysex = false;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Select I2C BUS
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}
 
void setup() {
  Serial.begin(115200);
  delay(100);

  // Start I2C communication with the Multiplexer
  display.begin(i2c_Address, true);

  // Init OLED display on bus number 2
  TCA9548A(2);
  if(!display.begin(SSD1306_SWITCHCAPVCC, i2c_Address)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }


  //if(!display.begin(i2c_Address, true)) {
  //  Serial.println(F("SSD1306 allocation failed"));
  //  for(;;);
  //} 
  // Clear the buffer
  display.clearDisplay();

  // Init OLED display on bus number 3
  //TCA9548A(3);
  //if(!display.begin(i2c_Address, true)) {
//Serial.println(F("SSD1306 allocation failed"));
 //   for(;;);
 // } 

  // Write to OLED on bus number 2
TCA9548A(2);
display.clearDisplay();

  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SH110X_WHITE); // Draw white text
  display.setCursor(45, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  display.println("HW3");
  display.setTextSize(3);      // Normal 1:1 pixel scale
  display.setCursor(15, 20);     // Start at top-left corner
  display.println("Quint");
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setCursor(50, 50);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.println("4");
 

  

  display.display();

  // Write to OLED on bus number 3
  TCA9548A(3);
  display.clearDisplay();

  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SH110X_WHITE); // Draw white text
  display.setCursor(45, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  display.println("HW");




  display.setTextSize(3);      // Normal 1:1 pixel scale
  display.setTextColor(SH110X_WHITE); // Draw white text
  display.setCursor(0, 20);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  display.println("Bourdon");


  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SH110X_WHITE); // Draw white text
  display.setCursor(50, 50);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  display.println("8");
 

  display.display();
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

TCA9548A(panelIdMSB+2);
display.clearDisplay();

  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SH110X_WHITE); // Draw white text
  display.setCursor(0, 32);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  display.println(text);
  display.display();

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