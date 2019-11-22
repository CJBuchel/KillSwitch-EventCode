#pragma once

#include <frc/Timer.h>
#include <frc/TimedRobot.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Spark.h>
#include <frc/DoubleSolenoid.h>
#include <frc/GenericHID.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableInstance.h>

#include "strategy/StrategyController.h"
#include "NTProvider.h"
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

#include "Toggle.h"

#include "Drivetrain.h"

class Robot : public frc::TimedRobot, protected curtinfrc::StrategyController, protected curtinfrc::NTProvider {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;

  void DisabledInit() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;

  curtinfrc::Drivetrain *drivetrain;

  frc::XboxController *xbox1;

  curtinfrc::TalonSrx *FlipperSRX1, *FlipperSRX2;

  //curtinfrc::TalonSrx *HatchMech;

  curtinfrc::TalonSrx *DriveMotorLeftSRX, *DriveMotorRightSRX;

  curtinfrc::VictorSpx *DriveMotorLeftSPX, *DriveMotorRightSPX;

  bool enableFOC = false;
 
  curtinfrc::Toggle fallToggle;
};
