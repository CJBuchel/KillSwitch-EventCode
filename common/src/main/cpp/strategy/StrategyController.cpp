#include "strategy/Strategy.h"

#include <mutex>
#include <exception>

#include <frc/Timer.h>
#include <wpi/spinlock.h>

using namespace curtinfrc;

struct StrategyController::Impl {
  using SystemsColl = std::set<StrategySystem *>;

  std::recursive_mutex systemsMtx;
  SystemsColl systems;
};

StrategyController::StrategyController() : _impl(new Impl) { }
StrategyController::~StrategyController() {
  delete _impl;
}

void StrategyController::Register(StrategySystem *sys) {
  {
    std::lock_guard<std::recursive_mutex> lk(_impl->systemsMtx);
    _impl->systems.insert(sys);
  }
}

bool StrategyController::Schedule(std::shared_ptr<Strategy> strategy, bool force) {
  std::lock_guard<std::recursive_mutex> lock(_impl->systemsMtx);
  return DoSchedule(strategy, force);
}

void StrategyController::Update(double dt) {
  if (dt < 0) {
    // Automatic dt finding with system clock
    double t = frc::GetTime();
    if (_last_update_time > 0.01) {
      dt = t - _last_update_time;
    } else {
      dt = 0;
    }
    _last_update_time = t;
  }

  {
    std::lock_guard<std::recursive_mutex> lk(_impl->systemsMtx);
    for (StrategySystem *sys : _impl->systems) {
      sys->StrategyUpdate(dt);
    }
  }
}

void StrategyController::InterruptAll(bool force) {
  std::lock_guard<std::recursive_mutex> lock(_impl->systemsMtx);
  for (StrategySystem *sys : _impl->systems) {
    auto active = sys->GetActiveStrategy();
    if (active != nullptr && active != sys->GetDefaultStrategy() && (force || active->_can_interrupt)) {
      sys->StrategyReplace(nullptr);
      sys->StrategyStatusUpdate();
    }
  }
}

bool StrategyController::DoSchedule(std::shared_ptr<Strategy> strategy, bool force) {
  if (strategy->GetStrategyState() != StrategyState::INITIALIZED && strategy->GetStrategyState() != StrategyState::CANCELLED && !strategy->_can_reuse) {
    throw std::invalid_argument("Cannot reuse a Strategy that has SetCanBeReused(false)");
  }

  // Assert that systems exist, and that they may have an interrupted strategy
  for (StrategySystem *sys : strategy->GetRequirements()) {
    if (std::find(_impl->systems.begin(), _impl->systems.end(), sys) == _impl->systems.end()) {
      throw std::invalid_argument("StrategyController does not have registered system required by " + strategy->GetStrategyName());
    } else {
      auto active = sys->GetActiveStrategy();
      if (active != nullptr) {
        bool can_interrupt = active->_can_interrupt || active == sys->GetDefaultStrategy();
        if (!force && !can_interrupt) {
          // Cannot interrupt, therefore cancelled.
          strategy->Stop(StrategyState::CANCELLED);
          return false;
        }
      }
    }
  }

  // Replace the running strategy on each system
  for (StrategySystem *sys : strategy->GetRequirements()) {
    // sys->_pending = strategy;
    sys->StrategyReplace(strategy);
    sys->StrategyStatusUpdate();
  }
  return true;
}