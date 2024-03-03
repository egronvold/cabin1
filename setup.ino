void setup() {
  // put your setup code here, to run once:
delay(200);           // Allow for the receiver to power up and connect
Serial.begin(9600);   // Set the baud rate to 9600 for hardware serial

  // Code from the author of the library
  // Start the serial communication
#if !defined(UBRR1H)
  mySerial.begin(9600);  // Set the baud rate to 9600 for SoftwareSerial
  myMP3.begin(mySerial, true);
#else
  Serial1.begin(9600);  // Set the baud rate to 9600 for hardware serial
  myMP3.begin(Serial1, true);
#endif

  // Pin modes and write initial state of the mode
  // PWM and signal inputs
pinMode(pwmInputPinA, INPUT_PULLUP);  // Pin to read PWM signal A
pinMode(pwmInputPinB, INPUT_PULLUP);  // Pin to read PWM signal B
pinMode(busyPin, INPUT_PULLUP);       // Pin to read the state of the MP3-player
  // LED outputs
pinMode(ovenPin,OUTPUT);              
pinMode(insidePin1,OUTPUT);           
pinMode(insidePin2,OUTPUT);           
pinMode(outsidePin,OUTPUT);
  // Initial LED states
digitalWrite(ovenPin,LOW);
digitalWrite(insidePin1,LOW);
digitalWrite(insidePin2,LOW);
digitalWrite(outsidePin,LOW);

delay(100);   // Short delay to make sure MP3-player is ready

  // Initial state of the MP3-player
myMP3.volume(15);  // Set the volume to 15
myMP3.stop();      // Make sure no music is played

delay(100);   // Short delay to make sure MP3-player is ready

Serial.println("Ready to play"); // Serial print sayin the MP3-player has initialized and is ready

  // Calibration of input A nd B to make sure the PWM-rage is known to the Arduino
  // Outside LED is on to show the Arduino is ready for the calibration process. Blinking for each finished step
  // Calibrate input A low
  digitalWrite(outsidePin, HIGH);
  while (calibratedMinStartA == calibratedMinA){
  int pwmValue = pulseIn(pwmInputPinA, HIGH);
  calibratedMinA = min(calibratedMinStartA, pwmValue);
  Serial.print("Min setup A ");
  Serial.println(calibratedMinA);
  Serial.print("Max setup A ");
  Serial.println(calibratedMaxA);
  Serial.print("Current PWM value A ");
  Serial.println(pwmValue);
  delay(calDelay);
  }
  digitalWrite(outsidePin, LOW);
  delay(setupBlink);
  digitalWrite(outsidePin, HIGH);
  delay(setupBlink);
  digitalWrite(outsidePin, LOW);
  delay(setupBlink);
  digitalWrite(outsidePin, HIGH);
  delay(setupBlink);
  digitalWrite(outsidePin, HIGH);

  // Calibrate input A high
  while (calibratedMaxStartA == calibratedMaxA){
  int pwmValue = pulseIn(pwmInputPinA, HIGH);
  calibratedMaxA = max(calibratedMaxStartA, pwmValue);
  Serial.print("Min setup A ");
  Serial.println(calibratedMinA);
  Serial.print("Max setup A ");
  Serial.println(calibratedMaxA);
  Serial.print("Current PWM value A ");
  Serial.println(pwmValue);
  delay(calDelay);
  }
  digitalWrite(outsidePin, LOW);
  delay(setupBlink);
  digitalWrite(outsidePin, HIGH);
  delay(setupBlink);
  digitalWrite(outsidePin, LOW);
  delay(setupBlink);
  digitalWrite(outsidePin, HIGH);
  delay(setupBlink);
  digitalWrite(outsidePin, HIGH);

  // Calibrate input B low
  while (calibratedMinStartB == calibratedMinB){
  int pwmValue = pulseIn(pwmInputPinB, HIGH);
  calibratedMinB = min(calibratedMinStartB, pwmValue);
  Serial.print("Min setup B ");
  Serial.println(calibratedMinB);
  Serial.print("Max setup B ");
  Serial.println(calibratedMaxB);
  delay(calDelay);
  }
  digitalWrite(outsidePin, LOW);
  delay(setupBlink);
  digitalWrite(outsidePin, HIGH);
  delay(setupBlink);
  digitalWrite(outsidePin, LOW);
  delay(setupBlink);
  digitalWrite(outsidePin, HIGH);
  delay(setupBlink);
  digitalWrite(outsidePin, HIGH);
  // Calibrate input B high
  while (calibratedMaxStartB == calibratedMaxB){
  int pwmValue = pulseIn(pwmInputPinB, HIGH);
  calibratedMaxB = max(calibratedMaxStartB, pwmValue);
  Serial.print("Min setup B ");
  Serial.println(calibratedMinB);
  Serial.print("Max setup B ");
  Serial.println(calibratedMaxB);
  delay(calDelay);
  }
  digitalWrite(outsidePin, LOW);
  //Blink to indicate calibration is complete
  for (int i = 0; i <= 3; ++i){
    digitalWrite(insidePin1, HIGH);
    digitalWrite(insidePin2, HIGH);
    delay(setupBlink);
    digitalWrite(insidePin1, LOW);
    digitalWrite(insidePin2, LOW);
    delay(setupBlink);
  }

}