#include "sender.h"

#include <iostream>
#include <fstream>
#include <random>
#include <thread>
#include <chrono>
#include <sstream>
#include <iomanip>

// Helper function to round to 2 decimal places
double roundToTwoDecimals(double value) {
    return std::round(value * 100.0) / 100.0;
}

// Generates a random set of sensor readings
SensorData generateSensorData() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> tempDist(36.0, 37.5);
    std::uniform_int_distribution<> pulseDist(60, 100);
    std::uniform_real_distribution<> spo2Dist(95.0, 100.0);

    SensorData data;
    data.temperature = roundToTwoDecimals(tempDist(gen));
    data.pulseRate = pulseDist(gen);
    data.spo2 = roundToTwoDecimals(spo2Dist(gen));

    return data;
}

// Reads sensor data from a file
std::vector<SensorData> readSensorDataFromFile(const std::string& filename) {
    std::vector<SensorData> dataList;
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string tempStr, pulseStr, spo2Str;
            if (std::getline(ss, tempStr, ',') &&
                std::getline(ss, pulseStr, ',') &&
                std::getline(ss, spo2Str)) {
                SensorData data;
                data.temperature = std::stod(tempStr);
                data.pulseRate = std::stoi(pulseStr);
                data.spo2 = std::stod(spo2Str);
                dataList.push_back(data);
            }
        }
        file.close();
    }
    return dataList;
}

// Writes sensor data to a file
void writeSensorDataToFile(const std::vector<SensorData>& dataList,
                           const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& data : dataList) {
            file << std::fixed << std::setprecision(2)
                 << data.temperature << ","
                 << data.pulseRate << ","
                 << data.spo2 << std::endl;
        }
        file.close();
    }
}

// Sends data to console (stdout)
void sendSensorDataToConsole(const std::vector<SensorData>& dataList) {
    for (const auto& data : dataList) {
        std::cout << std::fixed << std::setprecision(2)
                  << data.temperature << ","
                  << data.pulseRate << ","
                  << data.spo2 << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

// Checks if file exists
bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Checks if file is empty
bool isFileEmpty(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    return file.tellg() == 0;
}

int main(int argc, char* argv[]) {
    std::vector<SensorData> sensorDataList;
    std::string filename = (argc > 1) ? argv[1] : "";

    if (filename.empty()) {
        for (int i = 0; i < 50; ++i) {
            sensorDataList.push_back(generateSensorData());
        }
        sendSensorDataToConsole(sensorDataList);
    } else {
        if (!fileExists(filename) || isFileEmpty(filename)) {
            for (int i = 0; i < 50; ++i) {
                sensorDataList.push_back(generateSensorData());
            }
            writeSensorDataToFile(sensorDataList, filename);
            std::cout << "Empty file provided. Generated data has been written to " 
                      << filename << "." << std::endl;
        } else {
            sensorDataList = readSensorDataFromFile(filename);
            sendSensorDataToConsole(sensorDataList);
        }
    }

    return 0;
}
