#include "States.h"
#include "Motor.h"
#include "Dist.h"
#include "PID.h"
#include "ServoDrive.h"
#include "Buzzer.h"
#include "Sonar.h"
#include "IR.h"


PID pid(0.2, 0, 0, -128, 127);
// PID pid(1.0, 0, 0, -128, 127);

void bow()
{
  /*int d = 200;
  delay(d);
  yaw.write(YAW_MAX);
  delay(d);
  pitch.write(PITCH_MAX);
  delay(d);
  buz_squeak();
  pitch.write(PITCH_ZERO);
  delay(d);
  yaw.write(YAW_ZERO);
  delay(d); 
  delay(500);//*/
  
  const uint16_t servo_delay = 200;
  pitch_set_max();
  delay(servo_delay);
  yaw_set_max();
  delay(servo_delay);

  buz_squeak();

  pitch_set_zero();
  delay(servo_delay);
  yaw_set_zero();
  delay(servo_delay);

  delay(500);
}

void rotate(uint32_t time_rotate)
{
    uint32_t timer = millis();
    while(millis() - timer < time_rotate)
    {
        uint32_t t = millis();
        while (millis() - t < 10)
        ;
        
        motor_set_rpm(150);
        motor_update();

        Serial.println(motor_get_rpm());
        dist_update();

        uint16_t dist = dist_get();
        if (dist == 0) {
            ir_update();
            if(ir_get() > 600){
                servo_set(110);
                pid.reset();
            }
            else{
                servo_set(-110);
                pid.reset();
            }
        } else {
            servo_set(pid.compute(450, dist)); 
        }
    
        // delay(25);
    }
    motor_stop();
}

void whait_trigger()
{
    dist_update();
    uint16_t dist = dist_get();
    // Serial.println(dist);
    while (dist > 260 || dist == 0)
    {
        // Serial.println(dist);
        servo_set_zero();
        delay(25);
        dist_update();
        dist = dist_get();
    }
}

void to_cheburashka()
{
    uint32_t fail_timer = millis();
    son_update();
    uint16_t dist = son_get();
    while ( (dist > 44 || dist == 0) && (millis() - fail_timer < 2500) )
    {
        motor_set_rpm(90);
        servo_set_zero();
        motor_update();
        son_update();
        dist = son_get();
    }
    if (!(dist > 40 || dist == 0))
    {
        buz_state(1);
        delay(100);
        buz_state(0);
    }
    motor_stop();

    // PRE TURN
    const uint16_t servo_delay = 200;
    uint32_t turn_timer = millis();
    servo_set(125);
    delay(servo_delay);

    turn_timer = millis();
    while (millis() - turn_timer < 1000)
    {
        motor_set_rpm(90);
        motor_update();
        delay(25);
    }
    motor_stop();
    
    // servo_set(-125); /// EDITED
    servo_set(-119);
    delay(servo_delay);

    turn_timer = millis();
    while (millis() - turn_timer < 550)
    {
        motor_set_rpm(100);
        motor_update();
        delay(25);
    }
    motor_stop();
//////////////////////////
    servo_set(0);
    delay(servo_delay);

    turn_timer = millis();
    while (millis() - turn_timer < 150)
    {
        motor_set_rpm(100);
        motor_update();
        delay(25);
    }
    motor_stop();
//////////////////////////
    servo_set(0);
    delay(servo_delay);
}

void go_away()
{
    uint32_t timer = millis();
    while(millis() - timer < 2200)
    {
        
        uint32_t t = millis();
        while (millis() - t < 10)
        ;
        servo_set_zero();
        motor_set_rpm(100);
        motor_update();
    }
    motor_stop();
}