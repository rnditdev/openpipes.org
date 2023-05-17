#### Main controller software

The program starts with the setup, initializing the necessary variables and setting up the NeoPixel strip. Once the setup is complete, the program enters a loop where it checks the keys, processes MIDI events, and checks the volumes.

- In the "Check Keys" step, it sets the Mux channel and processes the key, which involves sending MIDI events.
- In the "Check MIDI" step, it receives MIDI events and updates the NeoPixel strip accordingly.
- In the "Check Volumes" step, it processes the volume, which involves sending control change MIDI events.

This loop continues indefinitely until the Arduino is reset or powered off.

<img src="https://showme.redstarplugin.com/s/aVHtosFr" title="" alt="Flowchart" data-align="center">
