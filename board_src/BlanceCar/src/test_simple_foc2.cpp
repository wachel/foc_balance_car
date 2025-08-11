#include <SimpleFOC.h>

// magnetic sensor instance - SPI
MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);

const int PolePairsNum = 7;
const int PinA_0 = 15;
const int PinB_0 = 16;
const int PinC_0 = 17;
const int PinEn_0 = 13;

// BLDC motor & driver instance
BLDCMotor motor = BLDCMotor(PolePairsNum);
BLDCDriver3PWM driver = BLDCDriver3PWM(PinA_0, PinB_0, PinC_0, PinEn_0);

// commander interface
Commander command = Commander(Serial);
void onMotor(char* cmd){ command.motor(&motor, cmd); }

void setup_foc2() {
  // monitoring port
  Serial.begin(115200);
  _delay(750);

  Serial.print("setup_foc2\n");
  // enable the debugging output
  SimpleFOCDebug::enable(&Serial);

  // initialise magnetic sensor hardware
  sensor.init();
  // link the motor to the sensor
  motor.linkSensor(&sensor);

  _delay(100);
  Serial.print("setup_foc2 111\n");

  // driver config
  // power supply voltage [V]
  driver.voltage_power_supply = 12;
  driver.init();

  Serial.print("setup_foc2 222\n");

  // link driver
  motor.linkDriver(&driver);

  // set control loop type to be used
  motor.controller = MotionControlType::torque;

  Serial.print("setup_foc2 444\n");

  
  // contoller configuration based on the control type 
  motor.PID_velocity.P = 0.2;
  motor.PID_velocity.I = 20;
  motor.PID_velocity.D = 0;
  // default voltage_power_supply
  motor.voltage_limit = 12;
  motor.KV_rating = 370;

  // velocity low pass filtering time constant
  motor.LPF_velocity.Tf = 0.01;


  Serial.print("setup_foc2 888");

  // angle loop controller
  motor.P_angle.P = 20;
  // angle loop velocity limit
  motor.velocity_limit = 50;

  // use monitoring with serial for motor init
  // comment out if not needed
  motor.useMonitoring(Serial);

  // initialise motor
  motor.init();
  // align encoder and start FOC
  motor.initFOC();

  // set the inital target value
  motor.target = 5;

  // define the motor id
  command.add('A', onMotor, "motor");

  // Run user commands to configure and the motor (find the full command list in docs.simplefoc.com)
  Serial.println(F("Motor commands sketch | Initial motion control > torque/voltage : target 2V."));
  
  _delay(1000);
}

void loop_foc2() {
    // 让电机移动到目标角度
    motor.move(1.07);

    // 运行FOC控制环
    motor.loopFOC();
}