#include <TC77.h>

void TC77::begin() {
    pinMode(_pin_data, INPUT);
    pinMode(_pin_clock, OUTPUT);
    pinMode(_pin_cs, OUTPUT);
    digitalWrite(_pin_cs, HIGH);
    delay(100);
    this->wake();
}

float TC77::read() {
    float temp = 0;
    uint8_t bh, bl;
    int16_t tbin = 0;
    digitalWrite(_pin_cs, LOW);
    bh = shiftIn(_pin_data, _pin_clock, MSBFIRST);
    bl = shiftIn(_pin_data, _pin_clock, MSBFIRST);
    digitalWrite(_pin_cs, HIGH);
    tbin = (bh << 8) | bl;
    tbin /= 8; // Important to divide, not shift, since it then preserves the sign

    temp = (float)tbin * 0.0625;
    return temp;
}

uint16_t TC77::readRaw() {
    uint8_t bh, bl;
    int16_t tbin = 0;
    digitalWrite(_pin_cs, LOW);
    bh = shiftIn(_pin_data, _pin_clock, MSBFIRST);
    bl = shiftIn(_pin_data, _pin_clock, MSBFIRST);
    digitalWrite(_pin_cs, HIGH);
    tbin = (bh << 8) | bl;
    return tbin;
}

void TC77::sleep() {
    digitalWrite(_pin_cs, LOW);
    shiftIn(_pin_data, _pin_clock, MSBFIRST);
    shiftIn(_pin_data, _pin_clock, MSBFIRST);
    shiftOut(_pin_data, _pin_clock, 0xFF, MSBFIRST);
    shiftOut(_pin_data, _pin_clock, 0xFF, MSBFIRST);
    shiftIn(_pin_data, _pin_clock, MSBFIRST);
    shiftIn(_pin_data, _pin_clock, MSBFIRST);
    shiftOut(_pin_data, _pin_clock, 0xFF, MSBFIRST);
    shiftOut(_pin_data, _pin_clock, 0xFF, MSBFIRST);
    digitalWrite(_pin_cs, HIGH);
}

void TC77::wake() {
    digitalWrite(_pin_cs, LOW);
    shiftIn(_pin_data, _pin_clock, MSBFIRST);
    shiftIn(_pin_data, _pin_clock, MSBFIRST);
    shiftOut(_pin_data, _pin_clock, 0x00, MSBFIRST);
    shiftOut(_pin_data, _pin_clock, 0x00, MSBFIRST);
    shiftIn(_pin_data, _pin_clock, MSBFIRST);
    shiftIn(_pin_data, _pin_clock, MSBFIRST);
    shiftOut(_pin_data, _pin_clock, 0x00, MSBFIRST);
    shiftOut(_pin_data, _pin_clock, 0x00, MSBFIRST);
    digitalWrite(_pin_cs, HIGH);
}


