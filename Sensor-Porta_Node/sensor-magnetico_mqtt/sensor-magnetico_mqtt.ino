#include <ESP8266WiFi.h>
#include <PubSubClient.h>

int sensorPin = 0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

char* newVal = "";
char* oldVal = "";

// Change the credentials below, so your ESP8266 connects to your router
const char* ssid     = "droid_wlan";
const char* password = "WlanDr01d16";

// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
const char* mqtt_server = "192.168.246.145";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
//float temp = 0;
int inPin = 5;
int magPin=4;

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient_temperature_sensor")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
 
void setup() {
  Serial.begin(115200);

  setup_wifi(); 
  client.setServer(mqtt_server, 1883);

  pinMode(inPin, INPUT);
  pinMode(magPin, INPUT_PULLUP); //4 se for no node 
}

void loop() {
   int  sensorValue = analogRead(A0);
    // map it to the range of the analog out:
   int outputValue = map(sensorValue, 0, 562, 0, 100);

   delay(1000);
   
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  /*
  long now = millis();
  if (now - lastMsg > 60000) {
    lastMsg = now;
    sensors.setResolution(12);
    sensors.requestTemperatures(); // Send the command to get temperatures
    temp = sensors.getTempCByIndex(0);
    Serial.println(temp);
    if((temp > -20) && (temp <60))
      {
      client.publish("/esp8266/soiltemp", String(temp).c_str(),TRUE);
      }
   client.publish("/esp8266/soilhumidity",String(outputValue).c_str(),TRUE);
   Serial.println(temp);
   Serial.println(sensorValue);
   Serial.println(outputValue);   
   Serial.println("Fim transmissão!!!! temp");
  }*/
   if (digitalRead(magPin) == HIGH){
     newVal = "A";     // Aberto
     Serial.println(" ABERTO"); 
  } 
  else {
    newVal = "B";     // Fechado
    Serial.println("FECHADO ");
    
  }
  
  client.publish("/esp8266/doorStatus", newVal);

/*
  if (newVal != oldVal && newVal==1) {
    Serial.println("MUDOU MUDOU");
    oldVal = newVal;
    client.publish("/esp8266/doorStatus", newVal);
    delay(10000);
  } 
  else {
    Serial.println("IGUAL IGUAL");
    oldVal=0;   
    //client.publish("/esp8266/doorStatus", String("PORTA FECHADA!!!").c_str(),TRUE);
    delay(10000);
  }*/
  
}
