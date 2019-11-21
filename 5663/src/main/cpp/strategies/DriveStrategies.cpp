#include "strategies/DriveStrategies.h"

#include <cmath>

#include "ControlMap.h"

using namespace curtinfrc;
using namespace curtinfrc::controllers;

BaseDrivetrainTeleopStrategy::BaseDrivetrainTeleopStrategy(std::string name, Drivetrain &drivetrain, SmartControllerGroup &contGroup)
    : Strategy(name), _drivetrain(drivetrain), _contGroup(contGroup) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
} 

DrivetrainManualStrategy::DrivetrainManualStrategy(Drivetrain &drivetrain, Elevator &elevator, SmartControllerGroup &contGroup) : BaseDrivetrainTeleopStrategy("Drivetrain Manual", drivetrain, contGroup), _elevator(elevator) { }

void DrivetrainManualStrategy::OnUpdate(double dt) {
  double joyForward = 0, joyTurn = 0;
  
  if (_contGroup.Get(ControlMap::chargeForward)) {
    joyForward = 1;
    joyTurn = 0;
  } else {
    if (!_contGroup.Get(ControlMap::holdMovement)) {
      joyForward = (_contGroup.Get(ControlMap::leftAxis) + _contGroup.Get(ControlMap::rightAxis)) / 2 * ControlMap::drivetrainForwardThrottle;
      joyForward *= std::abs(joyForward);
    }

    joyTurn = (_contGroup.Get(ControlMap::leftAxis) - _contGroup.Get(ControlMap::rightAxis)) / 2 * ControlMap::drivetrainTurnThrottle;
    // joyTurn *= abs(joyTurn);
  }

  if (_elevator.GetHeight() > ControlMap::liftSetpointMiddle2 + 0.2) {
    joyForward *= 0.55;
    joyTurn *= 0.55;
  }

  double leftSpeed = joyForward + joyTurn;
  double rightSpeed = joyForward - joyTurn;

  if (_invertedToggle.Update(_contGroup.Get(ControlMap::reverseDrivetrain)))
    _drivetrain.SetInverted(!_drivetrain.GetInverted());

  _drivetrain.Set(leftSpeed, rightSpeed);
}
