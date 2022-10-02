/*Program to control LED (ON/OFF) from ESP32 using Serial Bluetooth
   Thanks to Neil Kolbans for his efoorts in adding the support to Arduino IDE
   Turotial on: www.circuitdigest.com
*/

#include "BluetoothSerial.h" //Header File for Serial Bluetooth, will be added by default into Arduino

BluetoothSerial ESP_BT; //Object for Bluetooth

int incoming;
int MI1 = 16;
int MI2 = 17;
int MD1 = 2;
int MD2 = 4;
unsigned long lastMsg = 0;

int LED = 13;



#define echoPin 23 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 22 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement



void setup() {
  Serial.begin(9600); //Start Serial monitor in 9600
  ESP_BT.begin("AutoControl"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");

  //Pins setup for motors
  pinMode(MI1, OUTPUT);
  pinMode(MI2, OUTPUT);
  pinMode(MD1, OUTPUT);
  pinMode(MD2, OUTPUT);

  pinMode(LED, OUTPUT);

/*
  //Pins setup for ultrasonic sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.println("Ultrasonic Sensor HC-SR04 "); // print some text in Serial Monitor
  */
}

void loop() {

/*
  //Code for Ultrasonic sensor
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.print(distance);
  //Serial.println(" cm");

  if(distance < 10)
    digitalWrite(LED, HIGH);
  else  
    digitalWrite(LED, LOW);
*/
  distance = 11;

  //code for motor
  unsigned long now = millis();
  if ( ESP_BT.available())
  {
    char data_received;
    char last_received;
    data_received = ESP_BT.read();  // Data received from bluetooth
    if (data_received == '1') //adelante
    {
      if(distance > 10)
      {
        digitalWrite(MI1, LOW);
        digitalWrite(MI2, HIGH);
        digitalWrite(MD1, HIGH);
        digitalWrite(MD2, LOW);
        //Serial.write("Adelante\n");
      }
      else
      {
        Serial.print("Obstaculo a ");
        Serial.print(distance);
        Serial.println(" cm");

      }
    }
    else if (data_received == '2') //atras
    {
        digitalWrite(MI1, HIGH);
        digitalWrite(MI2, LOW);
        digitalWrite(MD1, LOW);
        digitalWrite(MD2, HIGH);
        //Serial.write("Atras\n");
    }
    else if (data_received == '3') //derecha
    {
      digitalWrite(MI1, LOW);
      digitalWrite(MI2, HIGH);
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
