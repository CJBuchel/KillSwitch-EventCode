#include "Robot.h"
#include "strategy/MPStrategy.h"

#include <math.h>
#include <iostream>

#include <cameraserver/CameraServer.h>
#include <frc/drive/DifferentialDrive.h>
#include "Drivetrain.h"
#include <frc/PowerDistributionPanel.h>
#include <cmath>
#include "frc/AnalogInput.h"

#include <frc/DriverStation.h>

using namespace frc;
using namespace curtinfrc;
using hand = frc::XboxController::JoystickHand;

double lastTimestamp;

void Robot::RobotInit() {

  xbox1 = new frc::XboxController(0);

  // flipper
  FlipperSRX1 = new curtinfrc::TalonSrx(6);
  FlipperSRX2 = new curtinfrc::TalonSrx(11);

  // left
  DriveMotorLeftSRX = new curtinfrc::TalonSrx(2);
  DriveMotorLeftSPX = new curtinfrc::VictorSpx(3);

  // right
  DriveMotorRightSRX = new curtinfrc::TalonSrx(5);
  DriveMotorRightSPX = new curtinfrc::VictorSpx(4);
}


void Robot::RobotPeriodic() {
  // In periodic mode. Continuous looped code
}

void Robot::DisabledInit() {
  InterruptAll(true);
}

void Robot::AutonomousInit() {
  // Schedule(std::make_shared<PathfinderMPStrategy>(*drivetrain, robotmap.drivetrain.gainsPathfinder, "5333", "d2_bM"));
}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {

  // Driving
  double leftY = -xbox1->GetY(hand::kLeftHand);
  double rightY = xbox1->GetY(hand::kRightHand);
  if (leftY > 0.005) {
    DriveMotorLeftSRX->Set(leftY);
    DriveMotorLeftSPX->Set(leftY);
  } else if (leftY < -0.005) {
    DriveMotorLeftSRX->Set(leftY);
    DriveMotorLeftSPX->Set(leftY);
  }
  if (rightY > 0.005) {
    DriveMotorRightSRX->Set(rightY);
    DriveMotorRightSPX->Set(rightY);
  } else if (rightY < -0.005) {
    DriveMotorRightSRX->Set(rightY);
    DriveMotorRightSPX->Set(rightY);
  }

  // Flipper

  if (xbox1->GetYButton()) {
    FlipperSRX1->Set(-0.3);
    FlipperSRX2->Set(-0.3);
  } else if (xbox1->GetAButton()) {
    FlipperSRX1->Set(0.3);
    FlipperSRX2->Set(0.3);
  } else {
    FlipperSRX1->Set(0);
    FlipperSRX2->Set(0);
  }

 
  
  
  
  
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}