#include <MIDIUSB.h>
#include <NeoPixelBrightnessBus.h>

const int muxSIG1 = 15;
const int muxSIG2 = 14;
const int muxSIG3 = 13;
const int muxSIG4 = 12;

int ports[]={15,14,16,10};

const int buttonValues[4];

const int muxS0 = 3;
const int muxS1 = 2;
const int muxS2 = 4;
const int muxS3 = 5;

int pedal=1;

bool debug=true;
int buttonState;
int pedals[64];
int j, i;
int ledPin=6;
const uint16_t PixelCount = 32;
const uint8_t PixelPin = 6;
int ledBrightness=50;
int midiCh=1;
const uint8_t noteLedMap[]   = {6, 7, 5, 8, 4, 3, 10, 2, 11, 1, 12, 0};

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

 
int SetMuxChannel(byte channel)
{
   digitalWrite(muxS0, bitRead(channel, 0));
   digitalWrite(muxS1, bitRead(channel, 1));
   digitalWrite(muxS2, bitRead(channel, 2));
   digitalWrite(muxS3, bitRead(channel, 3));
}

void noteOn(int cmd, int pitch, int velocity) {
  Serial1.write(cmd);
  Serial1.write(pitch);
  Serial1.write(velocity);
}

void processKey(int notenumber, int keystate) {
   //notenumber=31-notenumber; //this code is for pedals
   //int note = 0x18 + notenumber;  //This code is for pedals
   int note=0x0 + notenumber;
   if (keystate == 0 && pedals[notenumber]==0) {
       Serial.println(notenumber);
    MidiUSB.sendMIDI({0x09, 0x90 | midiCh , note, 127});
    //strip.SetPixelColor(15-(notenumber/2), RgbColor(255, 0,0));
    //strip.Show();
    pedals[notenumber]=1;}
  else if (keystate == 1 && pedals[notenumber]==1) {
    MidiUSB.sendMIDI({0x09, 0x90 | midiCh , note, 0});
    pedals[notenumber]=0;
    //strip.SetPixelColor(15-(notenumber/2), RgbColor(0, 0,0));
    //strip.Show();
    }
    MidiUSB.flush();

}


void setup()
{
  if (debug == true) {
    Serial.begin(115200);
    Serial.println(F("Serial debug enabled:"));
  }

   pinMode(muxS0, OUTPUT);
   pinMode(muxS1, OUTPUT);
   pinMode(muxS2, OUTPUT);
   pinMode(muxS3, OUTPUT);
   digitalWrite(muxS0, HIGH);
   digitalWrite(muxS1, HIGH);
   digitalWrite(muxS2, HIGH);
   digitalWrite(muxS3, HIGH);
   pinMode(muxSIG1, INPUT_PULLUP);
   pinMode(muxSIG2, INPUT_PULLUP);
   pinMode(muxSIG3, INPUT_PULLUP);
   pinMode(muxSIG4, INPUT_PULLUP);


  for ( i =0; i<64; i++)
  {
    pedals[i] = 0;
  }

  strip.Begin();
  strip.Show();

 for ( int a =0; a<32; a++)
  {
 
  strip.SetPixelColor(a, RgbColor(127, 127, 127));
  strip.Show();
  delay(100);
  }
}

void checkKeys(){
   int note;
   for (int channel=0;channel < 4;channel++){
     for (byte i = 0; i < 16; i++)
     {
        SetMuxChannel(i);
        int currentValue = digitalRead(ports[channel]);
        Serial.print(currentValue);
        Serial.print("\t");
        processKey(channel*16+i , currentValue);
        
     }

      Serial.print("\n");

   }
    Serial.println();
  }


void checkMidi() {
  midiEventPacket_t rx;
  do {
    rx = MidiUSB.read();
    if (rx.header != 0) {
      if (rx.byte1 == (0x90 | midiCh)) {            // tone on
        strip.SetPixelColor(int(rx.byte2), RgbColor(200, 200, 26));     // replace 0 with 4 if using sunvox MIDI echo...
        strip.Show();
        Serial.print(F("note off: "));
      } else if (rx.byte1 == (0x80 | midiCh)) {     // tone off
        strip.SetPixelColor(int(rx.byte2), RgbColor(49, 13, 117));   // replace 0 with 4 if using sunvox MIDI echo...
        strip.Show();
        Serial.print(F("note on: "));
      }
      if (true) {
        Serial.print(F("Received: "));
        Serial.print(rx.header, HEX);
        Serial.print("-");
        Serial.print(rx.byte1, HEX);
        Serial.print("-");
        Serial.print(rx.byte2, HEX);
        Serial.print("-");
        Serial.print(int(rx.byte2));
        Serial.print("-");
        Serial.println(rx.byte3, HEX);
      }
    }
  } while (rx.header != 0);
}


void loop() {
  checkKeys();
  checkMidi(); 
}
