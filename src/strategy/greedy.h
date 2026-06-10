#pragma once
#include<iostream>

#include"strategy.h"

class Greedy : public Strategy{
  public:
    Greedy(std::vector<Pos> distinations);
    ~Greedy() override;

    std::vector<ActionRecord> solve(Navigator& navigator,Logger& logger) override;
};
