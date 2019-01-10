/*
 * @Author:             Bruno F.
 * @Date:               July 20, 2017
 * @Last Modified by:   Bruno F.
 * @Last Modified time: Jan 10, 2019
 */

#ifndef MEMORY_H
#define MEMORY_H

#include "Arduino.h"
#include <EEPROM.h>

#define ADDRMODE 0
#define ADDRRED 1
#define ADDRGREEN 2
#define ADDRBLUE 3
#define ADDRSPEED 4
#define ADDRLED 5
#define ADDRBRIGHT 6

/**
 * @brief 
 * Data to be load and save for the proper functionning
 */
struct Data
{
    byte mode;
    byte red;
    byte green;
    byte blue;
    byte speed;
    byte led;
    byte brightness;
};

/**
 * @brief
 * Helper class to save and load data in EEPROM
 */
class MEMORY
{
    public:
        /**
         * @brief Save data in EEPROM
         * 
         * @param data 
         */
        void saveState(Data *data);
        
        /**
         * @brief Load data from EEPROM
         * 
         * @param data 
         */
        void loadState(Data *data);
};

#endif