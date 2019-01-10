#include "ble.h"

bool Ble::readBuffer(Data *data)
{
    if (available()) {
        readBytes(buff, 6);

        data->mode       = buff[0];
        data->red        = buff[1];
        data->green      = buff[2];
        data->blue       = buff[3];
        data->speed      = buff[4];
        data->led        = buff[5];
        data->brightness = buff[6];
        return true;
    }

    return false;
}