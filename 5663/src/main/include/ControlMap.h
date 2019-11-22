#pragma once

#include <vector>

#include "controllers/CurtinControllers.h"

#define N_CONT 3


class ControlMap {
 public:
  static void InitSmartControllerGroup(curtinfrc::controllers::SmartControllerGroup &contGroup);

  // DRIVETRAIN AXIS JOYMAP
  static const curtinfrc::controllers::tAxis leftAxis;
  static const curtinfrc::controllers::tAxis rightAxis;

  static const double axisDeadzone;


  // DRIVETRAIN JOYMAP
  static const std::vector<curtinfrc::controllers::tButton> reverseDrivetrain;   // Toggles the direction of the drivetrain
  static const std::vector<curtinfrc::controllers::tButton> holdMovement;        // Makes the robot 'line up' (0 magnitude but still rotating)
  static const std::vector<curtinfrc::controllers::tButton> chargeForward;

  static const double drivetrainMinThrottle;
  static const double drivetrainForwardThrottle;
  static const double drivetrainTurnThrottle;

  // CargoFlipper JOYMAP
  static const std::vector<curtinfrc::controllers::tButton> raiseFlipper;
  static const std::vector<curtinfrc::controllers::tButton> lowerFlipper;


  // BEELEVATOR JOYMAP
  static const std::vector<curtinfrc::controllers::tButton> raiseLift;
  static const std::vector<curtinfrc::controllers::tButton> lowerLift;

  static const std::vector<curtinfrc::controllers::tButton> liftGoalGround;
  static const std::vector<curtinfrc::controllers::tButton> liftGoalLower1;
  static const std::vector<curtinfrc::controllers::tButton> liftGoalLower2;
  static const std::vector<curtinfrc::controllers::tButton> liftGoalMiddle1;
  static const std::vector<curtinfrc::controllers::tButton> liftGoalMiddle2;
  static const std::vector<curtinfrc::controllers::tButton> liftGoalUpper1;
  static const std::vector<curtinfrc::controllers::tButton> liftGoalUpper2;

  static const double liftSetpointGround; // Exact values need to be tested *
  static const double liftSetpointLower1;
  static const double liftSetpointLower2;
  static const double liftSetpointMiddle1;
  static const double liftSetpointMiddle2;
  static const double liftSetpointUpper1;
  static const double liftSetpointUpper2;


  // HATCH JOYMAP
  static const std::vector<curtinfrc::controllers::tButton> hatchGrab;
  static const std::vector<curtinfrc::controllers::tButton> hatchRelease;
  static const std::vector<curtinfrc::controllers::tButton> hatchStow;
  static const std::vector<curtinfrc::controllers::tButton> hatchToggleEnabled; // Changes the currently enabled hatch intake


  // BOX INTAKE JOYMAP
  static const std::vector<curtinfrc::controllers::tButton> boxIn;
  static const std::vector<curtinfrc::controllers::tButton> boxOut;
  static const std::vector<curtinfrc::controllers::tButton> boxStow;

  static const double boxDeployedThrottle;
  static const double boxStowingThrottle;
  static const double boxStowedThrottle;


  // CONTROLSYSTEM JOYMAP
  static const std::vector<curtinfrc::controllers::tButton> compressorOn;
};
