/*
  Reading a serial ASCII-encoded string.

 This sketch demonstrates the Serial parseInt() function.
 It looks for an ASCII string of comma-separated values.
 It parses them into ints, and uses those to fade an RGB LED.

 Circuit: Common-Cathode RGB LED wired like so:
 * Red anode: digital pin 3
 * Green anode: digital pin 5
 * Blue anode: digital pin 6
 * Cathode : GND

 created 13 Apr 2012
 by Tom Igoe
 
 modified 14 Mar 2016
 by Arturo Guadalupi

 This example code is in the public domain.
 */

// pins for the LEDs:

#define RIGHT_CONTROL_PIN 4
#define LEFT_CONTROL_PIN 5
#define FORWARD_CONTROL_PIN 3
#define BACKWARD_CONTROL_PIN 2

#define ARM_COMMAND 'S'

char current_command = 'A';
uint8_t device_armed = 0;

void test()
{
   for(uint8_t i=0;i<100;i++)
   {
    digitalWrite(RIGHT_CONTROL_PIN, LOW);
//    digitalWrite(LEFT_CONTROL_PIN, LOW);
//    digitalWrite(FORWARD_CONTROL_PIN, LOW);
//    digitalWrite(BACKWARD_CONTROL_PIN, LOW);
  delay(100);
  }
}

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // make the pins outputs:
  pinMode(RIGHT_CONTROL_PIN, OUTPUT);
  pinMode(LEFT_CONTROL_PIN, OUTPUT);
  pinMode(FORWARD_CONTROL_PIN, OUTPUT);
  pinMode(BACKWARD_CONTROL_PIN, OUTPUT);

  digitalWrite(RIGHT_CONTROL_PIN, HIGH);
  digitalWrite(LEFT_CONTROL_PIN, HIGH);
  digitalWrite(FORWARD_CONTROL_PIN, HIGH);
  digitalWrite(BACKWARD_CONTROL_PIN, HIGH);
  Serial.print("Setup done");
//  test();
}


char get_input()
{
   char command = 'A';
   for(uint8_t i=0;i<100;i++)
   {
      if(Serial.available() > 0)
      {
          command = Serial.read();
          Serial.print(command);
          return command;
      }
      delay(1);
   }
   return command;
}


char control_car(char command)
{
  digitalWrite(RIGHT_CONTROL_PIN, HIGH);
  digitalWrite(LEFT_CONTROL_PIN, HIGH);
  digitalWrite(FORWARD_CONTROL_PIN, HIGH);
  digitalWrite(BACKWARD_CONTROL_PIN, HIGH); 

  if(command == 'l')
      digitalWrite(LEFT_CONTROL_PIN, LOW);
  if(command == 'r')
      digitalWrite(RIGHT_CONTROL_PIN, LOW);
  if(command == 'f')
      digitalWrite(FORWARD_CONTROL_PIN, LOW);
  if(command == 'b')
      digitalWrite(BACKWARD_CONTROL_PIN, LOW);

  delay(100);
}


void loop() {
  char command = 0;
  while(device_armed == 0)
  {
    command = get_input();
    if(command != 'A')
    {
       Serial.print("-->");
       Serial.print(command);
    }
    if(command == ARM_COMMAND)
    {
      device_armed = 1;
      Serial.print("ARMED");
      break;
    }
  }

  command = get_input();
  if(command != 'A')
  {
      current_command = command;
  }

  control_car(current_command);
}








