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


void buz_fin_squeak()
{
    float k = 1.95;
    buz_state(1);
    delay(100*k);
    buz_state(0);
    delay(100*k);

    for(int i = 0; i < 3; i++)
    {
        buz_state(1);
        delay(50*k);
        buz_state(0);
        delay(50*k);
    }
    delay(50*k);

    buz_state(1);
    delay(100*k);
    buz_state(0);
    delay(50*k);

    buz_state(1);
    delay(150*k);
    buz_state(0);
    delay(50*k);

}