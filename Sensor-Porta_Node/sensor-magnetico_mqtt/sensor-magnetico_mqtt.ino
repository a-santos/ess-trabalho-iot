#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// ATENÇÃO: Executar comando no PI para serviço MQTT correr em background
// $ mosquito -d

int sensorPin = 0;    
int sensorValue = 0;      

char* msg = "";

const char* ssid     = "droid_wlan";
const char* password = "WlanDr01d16";

// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
const char* mqtt_server = "10.20.138.127";     // IP do srv-PI

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
int inPin = 5;
int magPin = 5;

void setup_wifi() {
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
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
    } 
    else {
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
  pinMode(magPin, INPUT_PULLUP); //pullup para usar a resistencia do proprio node 
}

void loop() {
  int newVal = 1;
  int oldVal = 0;
  int  sensorValue = analogRead(A0);

  int outputValue = map(sensorValue, 0, 562, 0, 100);

  delay(1000);
   
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (digitalRead(magPin) == HIGH){
     newVal = 1;     // Aberto
     msg = "Aberto";     
     Serial.println(" ABERTO"); 
  } 
  else {
    newVal = 0;     // Fechado
    msg = "Fechado"; 
    Serial.println("FECHADO ");
    
  }
  
  client.publish("/esp8266/doorStatus", msg);

  delay(10000);
}