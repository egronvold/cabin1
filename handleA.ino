void handleLightModes() {
  
  // Toggle switch for signal A
  
  if (belowThresholdCount == 1) {
    switch (aboveThresholdCount) {
      case 1:                                               // Turn the lights on or off
        if (!lightsOn){
          for (i = 2; i <= 4; ++i){
          digitalWrite(i,HIGH);
          lightsOn = true;
          Serial.println("Lights on");
          }
        } else if (lightsOn){
            for (i = 2; i <= 4; ++i){
            digitalWrite(i,LOW);
            lightsOn = false;
            Serial.println("Lights off");
            }
          }
        break;

      case 2:                                             // Light or extinguish the oven fire
        if (fire == false){
          //fire = true;
          lightFire = true;
          fireLit = currentMillis;
          Serial.println("Lighting the oven");
        } else if (fire == true){
          extinguishFire = true;
          Serial.println("Extingushing the oven fire");
        }
        break;
      
      case 3:                                               // Turn the music on or off
        if (fire == false && isPlaying == false) {          // If the fire is not lit, no music is turned on
          Serial.println("First light the oven fire");
        } else if (fire == true) {                          // If the fire is burning, turn on the music and turn on the oven LED
            extinguishFire = true;
            firstSong = true;
            playMusic = true;
            songNumber = 1;
            digitalWrite(ovenPin,HIGH);
            Serial.println("Music turned on");
        } else if (fire == false && isPlaying == true) {    // If the music is playing, stop the music
          stopMusic();
          // playMusic = false;
          // isPlaying = false;
          // stop = true;
          //lightFire = true;
          Serial.println("Music turned off and oven fire lit");
        }
        break;

      case 4:                                              // Turn off music and sounds
        extinguishFire = true;
        playMusic = false;
        isPlaying = false;
        //stopAll();
        myMP3.stop();
        Serial.println("Turn off sounds and music");
        break;
      
      case 5:
        
        break;

      case 6:
        
        break;
      
      case 7:
        
        break;

      // Add cases for other modes as needed

      default:
        // Do nothing or handle the default case
        break;
    }
    // Reset the counters
    aboveThresholdCount = 0;
    belowThresholdCount = 0;
  }
}