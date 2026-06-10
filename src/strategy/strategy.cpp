#include"strategy.h"

Strategy::Strategy(){

}

Strategy::~Strategy()=default;

std::vector<Pos> Strategy::solve(State& state,Logger& logger){
  (void)state;
  (void)logger;

  return{};
}

