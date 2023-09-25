#include <iostream>

#ifndef BLOCKCHAIN_H_
#include "blockchain.h"
#endif

#include "../cmdline/cmdline.h"

class CLI{
public:
  Blockchain *bc;
  cmdline::parser psr;
};

CLI::CLI(Blockchain* blockchain){
  bc = blockchain;
}

void CLI::printUsage(){
  std::cout << "Usage:" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "" << std::endl;
}

void CLI::addBlock(std::string data){
  bc->addBlock(data);
  std::cout << "Success!" << std::endl;
}

void CLI::printChain(){
  auto bci = bc->Iterator(); // is bci pointer ?
  while(1){
    Block *block = bci.Next();

    std::cout << "Prev. hash: " << block.PrevBlockHash << std::endl;
    std::cout << "Data" << block.Data << std::endl;
    std::cout << "Hash" << block.Hash << std::endl;
    // pow =
    auto pow = NewProofOfWork(block);
    std::cout << "Pow: " << std::endl << std::endl;

    // how to write len() in C++ ?
    if(len(block.PrevBlockHash)==0)
      break;
  }
}

void CLI::run(int argc, char *argv[]){
  // Validate args
  if(argc<2){
    printUsage();
    exit(1);
  }
  
  //
  psr.add<std::string>("addblock", '\0', "add block", true, "");
  psr.add("printchain", '\0', "print blockchain");
  psr.parse_check(argc, argv);
  
  std::string data = psr.get<std::string>("")
  std::cout << data << std::endl;
  addBlock(data);
}
