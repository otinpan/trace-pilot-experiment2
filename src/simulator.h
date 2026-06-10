#pragma once
#include<iostream>
#include<vector>

#include"common.h"
#include"navigator.h"
#include"strategy/strategy.h"
#include"logger.h"

class Simulator{
  public:
    Simulator(
        Navigator navigator,
        Strategy& strategy,
        Logger& logger
    );
    ~Simulator();

    std::vector<ActionRecord> simulate();

  private:
    Navigator navigator_;
    Strategy& strategy_;
    Logger& logger_;
};

