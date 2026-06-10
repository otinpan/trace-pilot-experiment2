#pragma once
#include<iostream>
#include<vector>

#include"common.h"
#include"state.h"
#include"strategy/strategy.h"
#include"logger.h"

class Simulator{
  public:
    Simulator(
        State state,
        Strategy& strategy,
        Logger& logger
    );
    ~Simulator();

    std::vector<Pos> simulate();

  private:
    State state_;
    Strategy& strategy_;
    Logger& logger_;
};

