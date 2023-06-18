#include <SPI.h>
#include <LoRa.h>

#define SENDER_ADDRESS 0x01    // Change this to the address of the transmitter
#define RECEIVER_ADDRESS1 0x02  // Change this to the address of the relay
#define RECEIVER_ADDRESS2 0x03  // Change this to the address of the receiver

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  String message1 = "Hello Indirect"; // Message to be sent
  byte destination1 = RECEIVER_ADDRESS1; // Destination address

  String message2 = "Hello Direct"; // Message to be sent
  byte destination2 = RECEIVER_ADDRESS2; // Destination address
  
  
  LoRa.beginPacket();
  LoRa.write(destination1);
  LoRa.write(SENDER_ADDRESS);
  LoRa.write(message1.length());
  LoRa.print(message1);
  LoRa.endPacket();

  Serial.println("Message sent to RELAY!");
  delay(500);

  LoRa.beginPacket();
  LoRa.write(destination2);
  LoRa.write(SENDER_ADDRESS);
  LoRa.write(message2.length());
  LoRa.print(message2);
  LoRa.endPacket();

  Serial.println("Message sent to RECEIVER!");
  delay(500);

   
}