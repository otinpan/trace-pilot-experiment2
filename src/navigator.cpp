#include"navigator.h"
#include<algorithm>
#include<queue>

Navigator::Navigator(std::vector<Pos> blocks)
  :blocks_()
  ,row_blocks_()
  ,col_blocks_()
{
  for(const auto& block:blocks){
    change_block(block);
  }
}

// 幅優先探索
// fromからtoへの最短経路
std::vector<ActionRecord> Navigator::bfs(Pos from,Pos to) const{
  using namespace std;
  vector<vector<int>> dist(map_size,vector<int>(map_size,-1));
  vector<vector<ActionRecord>> pre(map_size,vector<ActionRecord>(map_size));

  queue<Pos> q;
  dist[from.i][from.j]=0;
  q.push(from);

  while(!q.empty()){
    Pos now=q.front();
    int d=dist[now.i][now.j];
    q.pop();

    if(now==to){
      break;
    }

    // move
    for(int k=0;k<DIRS.size();k++){
      const Direction dir=static_cast<Direction>(k);
      auto next=move(now,dir);
      if(!next){
        continue;
      }
      if(dist[next->i][next->j]!=-1){
        continue;
      }

      q.push(*next);
      dist[next->i][next->j]=d+1;
      pre[next->i][next->j]=ActionRecord{ActionType::MOVE,now,dir};
    }

    // slide
    for(int k=0;k<DIRS.size();k++){
      const Direction dir=static_cast<Direction>(k);
      auto next=slide(now,dir);
      if(!next){
        continue;
      }
      if(dist[next->i][next->j]!=-1){
        continue;
      }

      q.push(*next);
      dist[next->i][next->j]=d+1;
      pre[next->i][next->j]=ActionRecord{ActionType::SLIDE,now,dir};
    }
  }

  if(dist[to.i][to.j]==-1){
    return {};
  }

  vector<ActionRecord> path;
  Pos cur=to;
  while(cur!=from){
    const ActionRecord record=pre[cur.i][cur.j];
    path.push_back(record);
    cur=record.pos;
  }
  reverse(path.begin(),path.end());
  return path;
}

void Navigator::change_block(const Pos& pos){
  assert(pos.is_on_map());

  auto& row=row_blocks_[pos.i];
  auto row_it=std::lower_bound(row.begin(),row.end(),pos.j);

  auto& col=col_blocks_[pos.j];
  auto col_it=std::lower_bound(col.begin(),col.end(),pos.i);

  const int block_index=index(pos);
  if(!blocks_.test(block_index)){
    row.insert(row_it,pos.j);
    col.insert(col_it,pos.i);
  }else{
    assert(row_it!=row.end() && *row_it==pos.j);
    assert(col_it!=col.end() && *col_it==pos.i);
    row.erase(row_it);
    col.erase(col_it);
  }

  blocks_.flip(block_index);

}

std::optional<Pos> Navigator::move(const Pos& pos,Direction dir) const{
  Pos next=pos+DIRS[static_cast<int>(dir)];
  if(!next.is_on_map()){
    return std::nullopt;
  }

  if(get_block(next)){
    return std::nullopt;
  }

  return next;
}

std::optional<Pos> Navigator::slide(const Pos& pos,Direction dir) const{
  // チェック用
  Pos next=pos+DIRS[static_cast<int>(dir)];
  if(!next.is_on_map()||get_block(next)){
    return std::nullopt;
  }
  next=pos;
  switch(dir){
    case Direction::UP:{
      const auto& col=col_blocks_[pos.j];
      auto iter=std::lower_bound(col.begin(),col.end(),pos.i);
      if(iter==col.begin()){
        next.i=0;
      }else{
        --iter;
        next.i=*iter+1;
      }
      break;
    }
    case Direction::DOWN:{
      const auto& col=col_blocks_[pos.j];
      auto iter=std::upper_bound(col.begin(),col.end(),pos.i);
      if(iter==col.end()){
        next.i=map_size-1;
      }else{
        next.i=*iter-1;
      }
      break;
    }
    case Direction::RIGHT:{
      const auto& row=row_blocks_[pos.i];
      auto iter=std::upper_bound(row.begin(),row.end(),pos.j);
      if(iter==row.end()){
        next.j=map_size-1;
      }else{
        next.j=*iter-1;
      }
      break;
    }
    case Direction::LEFT:{
      const auto& row=row_blocks_[pos.i];
      auto iter=std::lower_bound(row.begin(),row.end(),pos.j);
      if(iter==row.begin()){
        next.j=0;
      }else{
        --iter;
        next.j=*iter+1;
      }
      break;
    }
    default:
      assert(false);
  }

  if(next==pos){
    return std::nullopt;
  }

  return next;
}

bool Navigator::get_block(const Pos& pos) const{
  return blocks_.test(index(pos));
}
