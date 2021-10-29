#ifndef HEARTBEAT_H
#define HEARTBEAT_H
#include <Arduino.h>
#endif

class HeartBeat
{
public:
    HeartBeat(int pin);
    void begin();
    void run();
    void ledtoggle();
    void ledoff();
    void ledon();
    void blink(int delay);
    void blinkasync(int delayon, int delayoff);
 
private:
  int _heartbeatpin = 2;
  int _state = 0;
  unsigned long _currentMillis = millis();
  unsigned long _previousMillis = 0;
};

HeartBeat::HeartBeat(int pin)
{
  pinMode( pin , OUTPUT);
  _heartbeatpin = pin;
}

void HeartBeat::begin()
  {
  pinMode( _heartbeatpin , OUTPUT);      
  }

void HeartBeat::run()
  {
  digitalWrite( _heartbeatpin , HIGH);
  delay(500);
  digitalWrite( _heartbeatpin , LOW);
  delay(500);
  }

void HeartBeat::ledtoggle() {                              //toggle led
  digitalWrite( _heartbeatpin , (!_state) ? HIGH : LOW);   //!state because otherwise the led would be inverted
  _state = !_state;                                        //toggle the state function to switch the led state
}

void HeartBeat::ledoff() {                                 //toggle led off
  _state = LOW;                                            //set _state off
  digitalWrite( _heartbeatpin , _state);                   //send _state to pin
}

void HeartBeat::ledon() {                                  //toggle led on
  _state = HIGH;                                           //set _state on
  digitalWrite( _heartbeatpin , _state);                   //send _state to pin
}

void HeartBeat::blink(int delay)                           //blink led
{
    _currentMillis = millis();
    if ( (_currentMillis - _previousMillis) >= delay)
      {
      // save the last time you blinked the LED
      _previousMillis = _currentMillis;
      // toggle LED
      ledtoggle();
    }
}

void HeartBeat::blinkasync(int delayon, int delayoff)
{
    _currentMillis = millis();
    if ( _state == LOW and (_currentMillis - _previousMillis) >= delayon)
      {
      // save the last time you blinked the LED
      _previousMillis = _currentMillis;
      // turn LED on
      ledon();
    }
	else if ( _state == HIGH and (_currentMillis - _previousMillis) >= delayoff)
      {
      // save the last time you blinked the LED
      _previousMillis = _currentMillis;
      // turn LED off
      ledoff();
    }
}
