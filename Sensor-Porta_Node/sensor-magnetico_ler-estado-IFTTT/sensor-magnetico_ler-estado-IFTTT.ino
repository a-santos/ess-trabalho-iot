/** 
@info: Sensor Magnético para Porta/ Janela, com envio do estado por mail (IFTTT)
      Testado na droidWlan + mail do Pedro
@status: ok
*/

/** 
LIGAÇÕES: NodeMCU
* Alimentação -> USB
* D1 -> cabo grande
* G -> cabo peq.

--> Sensor magnético
+ (cabo grande) -> R.10K + D2
- (cabo peq)    -> 3V (ou 5?)
*/

#include <ESP8266WiFi.h>

const char* ssid = "droid_wlan";        
const char* password = "WlanDr01d16";
const char* host = "maker.ifttt.com";
const char* apiKey = "dh0w-_fzIG-x02VrAHNnpa";     // key da recipe do Pedro
const char* door_state = "PORTA ABERTA !!!!!";

int newVal = 0;
int oldVal = 0;

void setup() {
  //Iniciar a porta Serie para Debug
  Serial.begin(115200); 
  
  delay(100);
  pinMode(4, INPUT);            // 4 se for no node 

  Serial.print("Connecting to: ");
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

void loop() {
  WiFiClient client;

  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed !!");
    return;
  }
   
  if (digitalRead(4) == HIGH){
    newVal = 0;             // estado = Fechado
    Serial.println("FECHADO ");
  }
  else{
    newVal = 1;             // estado = Aberto
    Serial.println("ABERTO ");

    String url = "/trigger/door_status/with/key/";
    url += apiKey;
    //Serial.println(host);
          
    Serial.print("Requesting URL: ");
    Serial.println(url);
    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
          "Host: " + host + "\r\n" + 
          "Content-Type: application/x-www-form-urlencoded\r\n" + 
          "Content-Length: 13\r\n\r\n" +
          "value1=" + door_state + "\r\n");                   
  }

  if (newVal != oldVal) {
    Serial.println("ESTADO MUDOU");
    oldVal = newVal;
  }
  else{
    Serial.println("ESTADO ESTA IGUAL");   
  }
  
  delay(2000);
}
