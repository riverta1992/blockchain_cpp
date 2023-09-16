#include <iostream>
#include <chrono>
#include "sha256.h"

// Go: time.Now().Unix
// C++: ???
static uint64_t getUnixTimeStamp(const std::time_t* t=nullptr)
{
  std::time_t st = t==nullptr ? std::time(nullptr):*t;
  auto secs = static_cast<std::chrono::seconds>(st).count();
  return static_cast<uint64_t>(secs);
}

int main()
{
  // Unix time
  auto now = std::chrono::system_clock::now();
  std::time_t end_time = std::chrono::system_clock::to_time_t(now);
  std::cout << std::ctime(&end_time) << std::endl;
  std::cout << getUnixTimeStamp() << std::endl;

  // SHA256
  SHA256 sha256;
  const char* buffer = "How are you";
  std::cout << sha256(buffer, 11) << std::endl;
  std::string s0 = "Hello";
  std::cout << sha256(s0) << std::endl;
  
  return 0;
}
    
