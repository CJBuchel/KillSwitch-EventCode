#pragma once

#include <frc/Timer.h>
#include <frc/TimedRobot.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Spark.h>
#include <frc/DoubleSolenoid.h>
#include <frc/GenericHID.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableInstance.h>

#include "RobotMap.h"
#include "strategy/StrategyController.h"
#include "NTProvider.h"

#include "Toggle.h"

#include "Drivetrain.h"
#include "Lift.h"
#include "HatchIntake.h"
#include "BoxIntake.h"

#include "strategies/DriveStrategies.h"

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


  RobotMap robotmap;

  curtinfrc::Drivetrain *drivetrain;


  HatchIntake *sideHatchIntake /*, *frontHatchIntake*/;


  BoxIntake *boxIntake;


  Lift *beElevator;
  curtinfrc::Toggle fallToggle;
};
