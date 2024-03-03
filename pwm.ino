void readAndCalibratePWM(int pwmInputPin, int& calibratedMin, int& calibratedMax) {
  
  // Used for calibrating min and max while using the sketch
  
  int pwmValue = pulseIn(pwmInputPin, HIGH);
  calibratedMin = min(calibratedMin, pwmValue);
  calibratedMax = max(calibratedMax, pwmValue);
}