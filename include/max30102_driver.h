#ifndef MAX30102_DRIVER_H
#define MAX30102_DRIVER_H

#include <Arduino.h>
#include <Wire.h>
#include "MAX30105.h"
#include "config.h"

class MAX30102Driver {
public:
    MAX30102Driver();
    bool begin();
    bool readSample(PPGPacket &packet);
    bool isConnected();

    // Dinamis Konfigurasi Sample Rate dari Web
    bool setSampleRate(uint16_t sampleRate, uint8_t sampleAverage = 1);
    uint16_t getSampleRate() const { return currentSampleRate; }
    uint8_t getSampleAverage() const { return currentSampleAverage; }

    // Kalibrasi / Kontrol LED
    void setLedPower(uint8_t redPower, uint8_t irPower);
    void reset();

private:
    MAX30105 sensor;
    bool connected;
    uint16_t currentSampleRate;
    uint8_t currentSampleAverage;

    // Filter DC Removal (High Pass ~0.5Hz)
    float dc_ir;
    float dc_red;
    float alpha_dc;

    // Filter Noise Removal (Low Pass ~6.0Hz)
    float lp_ir;
    float lp_red;
    float alpha_lp;
};

extern MAX30102Driver ppgSensor;

#endif // MAX30102_DRIVER_H
