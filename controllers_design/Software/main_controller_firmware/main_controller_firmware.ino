#include <MIDIUSB.h>
#include <NeoPixelBrightnessBus.h>

const int muxSIG1 = 15;
const int muxSIG2 = 14;
const int muxSIG3 = 13;
const int muxSIG4 = 12;

uint32_t startTimer = millis();
constexpr uint32_t timeDiff = 10000;
int sendVolumeTimeFlag = 0;


int ports[]={15,14,10,16};

int volumecenters[]={454,511,460,460};
int volumelow[]={200,200,200,200};
int volumehigh[]={823,823,823,823};
int enabledvolumesensors[]={0,1,0,0};
int enabledbuttonsensors[]={1,1,1,1};
const int buttonValues[4];

const int muxS0 = 3;
const int muxS1 = 2;
const int muxS2 = 4;
const int muxS3 = 5;

int pedal=1;

bool debug=true;
int buttonState;
int pedals[64];
int volumepedals[4];
int j, i;
int ledPin=6;
const uint16_t PixelCount = 64;
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

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}

void processKey(int notenumber, int keystate) {
   //notenumber=31-notenumber; //this code is for pedals
   //int note = 0x18 + notenumber;  //This code is for pedals
   int note=0x0 + notenumber;
   if (keystate == 0 && pedals[notenumber]==0) {
       Serial.println("notenumber");
       Serial.println(notenumber);
    MidiUSB.sendMIDI({0x09, 0x90 | midiCh , note, 127});
    //strip.SetPixelColor(15-(notenumber/2), RgbColor(255, 0,0));
    //strip.Show();
    pedals[notenumber]=1;}
  else if (keystate == 1 && pedals[notenumber]==1) {
    MidiUSB.sendMIDI({0x09, 0x90 | midiCh , note, 1});
    pedals[notenumber]=0;
    //strip.SetPixelColor(15-(notenumber/2), RgbColor(0, 0,0));
    //strip.Show();
    }
    MidiUSB.flush();

}

void processVolume(int sensor, int volumeread) {
   //notenumber=31-notenumber; //this code is for pedals
   //int note = 0x18 + notenumber;  //This code is for pedals
   int cc=0x0 + sensor;

   int newvalue = (abs(0.0000040 *(volumehigh[sensor]-volumeread) *(volumehigh[sensor]-volumeread) * (volumehigh[sensor]-volumeread)));
   if (newvalue < 0 ) {newvalue = 0;}
   if (newvalue > 127 ) {newvalue = 127;}
   

   if ((millis() - startTimer) > timeDiff){
     sendVolumeTimeFlag = 1;
     startTimer=millis();
     Serial.println(F("AAAAAAAAAAAAAAAAAAAAAAAAAA"));
   }


   if ( ((abs(volumeread -volumepedals[sensor])>5) && (enabledvolumesensors[sensor]==1)) ||   sendVolumeTimeFlag == 1 ) {
       controlChange(0, cc, newvalue);
       volumepedals[sensor]=volumeread;
       MidiUSB.flush();
       if (sendVolumeTimeFlag == 1 ) {sendVolumeTimeFlag=0;}
       }
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

  for ( i =0; i<4; i++)
  {
    volumepedals[i] = 0;
  }
  strip.Begin();
  strip.Show();

 for ( int a =0; a<PixelCount; a++)
  {
  strip.SetPixelColor(a, RgbColor(255, 208, 23));
  strip.Show();
  delay(200);
  }
}

void checkKeys(){
   int note;
   for (int channel=0;channel < 4;channel++){
     if (enabledbuttonsensors[channel]==0){break;}
     Serial.println(channel);
     for (byte i = 0; i < 16; i++)
     {
        SetMuxChannel(i);
        int currentValue = digitalRead(ports[channel]);
        Serial.print(i);
        Serial.print(":");
        Serial.print(currentValue);
        Serial.print("\t");
        processKey(channel*16+i , currentValue);  
     }
      Serial.print("\n");

   }
    Serial.println();
    delay(10);
  }

void checkVolumes(){
   int note;
   int initial_sensor_pin=18;
   for (int sensor_pin=0;sensor_pin < 4;sensor_pin++){
        int currentValue  = analogRead(initial_sensor_pin+sensor_pin);

        processVolume(sensor_pin , currentValue);
        Serial.print("sensor_pin:");
        Serial.print(sensor_pin);
        Serial.print("Value:");
        Serial.print(currentValue);  
        Serial.println();
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
  checkVolumes();
}
