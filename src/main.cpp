#include<iostream>
#include<vector>

#include"common.h"

int main(){
  int n,m;
  std::cin>>n>>m;
  std::vector<Pos> g;
  for(int i=0;i<m;i++){
    int a,b; std::cin>>a>>b;
    a--;
    b--;
    // @trace-pilot 873e2385e6a102e91092a12ea767e3b8fcda45b7
    g.emplace_back(Pos(a,b));
  }
  
}
