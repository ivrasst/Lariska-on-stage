#pragma once
#include <Arduino.h>

#define K_FILTR 0.4

float sharpF()
{
    uint16_t data = analogRead(A3);
    static float dataOld = data;
     
    float out = (data*K_FILTR) + (dataOld*(1-K_FILTR));
    dataOld = data;
    return out;
}

float sharpC()
{
    uint16_t data = analogRead(A0);
    static float dataOld = data;
     
    float out = (data*K_FILTR) + (dataOld*(1-K_FILTR));
    dataOld = out;
    return out;
}

float sharpF_m()
{
    float adc = sharpF();

    if(adc < 60)
        return(1.0);
    
    float dist_m = ( 13000.0/(adc-3.0) ) / 100.0;
    
    return(dist_m);
}

float sharpC_m()
{
    float adc = sharpC();

    if(adc < 60)
        return(1.0);
    
    float dist_m = ( 13000.0/(adc-3.0) ) / 100.0;
    
    return(dist_m);
}
