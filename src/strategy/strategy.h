#pragma once
#include<iostream>
#include<vector>
#include<cassert>

#include"../common.h"
#include"../navigator.h"
#include"../logger.h"

class Strategy{
  public:
    Strategy(std::vector<Pos> distinations);
    virtual ~Strategy();

    virtual std::vector<ActionRecord> solve(Navigator& navigator,Logger& logger);

  protected:
    std::vector<Pos> distinations_;
};

