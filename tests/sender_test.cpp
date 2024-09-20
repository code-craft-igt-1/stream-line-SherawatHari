#include "sender.h"
#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>

// Test case for generating sensor data
TEST(SensorDataTest, DataGeneration) {
    SensorData data = generateSensorData();

    EXPECT_GE(data.temperature, 36.0);
    EXPECT_LE(data.temperature, 37.5);
    EXPECT_GE(data.pulseRate, 60);
    EXPECT_LE(data.pulseRate, 100);
    EXPECT_GE(data.spo2, 95.0);
    EXPECT_LE(data.spo2, 100.0);
    EXPECT_EQ(data.temperature, roundToTwoDecimals(data.temperature));
    EXPECT_EQ(data.spo2, roundToTwoDecimals(data.spo2));
}

// Test case for writing and reading from a file
TEST(SensorDataFileTest, WriteAndReadFile) {
    std::string filename = "test_sensor_data.txt";
    std::vector<SensorData> dataList;

    for (int i = 0; i < 50; ++i) {
        dataList.push_back(generateSensorData());
    }

    writeSensorDataToFile(dataList, filename);
    std::vector<SensorData> readDataList = readSensorDataFromFile(filename);

    EXPECT_EQ(dataList.size(), readDataList.size());
    for (size_t i = 0; i < dataList.size(); ++i) {
        EXPECT_EQ(dataList[i].temperature, readDataList[i].temperature);
        EXPECT_EQ(dataList[i].pulseRate, readDataList[i].pulseRate);
        EXPECT_EQ(dataList[i].spo2, readDataList[i].spo2);
    }

    std::remove(filename.c_str());
}

// Test case for handling an empty file
TEST(SensorDataFileTest, EmptyFileHandling) {
    std::string filename = "empty_file.txt";
    std::ofstream file(filename);
    file.close();

    std::vector<SensorData> dataList;
    EXPECT_TRUE(isFileEmpty(filename));

    for (int i = 0; i < 50; ++i) {
        dataList.push_back(generateSensorData());
    }

    writeSensorDataToFile(dataList, filename);
    std::vector<SensorData> readDataList = readSensorDataFromFile(filename);

    EXPECT_EQ(dataList.size(), readDataList.size());
    for (size_t i = 0; i < dataList.size(); ++i) {
        EXPECT_EQ(dataList[i].temperature, readDataList[i].temperature);
        EXPECT_EQ(dataList[i].pulseRate, readDataList[i].pulseRate);
        EXPECT_EQ(dataList[i].spo2, readDataList[i].spo2);
    }

    std::remove(filename.c_str());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
