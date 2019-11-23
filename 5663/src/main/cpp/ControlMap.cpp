#include "ControlMap.h"

using namespace curtinfrc::controllers;

void ControlMap::InitSmartControllerGroup(SmartControllerGroup &contGroup) {
  // Xbox (0) Rebinds
  const tAxis lowerElevator = { 1, XboxController::kLeftThrottle }, raiseElevator = { 1, XboxController::kRightThrottle };
  tButton lowerElevatorButton = { 1, 28 }, raiseElevatorButton = { 1, 27 };

  contGroup.GetController(lowerElevator.cont).Map(lowerElevator, lowerElevatorButton);
  contGroup.GetController(raiseElevator.cont).Map(raiseElevator, raiseElevatorButton);
}

// DRIVETRAIN AXIS JOYMAP
const tAxis ControlMap::leftAxis{ 1, XboxController::kLeftYAxis };
const tAxis ControlMap::rightAxis{ 1, XboxController::kRightYAxis };

// DRIVETRAIN JOYMAP
const std::vector<tButton> ControlMap::reverseDrivetrain{  };   // Toggles the direction of the drivetrain
const std::vector<tButton> ControlMap::holdMovement{  };        // Makes the robot 'line up' (0 magnitude but still rotating)
const std::vector<tButton> ControlMap::chargeForward{  };

const double ControlMap::drivetrainMinThrottle       = 0.3;
const double ControlMap::drivetrainForwardThrottle   = -0.9;
const double ControlMap::drivetrainTurnThrottle      = -0.6;

// CargoFlipper JOYMAP
const std::vector<tButton> ControlMap::raiseFlipper{ { 1, XboxController::kY } };
const std::vector<tButton> ControlMap::lowerFlipper{ { 1, XboxController::kA } };

// BEELEVATOR JOYMAP
const std::vector<tButton> ControlMap::raiseLift{ { 2, XboxController::kA }, { 2, 20 } };
const std::vector<tButton> ControlMap::lowerLift{ { 2, XboxController::kB } };

const std::vector<tButton> ControlMap::liftGoalGround{ { 1, 28 } };
const std::vector<tButton> ControlMap::liftGoalLower1{ { 2, 11 } };
const std::vector<tButton> ControlMap::liftGoalLower2{ { 2, 12 } };
const std::vector<tButton> ControlMap::liftGoalMiddle1{ { 2, 9 } };
const std::vector<tButton> ControlMap::liftGoalMiddle2{ { 2, 10 } };
const std::vector<tButton> ControlMap::liftGoalUpper1{ { 2, 7 } };
const std::vector<tButton> ControlMap::liftGoalUpper2{ { 2, 8 } };

const double ControlMap::liftSetpointGround = 0.08;                                     // Exact values need to be tested
const double ControlMap::liftSetpointLower1 = 0.46;
const double ControlMap::liftSetpointLower2 = 0.68;
const double ControlMap::liftSetpointMiddle1 = 1.18;
const double ControlMap::liftSetpointMiddle2 = 1.39;
const double ControlMap::liftSetpointUpper1 = 1.89;
const double ControlMap::liftSetpointUpper2 = 1.7;

// HATCH JOYMAP
const std::vector<tButton> ControlMap::hatchGrab{ { 1, XboxController::kY } };
const std::vector<tButton> ControlMap::hatchRelease{ { 1, XboxController::kA } };
const std::vector<tButton> ControlMap::hatchStow{ { 1, XboxController::kBumperRight } };
const std::vector<tButton> ControlMap::hatchToggleEnabled{ { 1, XboxController::kStart } }; // Changes the currently enabled hatch intake



// BOX INTAKE JOYMAP
const std::vector<tButton> ControlMap::boxIn{ { 1, XboxController::kX } };   // reversed
const std::vector<tButton> ControlMap::boxOut{ { 1, XboxController::kB } };  // reversed
const std::vector<tButton> ControlMap::boxStow{ { 1, XboxController::kBumperLeft } };

const double ControlMap::boxDeployedThrottle = 0.6;
const double ControlMap::boxStowingThrottle = 0.4;
const double ControlMap::boxStowedThrottle = 0.2;


// CONTROLSYSTEM JOYMAP
// const std::vector<tButton> ControlMap::compressorOn{ { 1, XboxController::kBack } };
