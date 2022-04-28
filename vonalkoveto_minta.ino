/*
MSZO vonalkövető autó 2.0 mintakód
vonalérzékelő szenzorok tesztelésére (soros porttal)
a breadboard 4 érzékelőt tartalmaz, mindegyiken egy infra LED és fotorezisztor van
összesen 10 kábel lóg ki belőle
*/

// analóg input kábelek (fehér)
#define sensor1 A0
#define sensor2 A1
#define sensor3 A2
#define sensor4 A3
// infra LED kapcsolásához (narancs) - PWM (vagy sima digital pin)
#define infraLed1 9
#define infraLed2 10
#define infraLed3 11
#define infraLed4 3
// piros kábel a GND, fekete az 5V!
#define jobbE 5
#define jobbH 6
#define balE 7
#define balH 8

const int brightness = 50; // maximum fényesség 0-nál, minimum 255-nél

// bemenet: i=0..1023 (int)
// kimenet: text=" 690: #############      " (String)
String value2graph(int inp=0){
  int symNum = 30 * (double)inp / 1024;
  String text = String(inp) + ": ";
  if (inp < 10) text = " " + text;
  if (inp < 100) text = " " + text;
  if (inp < 1000) text = " " + text;
  for(int i=0; i<20; i++) {
    if(i<symNum) text+="#";
    else text+=" ";
  }
  return text;
}

// bemenet: analóg pin azonosítója (uint8_t)
// leolvas 3 értéket a pinen, és átlagolja az értékeket
// kimenet: átlagos feszültség a pinen, avg=0..1023 (int)
int anRead(uint8_t pin){
  int inp1 = analogRead(pin); delay (1);
  int inp2 = analogRead(pin); delay (1);
  int inp3 = analogRead(pin);
  int avg = (inp1 + inp2 + inp3) / 3;
  return avg;
}

// setup, egyszer fut le, minden más előtt
void setup() {  
  Serial.begin(9600); // soros port bekapcsolása (jobb fent a nagyítóval nyitható meg)

  analogWrite(infraLed1, 255);  // PWM vezérlése, így van kikapcsolva
  analogWrite(infraLed2, 255);
  analogWrite(infraLed3, 255);
  analogWrite(infraLed4, 255);
  pinMode(jobbE, OUTPUT);
  pinMode(jobbH, OUTPUT);
  pinMode(balE, OUTPUT);
  pinMode(balH, OUTPUT);
}

// loop, folyamatosan újrafut
void loop() {
  // szenzorok tesztelésére
  analogWrite(infraLed1, brightness); delay(20);  // áram kapcsolása az első infra LED-re
  int inp1 = anRead(sensor1); analogWrite(infraLed1, 255);  // analóg bemeneten beolvasás, infra LED kikapcsolása
  analogWrite(infraLed2, brightness); delay(20);  // következő LED
  int inp2 = anRead(sensor2); analogWrite(infraLed2, 255);  // input: 0 ha sok fény visszaverődik, 1023 ha semennyi se
  analogWrite(infraLed3, brightness); delay(20);
  int inp3 = anRead(sensor3); analogWrite(infraLed3, 255);
  analogWrite(infraLed4, brightness); delay(20);
  int inp4 = anRead(sensor4); analogWrite(infraLed4, 255);
  
  Serial.println(value2graph(inp1) + value2graph(inp2) + value2graph(inp3) + value2graph(inp4));  //kiiratás a soros portra
  delay(160);/**/
  
  // motorok tesztelésére
  /*Serial.println("jobbE");
  digitalWrite(jobbE, HIGH);
  delay(2000);
  digitalWrite(jobbE, LOW);
  Serial.println("jobbH");
  digitalWrite(jobbH, HIGH);
  delay(2000);
  digitalWrite(jobbH, LOW);
  Serial.println("balE");
  digitalWrite(balE, HIGH);
  delay(2000);
  digitalWrite(balE, LOW);
  Serial.println("balH");
  digitalWrite(balH, HIGH);
  delay(2000);
  digitalWrite(balH, LOW);
  /**/
}