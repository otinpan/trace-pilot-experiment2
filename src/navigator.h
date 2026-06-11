#pragma once
#include<iostream>
#include<vector>
#include<array>
#include<bitset>
#include<optional>

#include"common.h"
class Navigator{
  public:
    Navigator(std::vector<Pos> blocks);
    ~Navigator()=default;

    std::vector<ActionRecord> bfs(Pos from,Pos to) const;
    void change_block(const Pos& pos);
    bool get_block(const Pos& pos) const;

  private:
    // @trace-pilot 4cda53fe3be35f85a62c26847cb202661d0a9884
    std::optional<Pos> move(const Pos& from,Direction dir) const;
    std::optional<Pos> slide(const Pos& from,Direction dir) const;

    static constexpr int N=20;
    int index(const Pos& pos) const{
      return pos.i*N+pos.j;
    }


    std::bitset<N*N> blocks_;
    std::array<std::vector<int>,N> row_blocks_;
    std::array<std::vector<int>,N> col_blocks_;
};
