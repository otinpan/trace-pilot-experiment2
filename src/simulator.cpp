#include"simulator.h"

Simulator::Simulator(Navigator navigator,Strategy& strategy,Logger& logger)
  :navigator_(std::move(navigator))
  ,strategy_(strategy)
  ,logger_(logger)
{

}

Simulator::~Simulator(){

}

std::vector<ActionRecord> Simulator::simulate(){
  logger_.log("start");
  std::vector<ActionRecord> result=strategy_.solve(navigator_,logger_);

  return result;
}

