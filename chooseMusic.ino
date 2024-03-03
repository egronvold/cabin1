void music(){
  
  /* Function to turn on the music. Play song one
  in the MP3-folder when first triggered */
  
  if (playMusic == true && isPlaying == false){
    if (firstSong == true){
      myMP3.playFromMP3Folder(1);
    } else {
      myMP3.playFromMP3Folder(songNumber);
    }
    isPlaying = true;
    firstSong = false;
    lastCheck = currentMillis;
    Serial.print("songNumber ");
    Serial.println(songNumber);

  }
}