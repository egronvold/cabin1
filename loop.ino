void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis(); // update the timer

  // Read and calibrate PWM for Input A
  readAndCalibratePWM(pwmInputPinA, calibratedMinA, calibratedMaxA);
    // Map the PWM value to the range 0-255 for Input A
    /* Due to an unknown hardware error which suddenly put the calibratedMinA outside range,
    an if statement were added to bring the signal back within range. */
        if (calibratedMinA < 900){
          calibratedMinA = 1000;
        }
    signalRangeA = map(pulseIn(pwmInputPinA, HIGH), calibratedMinA, calibratedMaxA, 0, signalRangeMax);
    signalRangeA = constrain(signalRangeA, 0, signalRangeMax);
    
  // Read and calibrate PWM for Input B
  readAndCalibratePWM(pwmInputPinB, calibratedMinB, calibratedMaxB);
    // Map the PWM value to the range 0-255 for Input B
    signalRangeB = map(pulseIn(pwmInputPinB, HIGH), calibratedMinB, calibratedMaxB, 0, volumeMax);
    signalRangeB = constrain(signalRangeB, 0, volumeMax);
    volume = signalRangeB;  // Setting the current volume using a potmeter on the radio
  
  // Functions run at a certain interval
  if (currentMillis - lastFunctionCheck >= functionCheckTime){
    lastFunctionCheck = currentMillis;

    // Read the status of the DFPlayer Mini
    busyStatus = digitalRead(busyPin);

    // Adjust the volume while the sketch is running
    myMP3.volume(volume);

    // Print to the serial monitor
    // Serial.print("pwmInputPinA ");
    // Serial.println(pulseIn(pwmInputPinA, HIGH));
    // // Serial.print("pwmInputPinB ");
    // // Serial.println(signalRangeB);
    // // Serial.print("busyStatus ");
    // // Serial.println(busyStatus);
    // Serial.print("calibratedMinA ");
    // Serial.println(calibratedMinA);
    // Serial.print("signalRangeA ");
    // Serial.println(signalRangeA);
  }
  
  // Check input signals for Input A
  countSignalOverThreshold();   // Read signal A to choose a case
  countSignalUnderThreshold();  // Read signal A to execute a case
  
  // Run functions
  handleLightModes(); // If a case/ mode is selected it's executed on this function
  ovenFire();         // Function to simulate oven fire
  music();            // Function to play music
  updateSong();       // Function to choose the next song to be played

}