#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

#include"state.h"

class Logger{
  public:
    Logger(const std::string& path);

    void log(const std::string& s);
    void log(const State& state);
  private:
    std::ofstream ofs_;
};

