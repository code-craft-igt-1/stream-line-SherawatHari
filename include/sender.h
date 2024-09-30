#ifndef SENDER_H_
#define SENDER_H_

#include <string>
#include <vector>

struct SensorData {
    double temperature;
    int pulseRate;
    double spo2;
};

double roundToTwoDecimals(double value);

SensorData generateSensorData();

std::vector<SensorData> readSensorDataFromFile(const std::string& filename);

void writeSensorDataToFile(const std::vector<SensorData>& dataList,
                           const std::string& filename);

void sendSensorDataToConsole(const std::vector<SensorData>& dataList);

bool fileExists(const std::string& filename);

bool isFileEmpty(const std::string& filename);

#endif  // SENDER_H_
