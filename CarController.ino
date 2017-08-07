#include <DigiUSB.h>

#define CAR_FORWARD_PIN 0
#define CAR_BACKWARD_PIN 1
#define CAR_RIGHT_PIN 5
#define CAR_LEFT_PIN 2

#define ARMING_CODE 0xAA;

uint8_t speed_forward=0, speed_backward=0, speed_left=0, speed_right=0;
 
void setup() {
  DigiUSB.begin();
  pinMode(CAR_FORWARD_PIN, OUTPUT);
  pinMode(CAR_BACKWARD_PIN, OUTPUT);
  pinMode(CAR_RIGHT_PIN, OUTPUT);
  pinMode(CAR_LEFT_PIN, OUTPUT);
}

uint8_t get_input() {
  uint8_t current_key, last_key, counter=0;
  // when there are no characters to read, or the character isn't a newline
  while (counter < 10) { // loop forever
    if (DigiUSB.available()) {
      // something to read
      current_key = DigiUSB.read();
      DigiUSB.write(current_key);
      
      if (current_key == '\n') {
        //break; // when we get a newline, break out of loop
        return last_key;
      }
      else {
        last_key = current_key;
      }
    }
    
    // refresh the usb port for 10 milliseconds
    DigiUSB.delay(5);
    counter += 1;
  }
}

void control_car(uint8_t command)
{
  uint8_t forward_motion = command >> 4;
  uint8_t left_motion = command & 0x0f;

  for(uint8_t i=0;i<128; i++)
  {
    if(i<forward_motion)
    {
      digitalWrite(CAR_FORWARD_PIN, HIGH);
    }
  }
}

void loop() {
  uint8_t command = 0xAA;
  DigiUSB.println("Ready");
  while(command != 0xAA)
  {
    DigiUSB.println("Send 0xAA to arm the controller.");
    command = get_input();
    delay(100); 
  }
  command = get_input();
  while(command != 0xBB)
  {
    control_car(command);
    command = get_input();
  }
}
