/** 
@info: Programa para medir nível da água e quantidade de comida 
    (cód. IFTTT comentado) 
@status: testar
    configurar qd cd sensor lê (e imprime valores)
    Água- no arranque, ñ mostrar 'mudou'
*/

/** 
LIGAÇÕES: -> Arduino Uno
5V -> USB
GND -> breadboard
Pin A1 -> HC-SR04 
Pin A0/S -> sensor de nível 
-Pin 8 -> PIN_LED_AGUA Vermelho (Água)    // + R.180 Ohm
-Pin 9 -> PIN_LED_AGUA Verde (Comida)

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
const int PIN_LED_COMIDA = 9;  

// Variáveis para sensor de nível de água
const int PIN_SENSOR_NIVEL = A0;  // level sensor connected to an analog port
int val = 0;                      // define a variable val initial value of 0    
int data = 0;                     // define a variable data initial value of 0
int dataPercent = 0;
int newValAgua = 0;
int oldValAgua = 0;

// Variáveis para sensor de distância de comida
const int PIN_TRIG = 3;
const int PIN_ECHO = 5;
const int VEL_ULTRASSONS_AR = 343;    // vel. propagação dos ultrassons no ar = 343 m/s

void setup() {
  Serial.begin(9600);       // definir a vel. de comunicação na porta consola
  
  pinMode(PIN_LED_AGUA, OUTPUT); 
  pinMode(PIN_LED_COMIDA, OUTPUT);
  
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
}

void loop() {
  long duration = 0;
  float distance = 0.0;

  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  duration = pulseIn(PIN_ECHO, HIGH);
  //Serial.print(duration); //
  //Serial.println(" Microssegundos");

  // ********************** Água - Ler nível ********************** 
  val = analogRead(PIN_SENSOR_NIVEL);     // read the analog value to the variable val
  if (val > 700) {                        // determine whether more than 700 variables val
      digitalWrite(PIN_LED_AGUA, HIGH); 
  }
  else {
    digitalWrite(PIN_LED_AGUA, LOW);      // when variable val is less than 700 , the lamp goes out piranha
  }

  // ********************** Água - Calc. percentagem ********************** 
  data = val;                             // variable is assigned to the variable data val
  dataPercent = (data * 100) / 400;

  // Cálculo da distância em cm
  distance = (((float)duration * (float)VEL_ULTRASSONS_AR) / 2.0) / 10000.0;

  // ********************** Água - Mostrar no terminal valores ********************** 
  Serial.print("Valor da Água: ");
  Serial.println(data);                   
  Serial.print("Percentagem da Água: ");
  Serial.println(dataPercent);

  // ********************** Comida - Mostrar no terminal valores **********************
  Serial.println("");
  Serial.print("Distancia para a comida: ");
  Serial.print(distance); 
  Serial.println(" cm");
  if (distance >= 10) {
    //digitalWrite(PIN_LED_AGUA, HIGH);
    Serial.println("Aviso: Pouca comida");
  }
  else {
    //digitalWrite(PIN_LED_AGUA, LOW);
    Serial.println("Comida suficiente");
  }
  
  // Ligação à porta 80 HTTP
  /*const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }*/
  
  if (dataPercent > 30) {
    Serial.println("O nivel esta alto");
    newValAgua = 0;
  }
  else {
    newValAgua = 1;
    Serial.println("nivel baixo");

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
                "value1=" + water_empty + "\r\n");    */               
  }

  // ********************** Água - Mostra se valor atual é diferente do anterior **********************
  /*
  if (newValAgua != oldValAgua) {      
    Serial.println("MUDOU");
    Serial.println("");
    oldValAgua = newValAgua;
  }
  else {
    Serial.println("IGUAL");
    Serial.println("");   
  }*/

  delay(3000);   
}


