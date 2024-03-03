void ovenFire(){

  /* Function to light or extinguish the oven fire.
  Function is also used as part of switch from oven fire to music */
  
  if (lightFire == true){
    myMP3.play(1);                              // Play the soundfile with the sound of oven fire
    myMP3.loop(1);                              // Loop the sound of the oven fire
    fire = true;
    if (currentMillis - fireLit >= fireWait){
      lightFire = false;
      digitalWrite(ovenPin,HIGH);
      Serial.println("Fire lit");
      //Serial.println(lightFire);
    }
  } else if (extinguishFire == true){
    myMP3.stop();
    lightFire = false;
    fire = false;
    extinguishFire = false;
    if (playMusic == true){
      digitalWrite(ovenPin,HIGH);
    } else {
      digitalWrite(ovenPin,LOW);
    }
    Serial.println("Fire extinguished");
  }
}