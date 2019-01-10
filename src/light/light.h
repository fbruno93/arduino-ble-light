/*
 * @Author:             Bruno F.
 * @Date:               July 20, 2017
 * @Last Modified by:   Bruno F.
 * @Last Modified time: Jan 10, 2019
 */

#ifndef Light_h
#define Light_h

#define NUMPIXELS   12

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

/**
 * @brief 
 * Led Pattern display 
 */
enum Mode {
  Color = 0,
  Multi,
  Blink,
  Counter,
  Snake,
  Stop,
  Wheel
};

/**
 * @brief 
 * Class contains all pattern led display (Ring NEOPixels) 
 */
class Light
{
  public:
    /**
     * @brief Construct a new Light object
     * 
     * @param pin noepixel pin
     */
    Light(byte pin);

    /**
     * @brief Display wheel of color
     * 
     * @param speed Time (in ms) between two display
     */
    void colorWheel(int speed);

    /**
     * @brief Change color each {speed}ms
     * 
     * @param speed Time (in ms) between two display
     */
    void multi(int speed);

    /**
     * @brief Blink one color
     * 
     * @param r Value for red color
     * @param g Value for green color
     * @param b Value for blue color
     * @param speed Time (in ms) between two display
     */
    void blinking(int r, int g, int b, int speed);

    /**
     * @brief Switch off one led each {total}/12
     * 
     * @param r Value for red color
     * @param g Value for green color
     * @param b Value for blue color
     * @param total 
     */
    void counter(int r, int g, int b, int total);

    /**
     * @brief Display a colored snake
     * 
     * @param r Value for red color
     * @param g Value for green color
     * @param b Value for blue color
     * @param leds Number of led to switch on
     * @param speed Time (in ms) between two display
     */
    void snake(int r, int g, int b, int leds, int speed);

    /**
     * @brief Display one color 
     * 
     * @param r Value for red color
     * @param g Value for green color
     * @param b Value for blue color
     */
    void color(int r, int g, int b);

    /**
     * @brief Keep leds in current state
     */
    void stoping();

    /**
     * @brief Set the Brightness attribute
     * 
     * @param brightness Value for brightness led [0;255]
     */
    void setBrightness(int brightness);

    /**
     * @brief 
     * Reset lights and time
     */
    void resetCounter();

  private:

    // Pointer of NEOPixel
    Adafruit_NeoPixel pixels; 
    
    // number of led on [use for chrono mode]
    byte ligth_on;      

    // index :) 
    int j = 0;          
    
    // use to compare an other time
    long last_time;     
    
    // Two-dimensional array representing 360 degree color
    int arr[12][3] = {  
        {255, 000, 000},
        {255, 128, 000},
        {255, 255, 000},
        {128, 255, 000},
        {000, 255, 000},
        {000, 255, 128},
        {000, 255, 255},
        {000, 128, 255},
        {000, 000, 255},
        {128, 000, 255},
        {255, 000, 255},
        {255, 000, 128}
    };
};

#endif