#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

#define MAN 4
#define HAND 5

// Keep track of button state
int MPress = 0;
int MRelease = 0;
int HPress = 0;
int HRelease = 0;

int del = 500;

void setup() 
{
  pinMode(MAN, OUTPUT);
  pinMode(HAND, OUTPUT);
  digitalWrite(MAN, HIGH);
  digitalWrite(HAND, HIGH);
  Serial.begin(250000);    // Set your Serial Monitor is set at 250000
  Dabble.begin(9600);      // This is the baude rate of the HM-10
}

void reset()
{
  MPress = 0;
  MRelease = 0;
  HPress = 0;
  HRelease = 0;
  digitalWrite(MAN, HIGH);
  digitalWrite(HAND,HIGH);  
}

void loop() {
Dabble.processInput();  // This line is crucial in grabbing our data  

  if (GamePad.isSelectPressed()) { reset(); }

  // CIRCLE -> Toggle man
  // SQUARE -> Toggle hand
  // TRIANGLE -> Toggle both
  // CROSS -> Turn off both
  // SELECT -> Turn off both

  if (GamePad.isCirclePressed() || GamePad.isTrianglePressed())       
  {
    digitalWrite(MAN, MPress);
    MRelease = ~MPress;
  }
  if (GamePad.isSquarePressed() || GamePad.isTrianglePressed())       
  {
    digitalWrite(HAND, HPress);
    HRelease = ~HPress;
  }
  if (!GamePad.isCirclePressed() && !GamePad.isTrianglePressed())
  {
    MPress = MRelease;
  }
  if (!GamePad.isSquarePressed() && !GamePad.isTrianglePressed())
  {
    HPress = HRelease;
  }
  if (GamePad.isCrossPressed())
  {
    reset();
  }
}
