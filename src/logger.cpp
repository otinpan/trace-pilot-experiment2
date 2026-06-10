#include"logger.h"

Logger::Logger(const std::string& path)
  :ofs_(path)
{

}

void Logger::log(const std::string &s){
  ofs_<<s<<'\n';
}

void Logger::log(const Navigator& state){
}

