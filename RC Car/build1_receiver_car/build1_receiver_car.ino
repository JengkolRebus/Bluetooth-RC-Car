#include <VirtualWire.h>

int in1 = 2;
int in2 = 4;
int in3 = 5;
int in4 = 6; 

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;

void setup() {
  delay(1000);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  Serial.begin(9600);  // Debugging only
  Serial.println("setup");

  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);  // Bits per sec

  vw_rx_start();       // Start the receiver PLL running
}

void loop() {
  
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) { // Non-blocking
    int i;
    Serial.print("Got: ");
    for (i = 0; i < buflen; i++){
      Serial.print(buf[0]);
      Serial.print(' ');
      
      if(buf[0] == 'A') {   //diam
        digitalWrite(led_pin, LOW);
        Stop();
      }

      else if(buf[0] == 'B') {   //maju
        digitalWrite(led_pin, HIGH);
        
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      }
      
      else if(buf[0] == 'C') {    //mundur
        digitalWrite(led_pin, HIGH);
        
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
      }

      else if(buf[0] == 'D') {    //kiri
        digitalWrite(led_pin, HIGH);
        
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      }

      else if(buf[0] == 'E') {    //kanan
        digitalWrite(led_pin, HIGH);
        
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
      }
      
      else{
        digitalWrite(led_pin, LOW);
        Stop();
      }
    }
  Serial.println();
        //digitalWrite(led_pin, LOW);
  }
  
}
