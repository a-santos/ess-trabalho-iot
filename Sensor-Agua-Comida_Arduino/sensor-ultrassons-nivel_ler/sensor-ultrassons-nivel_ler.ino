/** 
@ info: Programa para medir nível da água e quantidade de comida 
    (cód. IFTTT comentado) 
@ material: Arduino, sensor de nível, sensor de ultrassons
@ status: ok
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

const char* ssid = "droid_wlan";        
const char* password = "WlanDr01d16";
  //const char* SSID = "Vodafone-3A4D78";        
  //const char* PASSWORD = "wifipedroalvaro";
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

void setup() {
  Serial.begin(9600);             // definir a vel. de comunicação na porta consola
  
  pinMode(PIN_LED_AGUA, OUTPUT); 
  pinMode(PIN_LED_COMIDA, OUTPUT);
  
  pinMode(PIN_US_TRIG, OUTPUT);
  pinMode(PIN_US_ECHO, INPUT);
  
  digitalWrite(PIN_US_TRIG, LOW);
  delayMicroseconds(2);
}

void loop() {
  long duration = 0;
  float distance = 0.0;

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

  // ********************** Comida - Ler distância **********************
  digitalWrite(PIN_US_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_US_TRIG, LOW);

  duration = pulseIn(PIN_US_ECHO, HIGH);
  //Serial.print(duration); //
  //Serial.println(" Microssegundos");

  distance = (((float)duration * (float)VEL_US_AR) / 2.0) / 10000.0;    // cálculos para mostrar em 'cm'

  delay(500);

  

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
    
  // ********************** Comida - Mostrar valores no terminal **********************
  Serial.println("");
  Serial.print("[COMIDA] Distancia: ");
  Serial.print(distance); 
  Serial.println(" cm");
  if (distance >= 10) {
    Serial.println("[COMIDA] Quantidade insuficiente");
    digitalWrite(PIN_LED_COMIDA, HIGH); 
  }
  else {
    Serial.println("[COMIDA] Quantidade suficiente");
    digitalWrite(PIN_LED_COMIDA, LOW); 
  }
  
  // Ligação à porta 80 HTTP
  /*const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }*/
  
  /*if (percentAgua > 30) {
    Serial.println("O nivel esta alto");
    digitalWrite(PIN_LED_COMIDA, LOW); 
    newValAgua = 0;
  }
  else {
    Serial.println("nivel baixo");
    digitalWrite(PIN_LED_COMIDA, HIGH); 
    newValAgua = 1;*/

    /*
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
  }*/ 

  // ********************** Água - Mostra se valor atual é diferente do anterior **********************
  /*if (newValAgua != oldValAgua) {      
    Serial.println("MUDOU");
    Serial.println("");
    oldValAgua = newValAgua;
  }
  else {
    Serial.println("IGUAL");
    Serial.println("");   
  }*/

  delay(4000);   
}
