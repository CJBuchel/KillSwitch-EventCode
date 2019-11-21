#pragma once

#include "Drivetrain.h"

#include "strategy/Strategy.h"
#include "Elevator.h"
#include "controllers/CurtinControllers.h"
#include "control/PIDController.h"

class BaseDrivetrainTeleopStrategy : public curtinfrc::Strategy {
 public:
  BaseDrivetrainTeleopStrategy(std::string name, curtinfrc::Drivetrain &drive, curtinfrc::controllers::SmartControllerGroup &contGroup);

 protected:
  curtinfrc::Drivetrain &_drivetrain;
  curtinfrc::controllers::SmartControllerGroup &_contGroup;
};

class DrivetrainManualStrategy : public BaseDrivetrainTeleopStrategy {
 public:
  DrivetrainManualStrategy(curtinfrc::Drivetrain &drive, curtinfrc::Elevator &elevator, curtinfrc::controllers::SmartControllerGroup &contGroup);

  void OnUpdate(double dt) override;

 private:
  curtinfrc::Elevator &_elevator;
  curtinfrc::Toggle _invertedToggle;
};
