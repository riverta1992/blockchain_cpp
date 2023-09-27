/*
 * Blockchain in C++
 * Date:2023-09-16
 *
 */
#include <iostream>

#ifndef Blockchain_H_
#include "blockchain.h"
#define Blockchain_H_
#endif

#include "proofofwork.h"
#include "cli.h"

int main(int argc, char *argv[]){
  Blockchain bc;
  CLI cli(&bc);
  cli.run(argc, argv);
  /*
  bc.AddBlock("Send 1 BTC to Ivan");
  bc.AddBlock("Send 2 more BTC to Ivan");
  
  for(auto block:bc.blocks){
    std::cout << "Prev. hash: " << block->prevBlockHash << std::endl;
    std::cout << "Data: " << block->data << std::endl;
    std::cout << "Hash: " << block->hash << std::endl;

    ProofOfWork pow(block);
    std::cout << pow.Validate() << std::endl << std::endl;
  }
  */
  return 0;
}
