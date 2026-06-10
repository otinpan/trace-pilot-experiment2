#pragma once
#include<iostream>
#include<vector>
#include<cassert>

#include"../common.h"
#include"../state.h"
#include"../logger.h"

class Strategy{
  public:
    Strategy();
    virtual ~Strategy();

    virtual std::vector<Pos> solve(State& state,Logger& logger);
};

