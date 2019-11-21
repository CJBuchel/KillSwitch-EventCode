#pragma once

#include <frc/SpeedControllerGroup.h>
#include <frc/Spark.h>
#include <frc/PowerDistributionPanel.h>

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

#include "control/PIDController.h"
#include "MotionProfiling.h"
// #include "strategy/MPStrategy.h"

#include "ControlMap.h"

#include "Drivetrain.h"
#include "Elevator.h"
#include "HatchIntake.h"
#include "BoxIntake.h"

struct RobotMap {
  curtinfrc::controllers::XboxController xbox{0};
  //curtinfrc::controllers::Joystick joy1{ 0 }; // Driver
  curtinfrc::controllers::Joystick joy2{ 1 }; // Co-Driver

  curtinfrc::controllers::SmartControllerGroup contGroup{ xbox, joy2 };

  // frc::PowerDistributionPanel pdp{0};

  struct DriveTrain {
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
    curtinfrc::PathfinderGains gainsPathfinder{ "Drivetrain Pathfinder", 24.0, 0, 1.5, 0.36, 0.08, 12.0 / 90.0 };    // PIDVAG

    curtinfrc::DrivetrainConfig config{ leftGearbox, rightGearbox, &gyro, 0.71, 0.71, 0.0762, 50 };
    curtinfrc::control::PIDGains gainsVelocity{ "Drivetrain Velocity", 1 };
  };

  DriveTrain drivetrain;


  struct Elevator {
    curtinfrc::VictorSpx liftSpx1{ 12 };// not needed for 5663
    curtinfrc::TalonSrx liftSrx1{ 6 };
    curtinfrc::TalonSrx liftSrx2{ 11 };
    curtinfrc::VictorSpx liftSpx2{ 13 }; // not needed for 5663
    curtinfrc::actuators::MotorVoltageController liftMotors = curtinfrc::actuators::MotorVoltageController::Group(liftSpx1, liftSrx1, liftSrx2, liftSpx2);

    curtinfrc::sensors::DigitalEncoder liftEncoder{ 2, 3, 2048 };
    curtinfrc::Gearbox elevatorGearbox{ &liftMotors, &liftEncoder, 15.79, curtinfrc::physics::DcMotor::m775pro() * 4 };

    curtinfrc::sensors::LimitSwitch bottomLimit{9, true};

    curtinfrc::control::PIDGains lower{ "Lower Elevator", 30.0, 0.025, 1.5 };
    // curtinfrc::control::PIDGains upper{ "Upper Elevator", 1 };


    curtinfrc::ElevatorConfig config{ elevatorGearbox, nullptr, &bottomLimit, 2.1, 30 / 1000.0, 20, "beElevator" };

    Elevator() {
      liftSpx1.SetUpdateRate(200);
      liftSrx1.SetUpdateRate(200);
      liftSrx2.SetUpdateRate(200);
      liftSpx2.SetUpdateRate(200);
    }
  };

  Elevator lift;

  struct SideHatchIntake {
    // const int forward = 115;
    // const int reverse = 5;

    // curtinfrc::actuators::BinaryServo servo{ 0, forward, reverse };
    curtinfrc::actuators::DoubleSolenoid graspSolenoid{ 2, 4, 5, 0.2 };
    curtinfrc::actuators::DoubleSolenoid extendSolenoid{ 2, 6, 7, 0.7 };

    HatchIntakeConfig config{ graspSolenoid, extendSolenoid, "Demogorgon" };
  };

  SideHatchIntake sideHatchIntake;

  // struct FrontHatchIntake {
  //   curtinfrc::actuators::DoubleSolenoid manipulatorSolenoid{ 2, 3, 2, curtinfrc::actuators::DoubleSolenoid::StandardActuationTime }; // eject
  //   curtinfrc::actuators::DoubleSolenoid solenoid{ 2, 0, 1, curtinfrc::actuators::DoubleSolenoid::StandardActuationTime }; // deploy

  //   HatchIntakeConfig config{ manipulatorSolenoid, solenoid, "Shin Destroyer" };
  // };

  // FrontHatchIntake frontHatchIntake;


  struct BoxIntake {
    curtinfrc::TalonSrx boxMotor{ 9 };
    curtinfrc::Gearbox boxIntakeGearbox{ &boxMotor, nullptr };
    curtinfrc::actuators::DoubleSolenoid solenoid{ 2, 0, 1, curtinfrc::actuators::DoubleSolenoid::StandardActuationTime };


    BoxIntakeConfig config{ boxIntakeGearbox, solenoid, true };
  };

  BoxIntake boxIntake;


  struct ControlSystem {
    curtinfrc::actuators::Compressor compressor{ 1 };

    curtinfrc::sensors::PressureSensor pressureSensor{ 0 };
    
    
    // vision
    std::shared_ptr<nt::NetworkTable> visionTable = nt::NetworkTableInstance::GetDefault().GetTable("VisionTracking");
    std::shared_ptr<nt::NetworkTable> hatchTable = visionTable->GetSubTable("HatchTracking");
    std::shared_ptr<nt::NetworkTable> tapeTable = visionTable->GetSubTable("TapeTracking");
    
    nt::NetworkTableEntry hatchDistanceEntry  = hatchTable->GetEntry("Hatch Distance"),
                          hatchXoffsetEntry   = hatchTable->GetEntry("Hatch X Offset"),
                          hatchYoffsetEntry   = hatchTable->GetEntry("Hatch Y Offset"),
                          tapeDistanceEntry   = tapeTable->GetEntry("Distance"),
                          tapeAngleEntry      = tapeTable->GetEntry("Angle"),
                          tapeTargetEntry     = tapeTable->GetEntry("Target");
  };

  ControlSystem controlSystem;
};
