#include <iostream>

#ifndef Blockchain_H_
#include "blockchain.h"
#define Blockchain_H_
#endif

#include "../cmdline/cmdline.h"

class CLI{
public:
  Blockchain *bc;
  cmdline::parser psr;
  CLI(Blockchain* bc);
  void printUsage();
  void addBlock(std::string data);
  void printChain();
  void run(int argc, char *argv[]);
};
