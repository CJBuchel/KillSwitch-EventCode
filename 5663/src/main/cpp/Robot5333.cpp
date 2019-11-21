#include "Robot5333.h"
#include "ControlMap.h"
#include "strategy/MPStrategy.h"

#include <math.h>
#include <iostream>

#include <cameraserver/CameraServer.h>

#include <frc/DriverStation.h>

using namespace frc;
using namespace curtinfrc;

double lastTimestamp;

void Robot::RobotInit() {
  lastTimestamp = Timer::GetFPGATimestamp();
  ControlMap::InitSmartControllerGroup(robotmap.contGroup);

  auto cameraFront = CameraServer::GetInstance()->StartAutomaticCapture(0);

  cameraFront.SetFPS(30);

  cameraFront.SetResolution(160, 120);

  // Our motors are mounted backwards, but the simulation doesn't know about that.
#ifdef __FRC_ROBORIO__
  robotmap.drivetrain.rightGearbox.transmission->SetInverted(true); 
#else
  robotmap.drivetrain.leftGearbox.transmission->SetInverted(true);
#endif
  robotmap.lift.elevatorGearbox.transmission->SetInverted(true);
  robotmap.drivetrain.leftGearbox.encoder->ZeroEncoder();
  robotmap.drivetrain.rightGearbox.encoder->ZeroEncoder();

  beElevator = new Lift(robotmap.lift.config, robotmap.lift.lower);
  beElevator->SetDefault(std::make_shared<LiftManualStrategy>(*beElevator, robotmap.contGroup));
  beElevator->StartLoop(100);

  drivetrain = new Drivetrain(robotmap.drivetrain.config, robotmap.drivetrain.gainsVelocity);
  drivetrain->SetDefault(std::make_shared<DrivetrainManualStrategy>(*drivetrain, *beElevator, robotmap.contGroup));
  drivetrain->StartLoop(100);

  // sideHatchIntake = new HatchIntake(robotmap.sideHatchIntake.config);
  // sideHatchIntake->SetDefault(std::make_shared<HatchIntakeManualStrategy>(*sideHatchIntake, robotmap.contGroup, true));
  // sideHatchIntake->StartLoop(50);

  // frontHatchIntake = new HatchIntake(robotmap.frontHatchIntake.config);
  // frontHatchIntake->SetDefault(std::make_shared<HatchIntakeManualStrategy>(*frontHatchIntake, robotmap.contGroup, false));
  // frontHatchIntake->StartLoop(50);

  boxIntake = new BoxIntake(robotmap.boxIntake.config);
  boxIntake->SetDefault(std::make_shared<BoxIntakeManualStrategy>(*boxIntake, robotmap.contGroup));
  boxIntake->StartLoop(50);

  StrategyController::Register(drivetrain);
  StrategyController::Register(beElevator);
  // StrategyController::Register(sideHatchIntake);
  // StrategyController::Register(frontHatchIntake);
  StrategyController::Register(boxIntake);


  NTProvider::Register(&robotmap.controlSystem.pressureSensor);

  NTProvider::Register(drivetrain);
  NTProvider::Register(beElevator);
  // NTProvider::Register(sideHatchIntake);
  // NTProvider::Register(frontHatchIntake);
  NTProvider::Register(boxIntake);
}

static bool goalExtend = actuators::kReverse;
static bool goalGrasp = actuators::kForward;

void Robot::RobotPeriodic() {
  double dt = Timer::GetFPGATimestamp() - lastTimestamp;
  lastTimestamp = Timer::GetFPGATimestamp();
  robotmap.contGroup.Update(); // update selectors, etc. [OPTIONAL]



  

  // if (robotmap.contGroup.Get(ControlMap::compressorOn, controllers::Controller::ONRISE)) 
    robotmap.controlSystem.compressor.SetTarget(actuators::BinaryActuatorState::kForward);
  robotmap.controlSystem.compressor.Update(dt);

  StrategyController::Update(dt);
  NTProvider::Update();
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
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
