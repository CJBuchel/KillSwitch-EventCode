#pragma once

#include "Gearbox.h"
#include "control/PIDController.h"
#include "devices/StateDevice.h"
#include "control/MotorFilters.h"
#include "Usage.h"


struct FlipperConfig {
  curtinfrc::Gearbox &gearbox;

    sensors::BinarySensor *limitSensorTop;
    sensors::BinarySensor *limitSensorBottom;

  std::string name = "<Flipper>";
};

enum class FlipperState { kStationary = 0, kMoving, kZeroing, kManual };
class Flipper : public curtinfrc::devices::StateDevice<FlipperState> {
   public:
    Flipper(FlipperConfig config, curtinfrc::control::PIDGains gain) : StateDevice(config.name), _config(config), _gain(gain), _controller(gain), _current_filter(-60.0, 120.0, config.gearbox) {};

    virtual std::string GetStateString() final;

    void SetManual(double power);
    void SetSetpoint(double setpoint);
    void SetZeroing();
    void SetHold();

    double GetFeedforward();

    double GetSetpoint(); // Do we need that?
    double GetHeight();

    FlipperConfig &GetConfig();
    
   protected:
    virtual void OnStatePeriodic(FlipperState state, double dt) override;

   private:
    FlipperConfig _config;

    curtinfrc::control::PIDGains _gain;
    curtinfrc::control::PIDController _controller;
    curtinfrc::control::CurrentFFFilter _current_filter;

    curtinfrc::Usage<FlipperConfig>::Scoped _usage{&_config};
  };
