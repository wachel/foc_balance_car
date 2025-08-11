#include "test_as5600.h"
#include <Wire.h>
#include <HardwareSerial.h>
#include <stdint-gcc.h>

#define AS5600_ADDR 0x36  // AS5600 I2C地址

void TestAS5600::Init() {
  Serial.begin(115200);
  Wire.begin();  // 初始化I2C，ESP32默认SDA=21, SCL=22
}

uint16_t readRawAngle() {
  Wire.beginTransmission(AS5600_ADDR);
  Wire.write(0x0C);  // 角度寄存器高字节地址
  Wire.endTransmission(false);
  
  Wire.requestFrom(AS5600_ADDR, 2);
  if (Wire.available() == 2) {
    uint8_t highByte = Wire.read();
    uint8_t lowByte = Wire.read();
    uint16_t angle = ((uint16_t)highByte << 8) | lowByte;
    return angle & 0x0FFF;  // 12位角度值
  }
  return 0;
}

void TestAS5600::Update() {
  uint16_t rawAngle = readRawAngle();
  float angleDegrees = (rawAngle * 360.0) / 4096.0;

  // 将角度转换为字符串，保留两位小数
  String angleStr = String(angleDegrees, 2);

  Serial.print("Raw Angle: ");
  Serial.print(rawAngle);
  Serial.print("  Angle: ");
  Serial.print(angleStr);
  Serial.println(" degrees");

  delay(500);
}