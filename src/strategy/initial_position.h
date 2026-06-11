#pragma once
#include"strategy.h"

class InitialPosition : public Strategy{
  public:
    InitialPosition(std::vector<Pos> distinations);
    ~InitialPosition() override;

    std::vector<ActionRecord> solve(Navigator& navigator,Logger& logger) override;

};
