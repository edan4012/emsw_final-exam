#include <DHT.h>
#include <DHT_U.h>
#include <SoftwareSerial.h>

#define BT_RXD 0
#define BT_TXD 1

#define MQ2pin A0

DHT dht(8, DHT11);
SoftwareSerial bluetooth(0, 1);
  

void setup() {
  bluetooth.begin(9600);
  Serial.begin(9600);
  dht.begin();
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}



void loop() {
  int on_off = Serial.read();
  delay(1000);
  char cmd = 0;
  if (bluetooth.available()) {
    cmd = bluetooth.read();

    if (cmd == '1') {
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
    }
    if (cmd == '0') {
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
    }
    Serial.println(cmd);
  }

  if (Serial.available()) {
    if (on_off == '1') {
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
    }
    if (on_off == '0') {
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
    }
  } 

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float g = analogRead(MQ2pin);

  if (cmd == 't') {
    bluetooth.println(t);
  }
  else if (cmd == 'h') {
    bluetooth.println(h);
  }
  else if (cmd == 'g') {
    bluetooth.println(g);
  }

  char charbuf[20] = {0};
  if (cmd == 't') {
    String c = String(t);
    c.toCharArray(charbuf, c.length());
    bluetooth.write(charbuf);
    Serial.println(charbuf);
  }
  else if (cmd == 'h') {
    String c = String(h);
    c.toCharArray(charbuf, c.length());
    bluetooth.write(charbuf);
    Serial.println(charbuf);
  }
  else if (cmd == 'g') {
    String c = String(g);
    c.toCharArray(charbuf, c.length());
    bluetooth.write(charbuf);
    Serial.println(charbuf);
  }

  Serial.print(t);
  Serial.print("C;");
  Serial.print(h);
  Serial.print("%;");
  Serial.print(g);
  Serial.print(";");
  Serial.println(on_off);
}
