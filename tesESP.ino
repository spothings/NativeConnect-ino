#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "bukanspot";
const char* password = "kosonginaja";

//Your Domain name with URL path or IP address with path
String serverName = "http://172.16.7.2/insert.php";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 6 seconds (6000)
unsigned long timerDelay = 6000;

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName + "?voltageR=" + random(10,200) + "&currentR=" + random(10,200) + "&powerR=" + random(10,200) + "&energyR=" + random(10,200) + "&frequencyR=" + random(10,200) + "&pfR=" + random(10,200) + "&voltageS=" + random(10,200) + "&currentS=" + random(10,200) + "&powerS=" + random(10,200) + "&energyS=" + random(10,200) + "&frequencyS=" + random(10,200) + "&pfS=" + random(10,200) + "&voltageT=" + random(10,200) + "&currentT=" + random(10,200) + "&powerT=" + random(10,200) + "&energyT=" + random(10,200) + "&frequencyT=" + random(10,200) + "&pfT=" + random(10,200);
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
