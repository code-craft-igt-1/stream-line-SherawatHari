#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>

struct SensorData {
    double temperature;
    int pulseRate;
    double spo2;
};

class Processor {
public:
    void processSensorData();
};

#endif // PROCESSOR_H
