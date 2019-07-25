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
const char* submissionUrl = "http://54.162.202.222/pulogger/submitdata/";
const char* timestampReqUrl = "http://54.162.202.222/pulogger/requestServerTime/";
//const char* submissionUrl = "192.168.1.11:8000/pulogger/submitdata/";
//const char* timestampReqUrl = "192.168.1.11:8000/pulogger/requestServerTime/";



//Device/sensor config
String CONTROLLERNAME = "test";
const uint8_t SENSORCOUNT = 2;
uint8_t SENSORADDRESSES[SENSORCOUNT] = {0x76, 0x77};
String SENSORNAMES[SENSORCOUNT] = {"sensor1", "sensor2"};
const int FCONTROLLERCOUNT = 2;

//Sensor calibration offsets (value = measurement + offset)
double HUMIDITYCALIBRATIONOFFSETS[SENSORCOUNT] = {5.0, 4.5};
//const double TEMPERATURECALIBRATIONOFFSETS = [0.0, 0.0]

HTTPClient http;
Controller* puLogger = nullptr;
FeedbackController* temperatureController = nullptr;
FeedbackController* humidityController = nullptr;
unsigned long lastTransmission = 0;
const unsigned long TRANSMISSIONPERIOD = 1000*10;


String addParameter(String url, String paramName, String paramValue) {
  url += (url.indexOf('?') != -1 ? "&" : "?");
  url += (paramName + "=" + paramValue);
  return url;
}

void submitData(FeedbackController** fControllers, String submissionUrl, String timestampReqUrl, int fControllerCount = 2) {
  HTTPClient http;
  String url = submissionUrl;
  String sensorNamesStr;
  String sensorParametersStr;
  String sensorValuesStr;

  for (int i = 0; i < fControllerCount; i++) {
    FeedbackController* fController = fControllers[i];
    
    for (int j = 0; j < fController->inputCount; j++) {
      String sensorParameter;
      switch(fController->inputs[j].getParameterCode()) {
        case 'T':
          sensorParameter = "temperature";
          break;
        case 'H':
          sensorParameter = "humidity";
          break;
        default:
          sensorParameter = "invalid";
      }
      
      String sensorName = fController->inputs[j].getName();
      double sensorValue = fController->inputs[j].get();
  
      sensorNamesStr += sensorName + ",";
      sensorParametersStr += sensorParameter + ",";
      sensorValuesStr += String(sensorValue) + ",";
    }
  }

  // Erase the final comma in each csv
  sensorNamesStr.remove(sensorNamesStr.length()-1);
  sensorParametersStr.remove(sensorParametersStr.length()-1);
  sensorValuesStr.remove(sensorValuesStr.length()-1);

  url = addParameter(url, "device", CONTROLLERNAME);    
  url = addParameter(url, "sensors", sensorNamesStr);
  url = addParameter(url, "types", sensorParametersStr);
  url = addParameter(url, "values", sensorValuesStr);

  Serial.println(url);

  // Get server timestamp, add as a parameter
  http.begin(timestampReqUrl);      //Specify request destination
  http.addHeader("Content-Type", "text/plain");  //Specify content-type header
  int httpCode = http.GET();  //Send the request
  String payload = http.getString();  //Get the response payload
  url = addParameter(url, "timestamp", payload); 
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.begin(url);      //Specify request destination
  http.addHeader("Content-Type", "text/plain");  //Specify content-type header
  httpCode = http.GET();  //Send the request
  payload = http.getString();  //Get the response payload
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection
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
  humidityController->defineInputs(reinterpret_cast<Sensor**>(puLogger->sensors), HUMIDITYCALIBRATIONOFFSETS, SENSORCOUNT,'H');
  DigitalOutputDevice* humidifier[1] = {puLogger->humidifier};
  humidityController->setSetpoint(68.0);
  humidityController->setHysteresis(0.5);
  humidityController->setUpperBound(73.0);
  humidityController->defineOutputs(humidifier, 1);
  humidityController->defineBuzzer(puLogger->buzzer);
  humidityController->setAlarm(62.0, 73.5, 1000*60*60);
  
  temperatureController = new FeedbackController(false,false,200);
  temperatureController->defineInputs(reinterpret_cast<Sensor**>(puLogger->sensors), SENSORCOUNT,'T');
  DigitalOutputDevice* heater[1] = {puLogger->heater};
  temperatureController->setSetpoint(25.0);
  temperatureController->defineOutputs(heater, 1);
  temperatureController->defineBuzzer(puLogger->buzzer);
  temperatureController->setAlarm(24.0, 29.0, 1000*60*60);

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
 
}


void loop() { 
  humidityController->poll();
  temperatureController->poll();
  
  if(WiFi.status()!= WL_CONNECTED){   //Check WiFi connection status
    Serial.println("Error in WiFi connection"); 
  }
  else if (millis() - lastTransmission > TRANSMISSIONPERIOD ||
           millis() < lastTransmission) {

    FeedbackController* hController = reinterpret_cast<FeedbackController*>(humidityController);
    FeedbackController* tController = reinterpret_cast<FeedbackController*>(temperatureController);
    FeedbackController* fControllers[FCONTROLLERCOUNT] = {hController, tController};
            
    lastTransmission = millis();
    submitData(fControllers, submissionUrl, timestampReqUrl);
  }
  else {
    //idle
  }
}
