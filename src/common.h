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

