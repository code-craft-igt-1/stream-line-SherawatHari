#include "../include/processor.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <iomanip>

void Processor::processSensorData() {
    std::string line;
    double tempSum = 0.0, spo2Sum = 0.0;
    int pulseSum = 0, count = 0;
    double tempMin = std::numeric_limits<double>::max();
    double tempMax = std::numeric_limits<double>::lowest();
    int pulseMin = std::numeric_limits<int>::max();
    int pulseMax = std::numeric_limits<int>::lowest();
    double spo2Min = std::numeric_limits<double>::max();
    double spo2Max = std::numeric_limits<double>::lowest();

    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        SensorData data;
        std::string tempStr, pulseStr, spo2Str;

        if (std::getline(ss, tempStr, ',') &&
            std::getline(ss, pulseStr, ',') &&
            std::getline(ss, spo2Str)) {
            data.temperature = std::stod(tempStr);
            data.pulseRate = std::stoi(pulseStr);
            data.spo2 = std::stod(spo2Str);

            // Update sums and counts
            tempSum += data.temperature;
            pulseSum += data.pulseRate;
            spo2Sum += data.spo2;
            count++;

            // Update min and max values
            tempMin = std::min(tempMin, data.temperature);
            tempMax = std::max(tempMax, data.temperature);
            pulseMin = std::min(pulseMin, data.pulseRate);
            pulseMax = std::max(pulseMax, data.pulseRate);
            spo2Min = std::min(spo2Min, data.spo2);
            spo2Max = std::max(spo2Max, data.spo2);
        }
    }

    // Calculate averages
    double tempAvg = (count > 0) ? tempSum / count : 0;
    double spo2Avg = (count > 0) ? spo2Sum / count : 0;
    double pulseAvg = (count > 0) ? static_cast<double>(pulseSum) / count : 0;

    // Output results
    std::cout << "Temperature - Avg: " << std::fixed << std::setprecision(2) << tempAvg 
              << ", Min: " << tempMin 
              << ", Max: " << tempMax << std::endl;
    std::cout << "Pulse Rate - Avg: " << pulseAvg 
              << ", Min: " << pulseMin 
              << ", Max: " << pulseMax << std::endl;
    std::cout << "SpO2 - Avg: " << std::fixed << std::setprecision(2) << spo2Avg 
              << ", Min: " << spo2Min 
              << ", Max: " << spo2Max << std::endl;
}


int main() {
    Processor processor;
    processor.processSensorData();
    return 0;
}
