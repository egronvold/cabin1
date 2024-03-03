void updateSong(){

  /* Function to choose the next song if the time for checking has passed
  and the MP3-player is not playing (busyPin = HIGH). The two first files
  must be played in sequence. Then randomly choose the next one. 
  After all tracks are played, the music stops and the oven fires is lit.
  All tracks have the sound of the oven fire added to the background in
  the setup where this sketch is used */
  
  if(currentMillis - lastCheck >= playTime){                              // Check to see if it's time to change songs
    if (busyStatus == HIGH && isPlaying == true && firstSong == false) {  
      lastCheck = currentMillis;
      isPlaying = false;
      firstSong = false;
        // Function to randomize music after the first two tracks
        if (songNumber > lastSequentialTrack){
          songNumber = random(lowRandomTrack,highRandomTrack);
          counter = ++counter;
            if (counter >= 7){    // After playing all songs in the folder, the music stops and the fire is lit
              stopMusic();
              counter = 0;        // Reset counter for next iteration
            }
        } else {
            ++songNumber;         // Move on to the next song
        }
    }
  } 
}