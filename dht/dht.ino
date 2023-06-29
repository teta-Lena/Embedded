#include <DHT.h>
#include <DHT_U.h>


    #include <DHT.h>
    DHT dht(14,DHT11); //pin14 is equivalent to D5 on esp8266 board
    
    const char* host = "iot.benax.rw";
    
    void setup(){
        Serial.begin(115200);
        dht.begin();                                                                                      
    }
    
    void readDHT11(String(&params)[3]){
      float Humidity = 0.0;
      float Temperature = 0.0;
      float HeatIndex = 0.0;
      /*Read temperature and humidity from DHT sensor*/
      Humidity = dht.readHumidity();
      Temperature = dht.readTemperature();
      /*The block of code below checks if either temperature or humidity failed
      and then exits early, allowing you not to waste a time.*/
      if(isnan(Humidity) || isnan(Temperature)){
        Serial.println("Failed to read from DHT sensor.");
        params [0] = "";
        params [1] = "";
        params [2] = "";
      }
      else{
        /*Calculate Heat Index */
        HeatIndex = dht.computeHeatIndex(Temperature, Humidity, false);
        params [0] = String(Temperature);
        params [1] = String(Humidity);
        params [2] = String(HeatIndex);
      }
    }
        void loop(){
        String data[3];
        readDHT11(data);
        String temperature = data[0];
        if(temperature!=""){
          String humidity = data[1];
          String heat_index = data[2];
//          String payload="";
//          String device = "KG271St-001";
//          payload = "device="+device+"&temperature="+temperature+"&humidity="+humidity+"&heat_index="+heat_index;    
//          connectToHost(80);
//          upload(payload, "/projects/4e8d42b606f70fa9d39741a93ed0356c/weather-station-02/backend.php");
Serial.println(temperature);
Serial.println(humidity);
        }
        else{
          Serial.println("Sensor reading failed.");
        }
        delay(30000);  
    }
