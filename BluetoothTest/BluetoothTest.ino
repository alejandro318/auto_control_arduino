#include <SoftwareSerial.h>
SoftwareSerial btSerial(D2, D3); // RX,
int MI1 = D0;
int MI2 = D1;
int MD1 = D5;
int MD2 = D6;
int LED = D4;
unsigned long lastMsg = 0;

void setup() {
 Serial.begin(9600); /* Define baud rate for serial communication */
 pinMode(LED, OUTPUT);
 pinMode(MI1, OUTPUT);
 pinMode(MI2, OUTPUT);
 pinMode(MD1, OUTPUT);
 pinMode(MD2, OUTPUT);   
 btSerial.begin(9600);
 Serial.println("Started...");

}

void loop() {
  unsigned long now = millis();
  if ( btSerial.available())
  {   
        char data_received;
        char last_received;
        data_received = btSerial.read();  /* Data received from bluetooth */
        if (data_received == '1') //adelante
        {
         digitalWrite(MI1, HIGH);
         digitalWrite(MI2, LOW);
         digitalWrite(MD1, HIGH);
         digitalWrite(MD2, LOW);
         //Serial.write("Adelante\n");        
        }
        else if (data_received == '2') //atras
        {       
         digitalWrite(MI1, LOW);
         digitalWrite(MI2, HIGH);
         digitalWrite(MD1, LOW);
         digitalWrite(MD2, HIGH);
         //Serial.write("Atras\n");
        }
        else if (data_received == '3') //derecha
        {
         digitalWrite(MI1, HIGH);
         digitalWrite(MI2, LOW);
         digitalWrite(MD1, LOW);
         digitalWrite(MD2, LOW);
         //Serial.write("Derecha\n");
        }
        else if (data_received == '4') //izquierda
        {       
         digitalWrite(MI1, LOW);
         digitalWrite(MI2, LOW);
         digitalWrite(MD1, HIGH);
         digitalWrite(MD2, LOW);
         //Serial.write("Izquierda\n");
        }
        Serial.println( data_received);
         lastMsg = now; 
        
  }
  else  /* If data is no available on serial port */
  {
    if ( (now - lastMsg ) > 200 ) 
    {
         lastMsg = now; 
         digitalWrite(MI1, LOW);
         digitalWrite(MI2, LOW);
         digitalWrite(MD1, LOW);
         digitalWrite(MD2, LOW);
         Serial.println("Clean");

    }
  } 
 
}
