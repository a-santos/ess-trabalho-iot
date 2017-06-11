/** 
@ info: Programa para medir nível da água e quantidade de comida 
@ material: Arduino, sensor de nível, sensor de ultrassons
*/

/** 
LIGAÇÕES: -> Arduino Uno
5V -> USB
GND -> breadboard
Pin A1 -> HC-SR04 
Pin A0/S -> sensor de nível 
Pin 8 + R.180 Ohm -> PIN_LED_AGUA Vermelho         
Pin 11 + R.180 Ohm -> PIN_LED_AGUA Verde 

--> Sensor ultrassons HC-SR04
VCC -> 5V 
GND -> GND 
Trig -> Pin 3 
Echo -> Pin 5
 
--> Sensor de nível
+ -> 5V 
- -> GND 
S -> A0 (Arduino)
*/

#include <SPI.h>
#include <Ethernet.h>

const char* ssid = "droid_wlan";        
const char* password = "WlanDr01d16";
const char* HOST = "maker.ifttt.com";
const char* API_KEY = "jcmug3BB7gFhv9eMvzRLXuvEuNmm1Le8xZWOgmG-LSY";     // key da recipe do Gonçalo
const char* AGUA_ESTADO = "Animal com sede";

const int PIN_LED_AGUA = 8; 
const int PIN_LED_COMIDA = 11;  

// Variáveis para sensor de nível de água
const int PIN_SENSOR_NIVEL = A0;  
int val = 0;                        
int data = 0;                    
int newValAgua = 0;
int oldValAgua = 0;
int percentAgua = 0;

// Variáveis para sensor de distância de comida
const int PIN_US_TRIG = 3;
const int PIN_US_ECHO = 5;
const int VEL_US_AR = 343;        // vel. propagação dos ultrassons no ar = 343 m/s

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "192.168.246.145";    // IP na droid_wlan

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 199);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);             // definir a vel. de comunicação na porta consola
  
  pinMode(PIN_LED_AGUA, OUTPUT); 
  pinMode(PIN_LED_COMIDA, OUTPUT);
  
  pinMode(PIN_US_TRIG, OUTPUT);
  pinMode(PIN_US_ECHO, INPUT);
  
  digitalWrite(PIN_US_TRIG, LOW);
  delayMicroseconds(2);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    //client.println("GET /search?q=arduino HTTP/1.1");
    //client.println("Host: 192.246.145");
    //client.println("sou o Arduino do Afonso");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // ********************** Água - Ler nível ********************** 
  val = analogRead(PIN_SENSOR_NIVEL);     
  if (val > 700) {                        
      digitalWrite(PIN_LED_AGUA, HIGH); 
  }
  else {
    digitalWrite(PIN_LED_AGUA, LOW);      
  }

  // ********************** Água - Calc. percentagem ********************** 
  data = val;                           
  percentAgua = (data * 100) / 400;

  // ********************** Água - Mostrar valores no terminal ********************** 
  Serial.println("");
  Serial.print("[AGUA] Valor: ");
  Serial.println(data);                   
  Serial.print("[AGUA] Percentagem: ");
  Serial.println(percentAgua);
  if (percentAgua > 30) {
    Serial.println("[AGUA] Nivel alto");
    digitalWrite(PIN_LED_AGUA, LOW); 
    newValAgua = 0;
  }
  else {
    Serial.println("[AGUA] Nivel baixo");
    digitalWrite(PIN_LED_AGUA, HIGH); 
    newValAgua = 1;
  }

  // Ligação à porta 80 HTTP
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  if (percentAgua > 30) {
    Serial.println("O nivel esta alto");
    digitalWrite(PIN_LED_COMIDA, LOW); 
    newValAgua = 0;
  }
  else {
    Serial.println("nivel baixo");
    digitalWrite(PIN_LED_COMIDA, HIGH); 
    newValAgua = 1;

    
    String url = "/trigger/water_empty/with/key/";
    url += API_KEY;
    //Serial.println(host);
          
      Serial.print("Requesting URL: ");
      Serial.println(url);
      client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                "Host: " + HOST + "\r\n" + 
                "Content-Type: application/x-www-form-urlencoded\r\n" + 
                "Content-Length: 13\r\n\r\n" +
                "value1=" + water_empty + "\r\n");                  
  }

  // ********************** Água - Mostra se valor atual é diferente do anterior **********************
  if (newValAgua != oldValAgua) {      
    Serial.println("MUDOU");
    Serial.println("");
    oldValAgua = newValAgua;
  }
  else {
    Serial.println("IGUAL");
    Serial.println("");   
  }

  delay(4000); 
}