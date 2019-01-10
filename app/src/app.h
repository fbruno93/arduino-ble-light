/*
 * @Author:             Bruno F.
 * @Date:               July 20, 2017
 * @Last Modified by:   Bruno F.
 * @Last Modified time: Jan 10, 2019
 */

#ifndef APP_H
#define APP_H

#define PIN 6
#define RX  2
#define TX  3

#include "light/light.h"
#include "ble/ble.h"
#include "memory/memory.h"

/**
 * @brief 
 * Arduino app
 */
class App {
    public:
        /**
         * @brief
         * Construct a new App object
         */
        App();

        /**
         * @brief 
         * Embeded app's setup
         */
        void setup();

        /**
         * @brief 
         * embeded app's loop
         */
        void loop();

    private:

        // Light library
        Light *light;
        
        // Memory library
        MEMORY memory;
        
        // Ble module library
        Ble *ble;

        // Structure app data
        Data data;
};

#endif