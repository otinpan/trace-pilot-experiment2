#include<iostream>
#include<vector>

#include"common.h"
#include"strategy/greedy.h"
#include"strategy/initial_position.h"
#include"navigator.h"

int map_size=0;
int main(){
  int n,m;
  std::cin>>n>>m;

  map_size=n;
  std::vector<Pos> g;
  for(int i=0;i<m;i++){
    int a,b; std::cin>>a>>b;
    // @trace-pilot 873e2385e6a102e91092a12ea767e3b8fcda45b7
    g.emplace_back(Pos(a,b));
  }

  Navigator navigator({});
  Logger logger("log.txt");

  InitialPosition strategy(g);
  std::vector<ActionRecord> result=strategy.solve(navigator,logger);

  for(const auto& r:result){
    std::cout<<ACTIONS_CHAR[static_cast<int>(r.type)]
      <<" "<<DIRS_CHAR[static_cast<int>(r.dir)]<<'\n';
  }
  
}
