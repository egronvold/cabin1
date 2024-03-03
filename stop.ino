void stopMusic(){
  
  // Function to stop the music and light the oven fire

  myMP3.stop();
  isPlaying = false;
  playMusic = false;
  lightFire = true;
  fireLit = currentMillis;
  Serial.println("Music stopped");
  
}