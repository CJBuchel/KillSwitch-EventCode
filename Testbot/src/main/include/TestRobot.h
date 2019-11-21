#pragma once

#include <frc/Timer.h>
#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Spark.h>
#include <frc/Talon.h>
#include <frc/DoubleSolenoid.h>
#include "controllers/CurtinControllers.h"

#include "CurtinCtre.h"
#include "Gearbox.h"
#include "Drivetrain.h"

#include "CurtinCtre.h"
#include "controllers/CurtinControllers.h"
#include "Gearbox.h"
#include "actuators/BinaryServo.h"
#include "actuators/Compressor.h"
#include "actuators/DoubleSolenoid.h"
#include "actuators/VoltageController.h"
#include "sensors/Encoder.h"
#include "sensors/LimitSwitch.h"
#include "sensors/NavX.h"
#include "sensors/PressureSensor.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;

  curtinfrc::controllers::XboxController *xbox;
  
  curtinfrc::TalonSrx leftSrx{ 2 };
  curtinfrc::VictorSpx leftSpx{ 3 };
  curtinfrc::actuators::MotorVoltageController leftMotors = curtinfrc::actuators::MotorVoltageController::Group(leftSrx, leftSpx);
  curtinfrc::sensors::DigitalEncoder leftEncoder{ 7, 6, 2048 };
  curtinfrc::Gearbox leftGearbox{ &leftMotors, &leftEncoder, 8.45 };

  curtinfrc::TalonSrx rightSrx{ 5 };
  curtinfrc::VictorSpx rightSpx{ 4 };
  curtinfrc::actuators::MotorVoltageController rightMotors = curtinfrc::actuators::MotorVoltageController::Group(rightSrx, rightSpx);
  curtinfrc::sensors::DigitalEncoder rightEncoder{ 4, 5, 2048 };
  curtinfrc::Gearbox rightGearbox{ &rightMotors, &rightEncoder, 8.45 };

  curtinfrc::sensors::NavX navx{frc::SPI::Port::kMXP, 200};
  curtinfrc::sensors::NavXGyro gyro{ navx.Angular(curtinfrc::sensors::AngularAxis::YAW) };
  curtinfrc::sensors::NavXGyro pitchGgyro{ navx.Angular(curtinfrc::sensors::AngularAxis::ROLL) }; // navx is 'sideways';
  curtinfrc::sensors::NavXGyro rollGyro{ navx.Angular(curtinfrc::sensors::AngularAxis::PITCH) };  // pitch <=> roll

  curtinfrc::control::PIDGains gainsFOC{ "Drivetrain FOC", 0.008, 0, 0 };
  curtinfrc::control::PIDGains gainsAlign{ "Drivetrain Align", 0.3, 0, 0.04 };

  curtinfrc::DrivetrainConfig config{ leftGearbox, rightGearbox, &gyro, 0.71, 0.71, 0.0762, 50 };
  curtinfrc::control::PIDGains gainsVelocity{ "Drivetrain Velocity", 1 };
  
};
