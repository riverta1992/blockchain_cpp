/*
 * Blockchain in C++
 * Date:2023-09-16 ---> 2023-09-17
 * Author:riverta
 */
#include "blockchain.h"

Blockchain::Blockchain(){
  blocks.push_back(NewGenesisBlock());
};

void Blockchain::AddBlock(std::string data){
    auto prevBlock = blocks.back();
    Block* newBlock = NewBlock(data, prevBlock->hash);
    blocks.push_back(newBlock);
}
