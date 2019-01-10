/*
Light.cpp - Library for specific control NEOPixels.
Created by Bruno F. July 20, 2017.
*/

#include "light.h"

Light::Light(byte pin)
{
    pixels = Adafruit_NeoPixel(NUMPIXELS, pin, NEO_GRB + NEO_KHZ800);
    pixels.begin();
    ligth_on = NUMPIXELS;
}

void Light::setBrightness(int brightness)
{
    pixels.setBrightness(brightness);
}

void Light::colorWheel(int speed)
{
    j = (j == NUMPIXELS) ? 0 : (j + 1);

    for (int i = 0 ; i < NUMPIXELS ; i++) {
        int diff = 0;
        if ( i < j) {
            diff = NUMPIXELS - j + i;
        }

        if (i > j) {
            diff = i - j;
        }

        pixels.setPixelColor(i, pixels.Color(arr[diff][0], arr[diff][1], arr[diff][2]));
    }

    pixels.show();
    delay(speed);
}

void Light::multi(int speed)
{
    j = (j == NUMPIXELS) ? 0 : (j + 1);

    for (int i = 0 ; i < NUMPIXELS ; i++) {
        int diff = i + j;
        pixels.setPixelColor(i, pixels.Color(arr[j][0], arr[j][1], arr[j][2]));
    }

    pixels.show();
    delay(speed);
}

void Light::blinking(int r, int g, int b, int tim)
{
    for (int i = 0 ; i < NUMPIXELS ; i++)
        pixels.setPixelColor(i, pixels.Color(r, g, b));

    pixels.show();

    delay(tim);

    for (int i = 0 ; i < NUMPIXELS ; i++)
        pixels.setPixelColor(i, pixels.Color(0,0,2));

    pixels.show();
    delay(tim);
}

void Light::counter(int r, int g, int b, int total)
{
    long current_time = millis();
    int moyen = total / NUMPIXELS;

    if (current_time - last_time > moyen * 1000) {

        for (int i = 0 ; i < ligth_on ; i++)
            pixels.setPixelColor(i, pixels.Color(r,g,b));

        pixels.show();

        for (int i = 11 ; i >= ligth_on ; i--) {
            pixels.setPixelColor(i, pixels.Color(0,0,0));
            pixels.show();
        }

        ligth_on--;
        last_time = millis();
    }

}

void Light::snake(int r, int g, int b, int leds, int speed)
{
    for(int i = 0 ; i < NUMPIXELS ; i++){
        pixels.setPixelColor(i, pixels.Color(r,g,b));

        if (i >= leds)
            pixels.setPixelColor(i - leds, pixels.Color(0,0,0));

        if (i < leds)
            pixels.setPixelColor(NUMPIXELS - leds + i, pixels.Color(0,0,0));

        pixels.show();
        delay(speed);
    }
}

void Light::color(int r, int g, int b)
{
    for(int i = 0 ; i < NUMPIXELS ; i++)
        pixels.setPixelColor(i, pixels.Color(r,g,b));

    pixels.show();
}

void Light::stoping()
{
    byte pxs[NUMPIXELS];

    for (int i = 0 ; i < NUMPIXELS ; i++)
        pxs[i] = pixels.getPixelColor(i);

    for (int i = 0 ; i < NUMPIXELS ; i++)
        pixels.setPixelColor(i, pxs[i]);

    pixels.show();
}

void Light::resetCounter() {
    ligth_on = NUMPIXELS;
    last_time = millis();
}