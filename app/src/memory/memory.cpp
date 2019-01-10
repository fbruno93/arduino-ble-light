#include "memory.h"

void MEMORY::saveState(Data *data) {
    EEPROM.write(ADDRMODE, data->mode);
    EEPROM.write(ADDRRED, data->red);
    EEPROM.write(ADDRGREEN, data->green);
    EEPROM.write(ADDRBLUE, data->blue);
    EEPROM.write(ADDRSPEED, data->speed);
    EEPROM.write(ADDRLED, data->led);
    EEPROM.write(ADDRBRIGHT, data->brightness);
}

void MEMORY::loadState(Data *data) {
    data->mode       = EEPROM.read(ADDRMODE);
    data->red        = EEPROM.read(ADDRRED);
    data->green      = EEPROM.read(ADDRGREEN);
    data->blue       = EEPROM.read(ADDRBLUE);
    data->speed      = EEPROM.read(ADDRSPEED);
    data->led        = EEPROM.read(ADDRLED);
    data->brightness = EEPROM.read(ADDRBRIGHT);
}