#include"state.h"

State::State(std::vector<Pos> distinations)
  :dists_(distinations)
  ,pos_(Pos(0,0))
{
  assert(!dists_.empty());
  pos_=dists_[0];
}

State::~State()=default;

  
