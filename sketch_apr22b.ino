#include <SoftwareSerial.h>

// Define the RX and TX pins for SoftwareSerial communication
#define GSM_RX 2
#define GSM_TX 3

SoftwareSerial gsmSerial(GSM_RX, GSM_TX); // RX, TX

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize GSM module serial communication
  gsmSerial.begin(9600);
  
  // Wait for the GSM module to initialize
  delay(1000);
  
  Serial.println("Enter the recipient's mobile number:");
  while(!Serial.available()); // Wait until data is received
  String recipientNumber = Serial.readStringUntil('\n');
  
  Serial.println("Enter the message:");
  while(!Serial.available()); // Wait until data is received
  String message = Serial.readStringUntil('\n');
  
  // Send AT command to test communication
  gsmSerial.println("AT");
  delay(1000);
  
  // Set SMS text mode
  gsmSerial.println("AT+CMGF=1");
  delay(1000);
  
  // Send SMS with the provided message to the provided recipient's mobile number
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(recipientNumber);
  gsmSerial.println("\"");
  delay(1000);
  gsmSerial.print(message);
  delay(1000);
  gsmSerial.write(26); // ASCII code for Ctrl+Z
  
  Serial.println("Message sent!");
}

void loop() {
  if (gsmSerial.available()) {
    // If data is available from GSM module, print it to serial monitor
    Serial.write(gsmSerial.read());
  }
  
  if (Serial.available()) {
    // If data is available from serial monitor, send it to GSM module
    gsmSerial.write(Serial.read());
  }
}
