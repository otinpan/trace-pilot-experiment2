#pragma once
#include<cassert>
#include<iostream>
#include<vector>
#include<array>

extern int map_size;

struct Pos{
  int i,j;
  Pos(int _i,int _j)
    :i(_i)
    ,j(_j){

    }

  Pos operator+(const Pos& other) const{
    return Pos(i+other.i,j+other.j);
  }

  Pos operator-(const Pos& other) const{
    return Pos(i-other.i,j-other.j);
  }

  bool operator==(const Pos& other) const{
    return i==other.i && j==other.j;
  }

  bool operator!=(const Pos& other) const{
    return i!=other.i && j!=other.j;
  }

  bool is_on_map() const{
    return i>=0 && i<map_size && j>=0 && j<map_size;
  }

  // @trace-pilot 1ffd672428fd4f2c37c60ed660f35d8456364846
  // マンハッタン距離
  int manhattan_distance(const Pos& other) const{
    return std::abs(i-other.i)+std::abs(j-other.j);
  }
};


enum ActionType{
  MOVE,
  SLIDE,
  CHANGE
};

struct ActionRecord{
  ActionType type;
  Pos pos=Pos(-1,-1);
};



enum class Direction{
  UP,
  DOWN,
  RIGHT,
  LEFT
};


const std::array<Pos,4> DIRS={
  Pos(-1,0),
  Pos(1,0),
  Pos(0,1),
  Pos(0,-1)
};

inline Direction get_direction(const Pos& from,const Pos& to){
  Pos diff=to-from;
  for(int i=0;i<static_cast<int>(DIRS.size());i++){
    if(DIRS[i]==diff){
      return static_cast<Direction>(i);
    }
  }
  assert(false);
  return Direction::UP;
}


