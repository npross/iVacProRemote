/*
  Dustcollector

  Turns an Dustcollector when you press a button
  Turns off dustcollector when you press another button

*/

static int bit_length = 425;
static unsigned char on_msg[5] = {0b11101010, 0b10101110, 0b10010011, 0b01001001, 0b00100000};
static unsigned char off_msg[5]= {0b11101010, 0b10101110, 0b10010010, 0b01001001, 0b00110000};
static int bits = 36;

void send_msg(char *msg, int bits, int bit_length) {
      int index = 0;
      int bindex = 7;

      digitalWrite(7, 0);
      delayMicroseconds(bit_length * 10);
 
      for (int i=0;i<bits;i++) {
        digitalWrite(7, msg[index] & (1 << bindex--));
        delayMicroseconds(bit_length);
        if (bindex < 0) {
          bindex = 7;
          index++;
        }
      }
      digitalWrite(7, 0);
      delayMicroseconds(bit_length * 10);
}

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
}

void loop() {
  digitalWrite(2, !digitalRead(9));   
  digitalWrite(3, !digitalRead(10));  
  digitalWrite(4, !digitalRead(11));  

  if (!digitalRead(9)) {
    for (int j=0;j<24;j++) {
      send_msg(on_msg, bits, bit_length);
      delay(100);
    }  
  }

  if (!digitalRead(10)) {
    for (int j=0;j<24;j++) {
      send_msg(off_msg, bits, bit_length);
      delay(100);
    }  
  }

  delay(10);
  
//  digitalWrite(, digitalRead(9));   // turn the LED on (HIGH is the voltage level)
}
