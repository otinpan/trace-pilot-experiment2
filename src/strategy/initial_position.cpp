#include"initial_position.h"

// 到達不能かどうかの検出
// 到達不能だった場合は、現在位置を更新しない
namespace{
bool append_path_or_fail(
  std::vector<ActionRecord>& result,
  Logger& logger,
  const std::vector<ActionRecord>& path,
  const Pos& current,
  const Pos& target,
  const std::string& label
){
  logger.log(
    label+"\n"
    "from: ("+std::to_string(current.i)+","+std::to_string(current.j)+") "
    "to: ("+std::to_string(target.i)+","+std::to_string(target.j)+") "
    "num of path: "+std::to_string(path.size())
  );

  if(path.empty() && current!=target){
    logger.log("unreachable");
    return false;
  }

  result.insert(result.end(),path.begin(),path.end());
  return true;
}
}

InitialPosition::InitialPosition(std::vector<Pos> distinations)
  :Strategy(distinations)
{

}

InitialPosition::~InitialPosition(){

}

std::vector<ActionRecord> InitialPosition::solve(Navigator& navigator,Logger& logger){
  std::vector<ActionRecord> result;
  if(distinations_.empty()){
    return result;
  }
  std::vector<Pos> block_pos={
    Pos(9, 9),
    Pos(10,10),
    Pos(3, 9),
    Pos(16,10),
    Pos(9, 3),
    Pos(10,16),
  };

  Pos current=distinations_.front();
  // 初期ブロックの配置
  for(const auto& b:block_pos){
    const Pos target=b+Pos(0,-1);
    std::vector<ActionRecord> path=navigator.bfs(current,target);

    if(!append_path_or_fail(result,logger,path,current,target,"block")){
      continue;
    }
    current=target;

    // ブロック配置
    navigator.change_block(b);
    result.emplace_back(ActionRecord{
      ActionType::CHANGE,
      current,
      Direction::RIGHT,
    });
  }

  // 目的地に移動
  for(size_t i=1;i<distinations_.size();i++){
    const Pos target=distinations_[i];

    if(navigator.get_block(target)){
      const Pos approach=target+Pos(0,-1);
      if(!approach.is_on_map() || navigator.get_block(approach)){
        logger.log("blocked destination has no left approach");
        break;
      }

      std::vector<ActionRecord> path=navigator.bfs(current,approach);
      if(!append_path_or_fail(result,logger,path,current,approach,"blocked destination")){
        break;
      }

      navigator.change_block(target);
      result.emplace_back(ActionRecord{
        ActionType::CHANGE,
        approach,
        Direction::RIGHT,
      });
      result.emplace_back(ActionRecord{
        ActionType::MOVE,
        approach,
        Direction::RIGHT,
      });
      result.emplace_back(ActionRecord{
        ActionType::MOVE,
        target,
        Direction::LEFT,
      });
      navigator.change_block(target);
      result.emplace_back(ActionRecord{
        ActionType::CHANGE,
        approach,
        Direction::RIGHT,
      });

      current=approach;
      continue;
    }

    std::vector<ActionRecord> path=navigator.bfs(current,target);
    if(!append_path_or_fail(result,logger,path,current,target,"destination")){
      break;
    }
    current=target;
  }

  logger.log("blocks\n");
  for(int i=0;i<map_size;i++){
    std::string l="";
    for(int j=0;j<map_size;j++){
      if(navigator.get_block(Pos(i,j))){
        l+=".";
      }else{
        l+="x";
      }
    }
    logger.log(l);
  }
  

  return result;
}
