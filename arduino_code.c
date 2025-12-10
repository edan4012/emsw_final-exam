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
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float g = analogRead(MQ2pin);
  
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

    if (cmd == 't') {
      bluetooth.println(t);
    }
    else if (cmd == 'h') {
      bluetooth.println(h);
    }
    else if (cmd == 'g') {
      bluetooth.println(g);
    }

    Serial.println(cmd);
  }

  if (Serial.available()) {
    char on_off = Serial.read();
    
    if (on_off == '1') {
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
    }
    if (on_off == '0') {
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
    }
  }

  Serial.print(t);
  Serial.print("C;");
  Serial.print(h);
  Serial.print("%;");
  Serial.print(g);
  Serial.println();
  delay(1000);
}
