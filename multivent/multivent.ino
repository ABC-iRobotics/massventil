#include <DallasTemperature.h>
#include <OneWire.h>

//65535

//#include <WiFi.h>
//#include <ArduinoJson.h>
//#include <PubSubClient.h>
//#include <ThingsBoard.h>

#include <ventillationControl.h>
#include <sensirionFlow.h>
#include <pressureSensor.h>


// pressure sensors
PressureSensor sensorPFlow;
PressureSensor sensorPPatient;
PressureSensor sensorPBB;
PressureSensor sensorPKB;
// flow sensor
SFM3300 sensirionSensorFlowPatient;
//temp sensor
#define ONE_WIRE_BUS 13
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensotTPatient(&oneWire);

//control variables
ventControl ventillationControl;
int homing = 1;


//const char* WIFI_APoint = "server";
//const char* WIFI_PASSWORD = "vent_server";
//char TOKEN[] = "6tp6MhXFNrx0I2XG55vt";  // mHOy9fVcanrFEoJ3uF5N  children temp sensor  //fVCqUjE93kSTPkaprC7S children thermo actuator // 1C7xeLknKbSYpHyi2YAi parent temp sensor
//char thingsboardServer[] = "192.168.0.222";
//WiFiClient wifiClient;
//PubSubClient client(wifiClient);
//ThingsBoard tb(wifiClient);
//int status = WL_IDLE_STATUS;


// sensor variables 
double pressurembar = 0;
double setpoint = 0;
double measureValue;
double sum_volume_calibrated = 0;
double pressureCurve[100];

//calibration variables 
bool Calibration = true;

unsigned long timeforhartbeat = 0;
unsigned long timeforprint = 0;
unsigned long timeformeasuring = 0;
unsigned long timeforcontrol = 0;




//temp sensor variables 
int  resolution = 12;
unsigned long lastTempRequest = 0;
int  delayInMillis = 0;

// command promt variables 
String dataArray;

// breasthin variables  
double pSetpointMax = 20.0;
double pSetpointMin = 2.0;
double fSetpointMax = 20.0;
double fSetpointMin = -15.0;
int fpcontrol = 1; // f:0 p:1
uint8_t  inout = 0; // steady 0  in 1  out 2

// the setup function runs once when you press reset or power the board
void setup()
{
  Serial.begin(115200);
  sensorPFlow.begin(A7);
  sensorPPatient.begin(A6);
  sensorPBB.begin(A3);
  sensorPKB.begin(A0);
  sensorPFlow.setoffsetV(2735.33);
  sensorPPatient.setoffsetV(1283.96);
  sensorPPatient.setscale(20 / 0.09);
  sensorPBB.setoffsetV(1287.43);
  sensorPBB.setscale(20 / 0.09);
  sensorPKB.setoffsetV(1284.64);
  sensorPKB.setscale(20 / 0.09);

  sensirionSensorFlowPatient.begin(0x40);
  sensirionSensorFlowPatient.startMeasuring();

  sensotTPatient.begin();
  sensotTPatient.setResolution(12);
  sensotTPatient.setWaitForConversion(false);
  delayInMillis = 750 / (1 << (12 - resolution));
  lastTempRequest = millis();

  ventillationControl.begin();
  
  /* InitWiFi();
    client.setServer( thingsboardServer, 1883 );
    client.setCallback(on_message);*/
}

void sensorsCalibration()
{
  if (timeformeasuring + 500 < micros())
  {
    sensorPFlow.measurePressure();
    sensorPPatient.measurePressure();
    sensorPBB.measurePressure();
    sensorPKB.measurePressure();
    if (!sensorPFlow.isCalibrated())  // calibration of sensor
    {
      sensorPFlow.calibration();
      Serial.print("sensorPFlow");
      Serial.print(sensorPFlow.getPressure());
      Serial.println();
    }
    else if (!sensorPPatient.isCalibrated())  // calibration of sensor
    {
      sensorPPatient.calibration();
      Serial.print("sensorPPatient");
      Serial.print(sensorPPatient.getPressure());
      Serial.println();
    }
    else if (!sensorPBB.isCalibrated())  // calibration of sensor
    {
      sensorPBB.calibration();
      Serial.print("sensorPBB");
      Serial.print(sensorPBB.getPressure());
      Serial.println();
    }
    else if (!sensorPKB.isCalibrated())  // calibration of sensor
    {
      sensorPKB.calibration();
      Serial.print("sensorPKB");
      Serial.print(sensorPKB.getPressure());
      Serial.println();
    }
    else
    {
      Calibration = false;
      Serial.println(sensorPFlow.offsetV);
      Serial.println(sensorPPatient.offsetV);
      Serial.println(sensorPBB.offsetV);
      Serial.println(sensorPKB.offsetV);
    }
  }
}
void printData()
{
  if (timeforprint + 50 < millis())
  {
    timeforprint = millis();

    Serial.print(setpoint);
    Serial.print(",");
    Serial.print(measureValue * -1);
    Serial.print(",");
    Serial.print(sum_volume_calibrated * -100);
    Serial.print(",");
    Serial.print(sensorPFlow.getPressure());
    Serial.print(",");
    Serial.print(sensorPPatient.getPressure());
    Serial.print(",");
    Serial.print(sensorPBB.getPressure());
    Serial.print(",");
    Serial.print(sensorPKB.getPressure());
    Serial.print(",");
    Serial.print(sensotTPatient.getTempCByIndex(0));
    Serial.println();
    /*
      for(int i=1; i< 100 ;i++)
      {
      pressureCurve[i-1]=pressureCurve[i];
      }

      pressureCurve[99]= sensorPFlow.getPressure();

      DynamicJsonDocument jsonBuffer(200);
      char payload[256];
      jsonBuffer["P1"] = sensorPFlow.getPressure();
      jsonBuffer["P2"] = sensorPPatient.getPressure();

      serializeJson(jsonBuffer, payload);
      String strPayload = String(payload);
      // Serial.println(strPayload);
      client.publish("v1/devices/me/telemetry", strPayload.c_str());
    */
  }
}
void breathingControl()
{

  if (Serial.available())
  {
    char c = Serial.read();
    if (c == 10)
    {
      int  ind1 = dataArray.indexOf(':');
      String cmd = dataArray.substring(0, ind1 );
      String cdata = dataArray.substring(ind1 + 1);

      Serial.print("Command: "); Serial.println(cmd);
      Serial.print("Data: "); Serial.println(cdata);

      if (cmd.equals("PP"))
      {
        ventillationControl.pKp = cdata.toDouble();
      }
      else if (cmd.equals("PI"))
      {
        ventillationControl.pKi = cdata.toDouble();
      }
      else if (cmd.equals("PD"))
      {
        ventillationControl.pKd = cdata.toDouble();

      }

      if (cmd.equals("FP"))
      {
        ventillationControl.pKp = cdata.toDouble();
      }
      else if (cmd.equals("FI"))
      {
        ventillationControl.pKi = cdata.toDouble();
      }
      else if (cmd.equals("FD"))
      {
        ventillationControl.pKd = cdata.toDouble();

      }

      else if (cmd.equals("PSMAX"))
      {
        pSetpointMax = cdata.toDouble();

      }
      else if (cmd.equals("PSMIN"))
      {
        pSetpointMin = cdata.toDouble();

      }
      else if (cmd.equals("FSMAX"))
      {
        fSetpointMax = cdata.toDouble();

      }
      else if (cmd.equals("FSMIN"))
      {
        fSetpointMin = cdata.toDouble();

      }
      else if (cmd.equals("CL"))
      {
        if (cdata.equals("flow"))
        {
          fpcontrol = 0;
        }
        else
        {
          fpcontrol = 1;
        }

      }
      else if (cmd.equals("A"))
      {
        if (cdata.equals("1"))inout = 0;
        else if (cdata.equals("2"))inout = 1;
      }
      ventillationControl.pidTuningP();
      ventillationControl.pidTuningF();
      Serial.println(ventillationControl.pKp);
      Serial.println(ventillationControl.pKi);
      Serial.println(ventillationControl.pKd);
      Serial.println(ventillationControl.fKp);
      Serial.println(ventillationControl.fKi);
      Serial.println(ventillationControl.fKd);
      Serial.println(pSetpointMax);
      Serial.println(pSetpointMin);
      Serial.println(fSetpointMax);
      Serial.println(fSetpointMin);


      dataArray = "";
      //

    }
    else dataArray += c;

  }

  if (timeforhartbeat + 1500 < millis())
  {
    timeforhartbeat = millis();
    if (inout == 1)inout = 2;
    else if (inout == 2)inout = 1;
    sum_volume_calibrated = 0;
  }

  if (inout == 0)
  {
    setpoint = -0.0;
  }
  else if (inout == 1)
  {
    if (fpcontrol) // f: 0 p:1
    {
      setpoint = pSetpointMax;
    }
    else
    {
      setpoint = fSetpointMax;
    }
  }
  else
  {
    if (fpcontrol) // f: 0 p:1
    {
      setpoint = pSetpointMin;
    }
    else
    {
      setpoint = fSetpointMin;
    }
  }

}
void controlLoop()
{
  if (timeformeasuring + 500 < micros())
  {
    timeformeasuring = micros();
    sensorPFlow.measurePressure();
    sensorPPatient.measurePressure();
    sensorPBB.measurePressure();
    sensorPKB.measurePressure();
    sensirionSensorFlowPatient.measureFlow();
    measureValue = sensirionSensorFlowPatient.readMeasuredFlow();
    sum_volume_calibrated += measureValue / 120000.0;
    if (fpcontrol) // f: 0 p:1
    { //pressure control
      ventillationControl.ventControlLoopP (sensorPPatient.getPressure(), setpoint);
    }
    else
    {
      ventillationControl.ventControlLoopF (measureValue * -1, setpoint);
    }
    //

  }
}
void loop() {
  /*
     if ( !client.connected() ) {
      reconnect();
    }
  */

  if (Calibration)
  {
    //// sensor calibration  ////
    sensorsCalibration();

    ////   Stepper homing ////
    if (!ventillationControl.homingSuccess)
    {
      Calibration = true;
      ventillationControl.runhoming();
    }

  }
  else
  {

    if (millis() - lastTempRequest >= delayInMillis) // // temperature sensor read, you must wait min 750ms at 12bi resolution
    {
      sensotTPatient.requestTemperatures();
      delayInMillis = 750 / (1 << (12 - resolution));
      lastTempRequest = millis();
    }
    //printing data
    printData();
    // setpoint manipulation (in and out)
    breathingControl();
    // controlling
    ventillationControl.runMotor();
    controlLoop();
  }


  //client.loop();

}


/*


  // The callback for when a PUBLISH message is received from the server.
  void on_message(const char* topic, byte* payload, unsigned int length) {

  Serial.println("On message");

  char json[length + 1];
  strncpy (json, (char*)payload, length);
  json[length] = '\0';

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(json);

  // Decode JSON request
  StaticJsonDocument<200> data;
  auto error = deserializeJson(data, json);

  if (error) {
    Serial.println("deserializeJson() failed");
    return;
  }

  // Check request method
  String methodName = String((const char*)data["method"]);


  if (methodName.indexOf("getTempCurve")>-1) {
      int index = 0;
     if (methodName.equals("getTempCurve1")) { index = 1; }
     else if (methodName.equals("getTempCurve2")) { index = 6; }
     else if (methodName.equals("getTempCurve3")) { index = 11; }
     else if (methodName.equals("getTempCurve4")) { index = 16; }
     else if (methodName.equals("getTempCurve5")) { index = 21; }
     else if (methodName.equals("getTempCurve6")) { index = 26; }
     else if (methodName.equals("getTempCurve7")) { index = 31; }
     else if (methodName.equals("getTempCurve8")) { index = 36; }
     else if (methodName.equals("getTempCurve9")) { index = 41; }
     else if (methodName.equals("getTempCurve10")) { index = 46; }
     else if (methodName.equals("getTempCurve11")) { index = 51; }
     else if (methodName.equals("getTempCurve12")) { index = 56; }
     else if (methodName.equals("getTempCurve13")) { index = 61; }
     else if (methodName.equals("getTempCurve14")) { index = 66; }
     else if (methodName.equals("getTempCurve15")) { index = 71; }
     else if (methodName.equals("getTempCurve16")) { index = 76; }
     else if (methodName.equals("getTempCurve17")) { index = 81; }
     else if (methodName.equals("getTempCurve18")) { index = 86; }
     else if (methodName.equals("getTempCurve19")) { index = 91; }
     else if (methodName.equals("getTempCurve20")) { index = 96; }
     else return;

    DynamicJsonDocument jsonBuffer(500);
    char payload[500];
    char buf[1];

    jsonBuffer[String(index)] = (int)((pressureCurve[index-1]*10)) /10.0;

    jsonBuffer[String(index+1)] = (int)((pressureCurve[index]*10)) /10.0;

    jsonBuffer[String(index+2)] = (int)((pressureCurve[index+1]*10)) /10.0;

    jsonBuffer[String(index+3)] = (int)((pressureCurve[index+2]*10)) /10.0;

    jsonBuffer[String(index+4)] = (int)((pressureCurve[index+3]*10)) /10.0;
    serializeJson(jsonBuffer, payload);
    String strPayload = String(payload);


    String requestTopic = String(topic);
    String responseTopic = String(topic);
    responseTopic.replace("request", "response");
    Serial.println(responseTopic);
    Serial.println(payload);
    client.publish(responseTopic.c_str(), strPayload.c_str());
  }



  }


  void InitWiFi() {
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_APoint, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
  }


  void reconnect() {

  // Loop until we're reconnected
  while (!client.connected()) {
    status = WiFi.status();
    if ( status != WL_CONNECTED) {
      WiFi.begin(WIFI_APoint, WIFI_PASSWORD);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("Connected to AP");
    }
    Serial.print("Connecting to ThingsBoard node ...");
    // Attempt to connect (clientId, username, password)
    if ( client.connect("Temp_act_test", TOKEN, NULL) ) {
      Serial.println( "[DONE]" );
      // Subscribing to receive RPC requests
      client.subscribe("v1/devices/me/rpc/request/+");
      // Sending current GPIO status
      Serial.println("Sending current GPIO status ...");




    } else {
      Serial.print( "[FAILED] [ rc = " );
      Serial.print( client.state() );
      Serial.println( " : retrying in 5 seconds]" );
      // Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
  }*/
