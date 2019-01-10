#include "app.h"

App::App()
{
    light = new Light(PIN);
    ble = new Ble(RX, TX);
}

void App::setup()
{
    ble->begin(9600);
    memory.loadState(&data);
    light->setBrightness(data.brightness);
}

void App::loop()
{
    if (ble->readBuffer(&data) == true) {
        memory.saveState(&data);
        light->resetCounter();
    }

    switch(data.mode) {
        case Mode::Color:
            light->color(data.red, data.green, data.blue);
        break;
        case Mode::Multi:
            light->multi(data.speed);
        break;
        case Mode::Blink:
            light->blinking(data.red, data.green, data.blue, data.speed);
        break;
        case Mode::Counter:
            light->counter(data.red, data.green, data.blue, data.speed);
        break;
        case Mode::Snake:
            light->snake(
                data.red, data.green, data.blue, data.led, data.speed
            );
        break;
        case Mode::Stop:
            light->stoping();
        break;
        case Mode::Wheel:
            light->colorWheel(data.speed);
        break;
    }
}