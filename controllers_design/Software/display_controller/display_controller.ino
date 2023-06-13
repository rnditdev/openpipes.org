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

//Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1306 display(SCREEN_WIDTH, 32 , &Wire, -1);
Adafruit_SSD1306 display2(SCREEN_WIDTH, 32, &Wire, -1);


// Select I2C BUS
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}

void TCA9548A2(uint8_t bus){
  Wire.beginTransmission(0x71);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}

 
void setup() {
  Serial.begin(9600);

  for (int i=0; i<8;i++){
  TCA9548A2(i);
  if(!display2.begin(SSD1306_SWITCHCAPVCC, i2c_Address2)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display2.clearDisplay();
  display2.drawPixel(10, 5*i, SSD1306_WHITE);
  display2.setTextSize(1);      // Normal 1:1 pixel scale
  display2.setTextColor(SSD1306_WHITE); // Draw white text
  display2.setCursor(10, 10);     // Start at top-left corner
  display2.cp437(true);         // Use full 256 char 'Code Page 437' font

  display2.println("22");
  display2.setCursor(10, 20);
  display2.println(i);
  

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display2.display();
}
  


  delay(100);
  // Start I2C communication with the Multiplexer
  for (int i=0; i<8;i++){
  TCA9548A(i);
  if(!display.begin(SSD1306_SWITCHgrCAPVCC, i2c_Address1)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.drawPixel(10, 5*i, SSD1306_WHITE);
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(10, 10);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.println("11");
  display.setCursor(10, 20);
  display.println(i);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
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


if (panelIdMSB < 8){
TCA9548A(panelIdMSB);
display.clearDisplay();

  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SH110X_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  display.println(text);
  display.display();

}

else{
TCA9548A2(panelIdMSB-8);
display2.clearDisplay();

  display2.setTextSize(2);      // Normal 1:1 pixel scale
  display2.setTextColor(SH110X_WHITE); // Draw white text
  display2.setCursor(0, 0);     // Start at top-left corner
  display2.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  display2.println(text);
  display2.display();


}

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