/*Program to control LED (ON/OFF) from ESP32 using Serial Bluetooth
 * Thanks to Neil Kolbans for his efoorts in adding the support to Arduino IDE
 * Turotial on: www.circuitdigest.com 
 */

#include "BluetoothSerial.h" //Header File for Serial Bluetooth, will be added by default into Arduino

BluetoothSerial ESP_BT; //Object for Bluetooth

int incoming;
int MI1 = 16;
int MI2 = 17;
int MD1 = 2;
int MD2 = 4;
unsigned long lastMsg = 0;


void setup() {
  Serial.begin(9600); //Start Serial monitor in 9600
  ESP_BT.begin("AutoControl"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");
  pinMode(MI1, OUTPUT);
  pinMode(MI2, OUTPUT);
  pinMode(MD1, OUTPUT);
  pinMode(MD2, OUTPUT);   
}

void loop() {


  

  unsigned long now = millis();
  if ( ESP_BT.available())
  {   
        char data_received;
        char last_received;
        data_received = ESP_BT.read();  // Data received from bluetooth 
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

        //delay(200);
        
  }
  else  // If data is no available on serial port 
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
