#include"strategy.h"

Strategy::Strategy(std::vector<Pos> distinations)
  :distinations_(distinations)
{

}

Strategy::~Strategy()=default;

std::vector<ActionRecord> Strategy::solve(Navigator& navigator,Logger& logger){
  (void)navigator;
  (void)logger;

  return{};
}

