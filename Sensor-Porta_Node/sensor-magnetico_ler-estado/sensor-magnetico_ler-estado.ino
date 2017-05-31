/** 
@info: Sensor Magnético para Porta/ Janela
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

Links: http://iot-playground.com/blog/2-uncategorised/72-esp8266-wifi-door-window-sensor-easyiot-cloud-rest-api
      http://iot-playground.com/blog/2-uncategorised/91-esp8266-wifi-door-window-sensor-easyiot-cloud-rest-api-v1-0
*/

int newVal = 0;
int oldVal = 0;

void setup() {
  //Iniciar a porta Serie para Debug
  Serial.begin(115200); 
  
  pinMode(4, INPUT);      // 4 se for no Node 
}

void loop() {
  if (digitalRead(4) == HIGH){
    newVal = 0;           // estado = Fechado
    Serial.println("FECHADO ");
  } 
  else {
    newVal = 1;           // estado = Aberto
    Serial.println("ABERTO ");
  }

  if (newVal != oldVal) {
    Serial.println("ESTADO MUDOU");
    oldVal = newVal;
  } 
  else {
    Serial.println("ESTADO ESTA IGUAL");   
  }
  
  delay(2000);
}