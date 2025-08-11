#include "test_simple_foc.h"

void TestSimpleFoc::Init(){
    Serial.begin(115200);
    _delay(750);

    Wire.setClock(400000);
    Wire1.setClock(400000);


    // Normally SimpleFOC will call begin for i2c but with esp32 begin() is the only way to set pins!
    // It seems safe to call begin multiple times
    const int sda0 = 21;
    const int scl0 = 22;
    //Wire0 总是使用sda=21, scl=22 引脚，不需要设置

    const int sda1 = 19;
    const int scl1 = 23;
    Wire1.begin(sda1, scl1, (uint32_t)400000); 

    sensor0.init();
    sensor1.init(&Wire1);
}

void TestSimpleFoc::Update()
{
    sensor0.update();
    //sensor1.update();

    _delay(200);
    Serial.print(sensor0.getAngle()); 
    Serial.println();
    //Serial.print(sensor1.getAngle());
    //Serial.println();
}