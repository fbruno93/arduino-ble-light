/*
 * @Author:             Bruno F.
 * @Date:               July 20, 2017
 * @Last Modified by:   Bruno F.
 * @Last Modified time: Jan 10, 2019
 */

#ifndef BLE_h
#define BLE_h

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "../memory/memory.h"

// UUID 0xB2F0
// CHAR 0xB2F1

/**
 * @brief 
 * Helper class to read ble buffer 
 */
class Ble: public SoftwareSerial
{
    public:
        /**
         * @brief Construct a new Ble object
         * 
         * @param rx 
         * @param tx 
         */
        Ble(int rx, int tx) : SoftwareSerial(rx, tx) {}

        /**
         * @brief Read data from ble module
         * 
         * @param data 
         * @return true If data has been readden
         * @return false If no data has readden
         */
        bool readBuffer(Data *data);

    private:
        // Recievied data
        byte buff[7];   
};

#endif