/* Use the following settings for RobotDyn WiFi D1 mini PRO:
 * ESP8266 Boards v2.5.2 (installed via Boards Manager) - LOLIN (Wemos) D1 Mini Pro)
 * CPU Speed: either choice
 * 
*/

/* Use the following settings for Nano
 * Arduino AVR Boards - Arduino Nano
 * CPU Speed: either choice
 * 
*/

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include "Wire.h"
#include "Controller.h"
#include "FeedbackController.h"

//#include "config_nano.h"
#include "config_D1_pro_mini.h"

//Wifi credentials
const char* ssid = "Nacho2G";
const char* password = "yaNgchInghaOpu'ErchA@$350reMinbi";
const char* submissionUrl = "http://54.162.202.222/pulogger/submitdatum/";
//const char* submissionUrl = "http://192.168.1.11:8000/pulogger/submitdatum/";


String CONTROLLERNAME = "test";
//const uint8_t SENSORCOUNT = 1;
//uint8_t SENSORADDRESSES[SENSORCOUNT] = {0x77};
//String SENSORNAMES[SENSORCOUNT] = {"sensor1"};
const uint8_t SENSORCOUNT = 2;
uint8_t SENSORADDRESSES[SENSORCOUNT] = {0x76, 0x77};
String SENSORNAMES[SENSORCOUNT] = {"sensor1", "sensor2"};

HTTPClient http;
Controller* puLogger = nullptr;
FeedbackController* temperatureController = nullptr;
FeedbackController* humidityController = nullptr;


String addParameter(String url, String paramName, String paramValue) {
  url += (url.indexOf('?') != -1 ? "&" : "?");
  url += (paramName + "=" + paramValue);
  return url;
}

void submitData(FeedbackController* fController, String submissionUrl) {
  HTTPClient http;

  for (int i = 0; i < fController->inputCount; i++) {
    String sensorParameter;
    switch(fController->inputs[i].getParameterCode()) {
      case 'T':
        sensorParameter = "temperature";
        break;
      case 'H':
        sensorParameter = "humidity";
        break;
      default:
        sensorParameter = "invalid";
    }
    String sensorName = fController->inputs[i].getName();
    double sensorValue = fController->inputs[i].get();

    String url = submissionUrl;
    url = addParameter(url, "device", CONTROLLERNAME);
    url = addParameter(url, "sensor", sensorName);
    url = addParameter(url, "type", sensorParameter);
    url = addParameter(url, "value", String(sensorValue));
    
    http.begin(url);      //Specify request destination
    http.addHeader("Content-Type", "text/plain");  //Specify content-type header
    
    int httpCode = http.GET();   //Send the request
    String payload = http.getString();                  //Get the response payload
    
//    Serial.println(httpCode);   //Print HTTP return code
//    Serial.println(payload);    //Print request response payload
    
    http.end();  //Close connection
  }
}


void setup() {
	Serial.begin(57600);
	Wire.begin();
  WiFi.begin(ssid, password);   //WiFi connection
	
	puLogger = new Controller();
	
	puLogger->defineBME280Sensors(SENSORADDRESSES, SENSORNAMES, SENSORCOUNT);
  puLogger->defineBuzzer(BUZZERPIN);
  puLogger->defineHumidifier(FANPIN);
  puLogger->defineHeater(HEATPIN);

  humidityController = new FeedbackController(false,false,200);
  humidityController->defineInputs(reinterpret_cast<Sensor**>(puLogger->sensors), SENSORCOUNT,'H');
  DigitalOutputDevice* humidifier[1] = {puLogger->humidifier};
  humidityController->setSetpoint(65.0);
  humidityController->setHysteresis(0.5);
  humidityController->setUpperBound(68.0);
  humidityController->defineOutputs(humidifier, 1);
  
  temperatureController = new FeedbackController(false,false,200);
  temperatureController->defineInputs(reinterpret_cast<Sensor**>(puLogger->sensors), SENSORCOUNT,'T');
  DigitalOutputDevice* heater[1] = {puLogger->heater};
  temperatureController->setSetpoint(25.0);
  temperatureController->defineOutputs(heater, 1);

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
 
}


void loop() { 
  humidityController->poll();
  temperatureController->poll();
  Serial.print("AVG: (");
  Serial.print(humidityController->getAvgValue());
  Serial.print("|");
  Serial.print(temperatureController->getAvgValue());
  Serial.print(")");
  
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    submitData(humidityController, submissionUrl);
    submitData(temperatureController, submissionUrl);
  }
  else {
    Serial.println("Error in WiFi connection");   
  }
  
  Serial.println("");
  delay(1000*10);
}
