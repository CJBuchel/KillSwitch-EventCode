#include "TestRobot.h"

#include <actuators/VoltageController.h>

#include <math.h>
#include <iostream>

using namespace frc;
using namespace curtinfrc;

void Robot::RobotInit() {
  xbox = new curtinfrc::controllers::XboxController(0);
  

}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  double leftSpeed = -xbox->GetAxis(1); // L Y axis
  double rightSpeed = -xbox->GetAxis(5); // R Y axis

  
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
