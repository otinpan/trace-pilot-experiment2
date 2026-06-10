#pragma once
#include<iostream>
#include<vector>

#include"common.h"

class State{
  public:
    State(std::vector<Pos> distinations);
    ~State();

  private:
    Pos pos_;
    std::vector<Pos> dists_;
};
