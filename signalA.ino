void countSignalOverThreshold() {
  
  // Used for counting signal A over the threshold = select light mode
  
  if (signalRangeA > 0.9 * signalRangeMax && millis() - lastCountTime > yourCountInterval) {
    aboveThresholdCount++;
    lastCountTime = millis();
    Serial.print("aboveThresholdCount ");
    Serial.println(aboveThresholdCount);
    if (aboveThresholdCount > numModes) { 
      aboveThresholdCount = 0;
    }
  }
}

void countSignalUnderThreshold() {
  
  // Used for counting signal A under the threshold = execute toggle swhich
  
  if (signalRangeA < 0.1 * signalRangeMax && millis() - lastCountTime > yourCountInterval) {
    belowThresholdCount++;
    lastCountTime = millis();
    Serial.print("belowThresholdCount ");
    Serial.println(belowThresholdCount);
  }
}