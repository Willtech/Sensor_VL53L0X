
#include "Adafruit_VL53L0X.h"
#include <AiEsp32RotaryEncoderNumberSelector.h>
#include <AiEsp32RotaryEncoder.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();


#define ROTARY_ENCODER_A_PIN D12
#define ROTARY_ENCODER_B_PIN D13
#define ROTARY_ENCODER_BUTTON_PIN D14
#define ROTARY_ENCODER_STEPS 4

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, -1, ROTARY_ENCODER_STEPS);

void IRAM_ATTR readEncoderISR()
{
    rotaryEncoder.readEncoder_ISR();
}

int Read_delay=0;
int Off_delay=0;

void setup() {

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D3, OUTPUT);
  
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 

    // pinMode(ROTARY_ENCODER_A_PIN, INPUT_PULLUP);
    // pinMode(ROTARY_ENCODER_B_PIN, INPUT_PULLUP);
    Serial.begin(115200);
    rotaryEncoder.areEncoderPinsPulldownforEsp32=false;
    rotaryEncoder.begin();
    rotaryEncoder.setup(readEncoderISR);
    rotaryEncoder.setBoundaries(0, 1000, false); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
    rotaryEncoder.setAcceleration(250);
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
   
  }

  if (measure.RangeMilliMeter < 500) { // If it sense

    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(D3, HIGH);
    Off_delay=millis()+10000+(Read_delay*10);

  } else {

    if (millis() > Off_delay) {
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(D3, LOW);  
    }
    
  }

      if (rotaryEncoder.encoderChanged())
    {
        Read_delay=rotaryEncoder.readEncoder();
        Serial.println(Read_delay);
        Off_delay=millis()+10000+(Read_delay*10);
        
    }
    if (rotaryEncoder.isEncoderButtonClicked())
    {
        Serial.println("button pressed");
    }
  
  delay(100);
}
