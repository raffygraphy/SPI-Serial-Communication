#include <SPI.h>

char buff1[] = "Hi 1!";
char buff2[] = "Hi 2!";
char receivedDataFromSlave1[100];

int count1 = 0;
int count2 = 0;
const int slave1 = D1;
const int slave2 = D2;

void setup() {
  Serial.begin(9600); 
  SPI.begin();        
  count1 = sizeof(buff1);
  count2 = sizeof(buff2);

  pinMode(slave1, OUTPUT);
  pinMode(slave2, OUTPUT);

  // Set both slave select pins high
  digitalWrite(slave2, HIGH);
  digitalWrite(slave1, HIGH);
}

void loop() {

  //Chip Select Slave 1
  Serial.println("Tapping Slave 1");
  digitalWrite(slave1, LOW);
  Serial.print("Master Sending: ");
  Serial.println(buff1);
  for (int i = 0; i < count1; i++) {
    SPI.transfer(buff1[i]);

    delay(1000);
  }
  digitalWrite(slave1, HIGH);

  //Chip Select Slave 2
  Serial.println("Tapping Slave 2");
  digitalWrite(slave2, LOW);
  Serial.print("Master Sending: ");
  Serial.println(buff2);
  for (int i = 0; i < count2; i++) {
    SPI.transfer(buff2[i]);
    delay(1000);
  }
  digitalWrite(slave2, HIGH);
}
