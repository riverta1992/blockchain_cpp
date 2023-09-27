/*
#include <iostream>

#ifndef BLOCKCHAIN_H_
#include "blockchain.h"
#endif

#include "../cmdline/cmdline.h"
*/
#include "cli.h"
#include "proofofwork.h"

CLI::CLI(Blockchain* blockchain){
  bc = blockchain;
}

void CLI::printUsage(){
  std::cout << "Usage:" << std::endl;
  std::cout << "  --addblock=data : add a block to the blockchain" << std::endl;
  std::cout << "  --printchain : print all the blocks of the blockchain" << std::endl;
}

void CLI::addBlock(std::string data){
  bc->AddBlock(data);
  std::cout << "Success!" << std::endl;
}

void CLI::printChain(){
  auto bci = bc->Iterator(); // is bci pointer ?
  while(1){
    Block block = bci->Next();

    std::cout << "Prev. hash: " << block.prevBlockHash << std::endl;
    std::cout << "Data: " << block.data << std::endl;
    std::cout << "Hash: " << block.hash << std::endl;
    // pow =
    auto pow = NewProofOfWork(&block);
    std::cout << "Pow: " << pow->Validate() << std::endl << std::endl;

    // how to write len() in C++ ?
    if(block.prevBlockHash.length()==0){
      //std::cout << "break : string length"<< std::endl;
      break;
    }
    /*
    if(block.prevBlockHash == ""){
      std::cout << "break : string compare" << std::endl;
      break;
    }
    */
  }
}

void CLI::run(int argc, char *argv[]){
  bool flag = true;
  
  // Validate args
  if(argc<2){
    printUsage();
    flag = false;
  }
  
  //
  psr.add<std::string>("addblock", '\0', "add block", false, "");
  psr.add("printchain", '\0', "print blockchain");
  psr.parse_check(argc, argv);
  
  std::string data = psr.get<std::string>("addblock");
  if(psr.exist("printchain")){
    printChain();
    flag = false;
  }
  if(data.length()>0){
    addBlock(data);
    flag = false;
  }
  if(flag)
    printUsage();
}
