#include"greedy.h"

Greedy::Greedy(std::vector<Pos> distinations)
  :Strategy(distinations)
{

}

Greedy::~Greedy()=default;

std::vector<ActionRecord> Greedy::solve(Navigator& navigator, Logger& logger){
  std::vector<ActionRecord> result;
  if(distinations_.empty()){
    return result;
  }

  Pos current=distinations_.front();
  for(size_t i=1;i<distinations_.size();i++){
    const Pos target=distinations_[i];
    std::vector<ActionRecord> path=navigator.bfs(current,target);
    
    logger.log(
      "from: ("+std::to_string(current.i)+","+std::to_string(current.j)+") "
      "to: ("+std::to_string(target.i)+","+std::to_string(target.j)+") "
      "num of path: "+std::to_string(path.size())
    );
    result.insert(result.end(),path.begin(),path.end());
    current=target;
  }



  return result;
}
