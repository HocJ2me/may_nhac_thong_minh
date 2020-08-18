
AudioGeneratorMP3 *mp3;
AudioFileSourceSPIFFS *file;
AudioOutputI2SNoDAC *out;
AudioFileSourceID3 *id3;

void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string)
{
  (void)cbData;
  Serial.printf("ID3 callback for: %s = '", type);

  if (isUnicode) {
    string += 2;
  }
  
  while (*string) {
    char a = *(string++);
    if (isUnicode) {
      string++;
    }
    Serial.printf("%c", a);
  }
  Serial.printf("'\n");
  Serial.flush();
}

void update_mp3()
{
    digitalWrite(output, HIGH);
//    file_name = test2.htm  
    Serial.println(url_audio);
    SPIFFS.remove(filename);
    File f = SPIFFS.open(filename, "w");
    if (f) {
      Serial.println("Downloading file");
      http.begin(url_audio);
      int httpCode = http.GET();
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          http.writeToStream(&f); //This is the part gives error i don't know why.
          
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      Serial.println("Done");
      Serial.println(f.size());
      f.close();
    }
  else Serial.println("Cannot open file name");
    http.end();
    digitalWrite(output, LOW);
}
void play_audio()
{
    audioLogger = &Serial;
    file = new AudioFileSourceSPIFFS(filename);
    id3 = new AudioFileSourceID3(file);
    id3->RegisterMetadataCB(MDCallback, (void*)"ID3TAG");
    out = new AudioOutputI2SNoDAC();
    mp3 = new AudioGeneratorMP3();
    out -> SetGain(3.9); //Set the volume
    mp3->begin(id3, out);
    Serial.println("Play audio");
    playing_audio = true;
}
void audio_running()
{
    if (mp3->isRunning()) 
    {
      if (!mp3->loop()) mp3->stop();
    }
    else
    {
      playing_audio = false;
//      Serial.print(".done.");
    }
}
