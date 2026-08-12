#include "Buzzer.h"

#define BUZ_PIN 14

void buz_init()
{
    pinMode(BUZ_PIN, OUTPUT);
    digitalWrite(BUZ_PIN, LOW);
}

void buz_state(bool buz_state)
{
    digitalWrite(BUZ_PIN, buz_state);
}

void buz_squeak()
{
    for(int i = 0; i < 3; i++)
    {
        buz_state(1);
        delay(500);
        buz_state(0);
        delay(500);
    }
}
