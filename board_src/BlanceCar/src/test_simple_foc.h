#include <SimpleFOC.h>
#include <Wire.h>


class TestSimpleFoc
{
public:
    void Init();
    void Update();
private:
    MagneticSensorI2C sensor0 = MagneticSensorI2C(AS5600_I2C);
    MagneticSensorI2C sensor1 = MagneticSensorI2C(AS5600_I2C);
};