#include <ESP8266WiFi.h>

WiFiClient wifiClient;    
const char* host = "iot.benax.rw";

void setup(){
    Serial.begin(115200);
    connectToWiFi("Benax Technologies", "ben@kusu");                                                                                          
}

void loop(){
    String mData="";
    String dummy_device = "KG271St-001";
    String dummy_temperature = "25.00";
    mData = "device="+dummy_device+"&temperature="+dummy_temperature;    
    connectToHost(80);
    transferData(mData, "/projects/4e8d42b606f70fa9d39741a93ed0356c/iot/backend.php"); 
    delay(30000);  
}

void connectToWiFi(const char* ssid, const char* passwd){
    WiFi.mode(WIFI_OFF); //This prevents reconnection issue
    delay(10);
    WiFi.mode(WIFI_STA); //This hides the viewing of ESP as wifi hotspot
    WiFi.begin(ssid, passwd); //Connect to your WiFi router
    while (WiFi.status() != WL_CONNECTED){
        delay(1000);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("WiFi Connected.");
    Serial.println();  
}

void connectToHost(const int httpPort){
    int retry_counter=0; //To be used while retrying to get connected
    wifiClient.setTimeout(15000); // 15 Seconds
    delay(1000);
    Serial.printf("Connecting to \"%s\"\n", host);
  
    while((!wifiClient.connect(host, httpPort)) && (retry_counter <= 30)){
      delay(100);
      Serial.print(".");
      retry_counter++;
    }
  
    if(retry_counter==31){
      Serial.println("\nConnection failed.");
      return;
    }
    else{
      Serial.println("Connected.");
    }   
}

void transferData(String data, const char* filepath){
    wifiClient.println("POST "+(String)filepath+" HTTP/1.1");
    wifiClient.println("Host: " + (String)host);
    wifiClient.println("User-Agent: ESP8266/1.0");
    wifiClient.println("Content-Type: application/x-www-form-urlencoded");
    wifiClient.println("Content-Length: " +(String)data.length());
    wifiClient.println();
    wifiClient.print(data); 
    Serial.println("Uploading data...");
    parseResponse("Success");
}

/*
 * GET FEEDBACK
*/
void parseResponse(String success_msg){
    String datarx;
    while (wifiClient.connected()){
        String line = wifiClient.readStringUntil('\n');
        if (line == "\r") {
        break;
        }
    }
    while (wifiClient.available()){
        datarx += wifiClient.readStringUntil('\n');
    }

    if(datarx.indexOf(success_msg) >= 0){
        Serial.println("Uploaded.\n");  
    }
    else{
        Serial.println("Failed.\n"); 
    }
    Serial.println("*******************\n");
    datarx = "";  
}