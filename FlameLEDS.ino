#include <FastLED.h>
#include <Servo.h>

#define NUM_LEDS 20
#define RAY_DELAY 20
#define SERVO_REST 10
#define SERVO_ACTIVE 80


#define LED_PIN1 13
#define LED_PIN2 12
#define BUTTON_PIN 2


// Define the array of leds
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
Servo servo;

int buttonState = 0; 
int servoPosition = 0;


bool didRay = false; // Check if startup ray animation occurred

void setup() { 
    servo.attach(4);
    rotate(SERVO_REST);
    
    FastLED.addLeds<NEOPIXEL, LED_PIN1>(leds1, NUM_LEDS);  // GRB ordering is assumed
    FastLED.addLeds<NEOPIXEL, LED_PIN2>(leds2, NUM_LEDS);  // GRB ordering is assumed
    // initialize the pushbutton pin as an input:
    pinMode(BUTTON_PIN, INPUT);
}

void loop() { 
  buttonState = digitalRead(BUTTON_PIN);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
     trigger();
  } else { 
      untrigger();
  }

}

void trigger()
{
  if(didRay == false)
  {
      ray();
      didRay = true;
      rotate(SERVO_ACTIVE);
  }
  else
  {
      rotate(SERVO_ACTIVE);
      pulse();
  }
}

void untrigger()
{
   rotate(SERVO_REST);
   didRay = false;
   rayclear();
}

void rotate(int position)
{
  servo.write(position);
  servoPosition = position;
}

// Light up all LEDS in a ray effect
void ray()
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
     rgb(i, 255, 49, 0);
     delay(RAY_DELAY);
     FastLED.show();
  }
}

// Clear all LEDS in a trailing ray
void rayclear()
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
     rgb(i, 0, 0, 0);
     delay(RAY_DELAY);
     FastLED.show();
  }
}

// Create a pulsating effect
void pulse()
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
    range(i);
  }
}

// Lights up a LED and surrounding LEDS in a gradient
void range(int i)
{
  delay(20);
  fill(255, 49, 0);
  rgb(i - 2, 255, 29, 0);
  rgb(i - 2, 255, 19, 0);
  rgb(i, 255, 9, 0);
  rgb(i + 1, 255, 19, 0);
  rgb(i + 2, 255, 29, 0);
  FastLED.show();
}

// Lights up the LED in both strips
void rgb(int i, int R, int G, int B)
{
 leds1[i].setRGB(R, G, B);
 leds2[i].setRGB(R, G, B);
}

void fill(int R, int G, int B)
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
      rgb(i, R, G, B);
  }
    FastLED.show();
}

// Clear all LEDS
void clear()
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
      leds1[i] = CRGB::Black;
      leds2[i] = CRGB::Black;
  }
    FastLED.show();
}
