#include"simulator.h"

Simulator::Simulator(State state,Strategy& strategy,Logger& logger)
  :state_(std::move(state))
  ,strategy_(strategy)
  ,logger_(logger)
{

}

Simulator::~Simulator(){

}

std::vector<Pos> Simulator::simulate(){
  logger_.log("start");
  std::vector<Pos> result=strategy_.solve(state_,logger_);

  return result;
}

