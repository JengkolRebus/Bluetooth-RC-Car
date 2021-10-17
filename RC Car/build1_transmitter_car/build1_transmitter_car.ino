#include <VirtualWire.h>

int LX;
int LY;
int RX;
int RY;

int lx;
int ly;
int rx;
int ry;

const char *msg;

const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;

void setup()
{
  Serial.begin(9600);
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);   // Bits per sec
}

byte count = 1;

void loop()
{
  //LX = analogRead(A0);
  LY = analogRead(A1);
  RX = analogRead(A2);
  //RY = analogRead(A3);
  //lx = map(pot, 0, 1023, 0, 2);
  ly = map(LY, 0, 1023, 0, 4);
  rx = map(RX, 0, 1023, 0, 4);
  //ry = map(pot, 0, 1023, 0, 2);
  
  Serial.print(ly);
  Serial.print("\t");
  Serial.print(rx);
  Serial.print("\t");
  //char msg[7] = {'h','e','l','l','o',' ','#'};

  if(ly == 2 && rx == 2){
    msg = "A";  //diam
  }
  else if(ly == 0 && rx == 2){
    msg = "B";  //maju
  }
  else if(ly == 3 && rx == 2){
    msg = "C";  //mundur
  }
  else if(rx == 0 && ly == 2){
    msg = "D";  //kiri
  }
  else if(rx == 3 && ly == 2){
    msg = "E";  //kanan
  }
  
  Serial.println(msg);

  //msg[6] = count;
  //digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 1);
  vw_wait_tx(); // Wait until the whole message is gone
  //digitalWrite(led_pin, LOW);
  delay(1);
  //count = count + 1;
}
