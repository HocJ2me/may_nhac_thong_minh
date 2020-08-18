#define output 0
ESP8266WebServer server(80);
const char* ssid = "DaNang0135";
const char* passphrase = "dndndndn";
String st;
String content;
int statusCode;
int connect_time = 0;

unsigned long last_time = 0L;
unsigned long last_update = 0L;

const char filename[] = "/amthanh.mp3";
const char json_string[] = "http://www.maynhac.com/DN0135/schedule.json";
String url_audio;

String Time1 = "00:00";
String Time2 = "00:00";
String Time3 = "00:00";
String Time4 = "00:00";
String Time5 = "00:00";
String Time6 = "00:00";
String Time7 = "00:00";
String Time8 = "00:00";
String Time9 = "00:00";
String Time10 = "00:00";

boolean playing_audio = false;
