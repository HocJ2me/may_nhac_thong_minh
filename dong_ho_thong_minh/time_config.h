WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "pool.ntp.org", 7 * 3600);

void setClock() {
  timeClient.begin();
}
boolean same_time(int h, int m, String T)
{
  if(((T[0]-48)*10+T[1]-48==h)&&((T[3]-48)*10+T[4]-48==m))
    return true;
  return false; 
}
void update_time()
{
      timeClient.update();
      Serial.print(timeClient.getHours());
      Serial.print(":");
      Serial.print(timeClient.getMinutes());
      Serial.print(":");
      Serial.println(timeClient.getSeconds());
      int Hour = timeClient.getHours(),
          Minute = timeClient.getMinutes();
      if( same_time(Hour, Minute, Time1)
          ||same_time(Hour, Minute, Time2)
          ||same_time(Hour, Minute, Time3)
          ||same_time(Hour, Minute, Time4) 
          ||same_time(Hour, Minute, Time5) 
          ||same_time(Hour, Minute, Time6) 
          ||same_time(Hour, Minute, Time7) 
          ||same_time(Hour, Minute, Time8) 
          ||same_time(Hour, Minute, Time9) 
          ||same_time(Hour, Minute, Time10)  
        ) if(!playing_audio) play_audio();
      
}
