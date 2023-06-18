#include <SPI.h>
#include <LoRa.h>

#define SENDER_ADDRESS 0x01    // Change this to the address of the transmitter
#define RECEIVER_ADDRESS1 0x02  // Change this to the address of the receiver1
#define RECEIVER_ADDRESS2 0x03  // Change this to the address of the receiver1

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
  if (LoRa.parsePacket()) {
    byte destination = LoRa.read();
    byte sender = LoRa.read();
    byte size = LoRa.read();
    String message = "";

    while (LoRa.available()) {
      message += (char)LoRa.read();
    }

    if (destination == RECEIVER_ADDRESS1) {           //Relay address
      Serial.print("Received message from Relay address: ");
      Serial.println(sender);                         //Source address
      
      String relaymsg = message + "(sent through relay)";
      
      LoRa.beginPacket();
      LoRa.write(RECEIVER_ADDRESS2);                  //Receiver address as destination
      LoRa.write(RECEIVER_ADDRESS1);                  //Relay address as second sender
      LoRa.write(relaymsg.length());
      LoRa.print(relaymsg);
      LoRa.endPacket();

      Serial.println("Message sent to Receiver!");
      delay(500);
    }
  }
}