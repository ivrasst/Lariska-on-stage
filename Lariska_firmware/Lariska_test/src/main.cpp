#include <Arduino.h>
#include <argviz.h>

// #include "VoltageSens.h"
#include "VelEst.h"
#include "Motor.h"
#include "Encoder.h"
#include "ServoMotor.h"
#include "Sonar.h"
/*pins
Motor
Encoder
Sonar
*/

SCREEN(volts,
       {
          //  ROW("Vel : %d", int(ve_get_w_est_f() * 1000));
          ROW("Enc : %d", int(enc_phi));
       })

void setup() {
  Serial.begin(115200);
  ve_init();
  m_init();
  enc_init();
  

  argviz_init(Serial);
  argviz_registerScreen(0, volts);
  argviz_start();

}

void loop() {
  static uint32_t timer = micros();
  while (micros() - timer < Ts_us)
    ;
  timer = micros();

  enc_tick();
}