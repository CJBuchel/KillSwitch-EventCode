#include "Robot5333.h"
#include "ControlMap.h"
#include "strategy/MPStrategy.h"
#include "RobotMap.h"

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

  //cargo = new Cargo(6,11,8);

  xbox1 = new frc::XboxController(0);

  FlipperSRX1 = new curtinfrc::TalonSrx(6);
  FlipperSRX2 = new curtinfrc::TalonSrx(11);

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


  boxIntake = new BoxIntake(robotmap.boxIntake.config);
  boxIntake->SetDefault(std::make_shared<BoxIntakeManualStrategy>(*boxIntake, robotmap.contGroup));
  boxIntake->StartLoop(50);

  StrategyController::Register(drivetrain);
  StrategyController::Register(beElevator);
  StrategyController::Register(boxIntake);


  NTProvider::Register(&robotmap.controlSystem.pressureSensor);

  NTProvider::Register(drivetrain);
  NTProvider::Register(beElevator);
  NTProvider::Register(boxIntake);
}

static bool goalExtend = actuators::kReverse;
static bool goalGrasp = actuators::kForward;

void Robot::RobotPeriodic() {
  double dt = Timer::GetFPGATimestamp() - lastTimestamp;
  lastTimestamp = Timer::GetFPGATimestamp();
  robotmap.contGroup.Update(); // update selectors, etc. [OPTIONAL]



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

  if (robotmap.contGroup.Get(ControlMap::raiseFlipper)) {
    //
  }

  if (xbox1->GetYButton()) {
    FlipperSRX1->Set(0.3);
  } else if (xbox1->GetAButton()) {
    FlipperSRX2->Set(-0.3);
  }
  
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
