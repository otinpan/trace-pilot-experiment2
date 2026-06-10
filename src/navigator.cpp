#include"navigator.h"
#include<algorithm>
#include<queue>

Navigator::Navigator(std::vector<Pos> blocks)
  :blocks_()
  ,row_blocks_()
  ,col_blocks_()
{
// @trace-pilot d0b54a024abf0bd00d8ee52220a603d60c21a363
  for(const auto& block:blocks){
    change_block(block);
  }
}

// @trace-pilot fc89c8d031bf50dbb6c1b2cd43f3dd536bb5a415
// 幅優先探索 (BFS)
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
      auto next=move(now,static_cast<Direction>(k));
      if(!next){
        continue;
      }
      if(dist[next->i][next->j]!=-1){
        continue;
      }

      q.push(*next);
      dist[next->i][next->j]=d+1;
      pre[next->i][next->j]=ActionRecord{ActionType::MOVE,now};
    }

    // slide
    for(int k=0;k<DIRS.size();k++){
      auto next=slide(now,static_cast<Direction>(k));
      if(!next){
        continue;
      }
      if(dist[next->i][next->j]!=-1){
        continue;
      }

      q.push(*next);
      dist[next->i][next->j]=d+1;
      pre[next->i][next->j]=ActionRecord{ActionType::SLIDE,now};
    }
  }

// @trace-pilot ac8f01f4bc9b03667e67f8ccd716b35e27159ec9
  if(dist[to.i][to.j]==-1){
    return {};
  }

  vector<ActionRecord> path;
  Pos cur=to;
  while(cur!=from){
    const ActionRecord record=pre[cur.i][cur.j];
    path.push_back(ActionRecord{record.type,cur});
    cur=record.pos;
  }
  reverse(path.begin(),path.end());
  return path;
}

// @trace-pilot d0b54a024abf0bd00d8ee52220a603d60c21a363
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
// @trace-pilot e9c15b09a9b393aa5ed667d6eaf6ae63c7f2a46a
    case Direction::UP:{
      const auto& col=col_blocks_[pos.j];
// @trace-pilot e9c15b09a9b393aa5ed667d6eaf6ae63c7f2a46a
      auto iter=std::lower_bound(col.begin(),col.end(),pos.i);
      if(iter==col.begin()){
        next.i=0;
      }else{
        --iter;
        next.i=*iter+1;
      }
      break;
// @trace-pilot e9c15b09a9b393aa5ed667d6eaf6ae63c7f2a46a
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
// @trace-pilot e9c15b09a9b393aa5ed667d6eaf6ae63c7f2a46a
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
// @trace-pilot e9c15b09a9b393aa5ed667d6eaf6ae63c7f2a46a
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
// @trace-pilot e9c15b09a9b393aa5ed667d6eaf6ae63c7f2a46a
    }
    default:
      assert(false);
  }

// @trace-pilot e9c15b09a9b393aa5ed667d6eaf6ae63c7f2a46a
  if(next==pos){
    return std::nullopt;
  }

  return next;
}

bool Navigator::get_block(const Pos& pos) const{
  return blocks_.test(index(pos));
}
