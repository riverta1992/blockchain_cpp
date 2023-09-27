/*
 * Blockchain in C++
 * Date:2023-09-16 ---> 2023-09-17
 * Author:riverta
 */
#include <vector>

#ifndef Block_H_
#include "block.h"
#define Block_H_
#endif

#include <leveldb/db.h>

class BlockchainIterator{
public:
  std::string currentHash;
  leveldb::DB *db;
  BlockchainIterator(std::string currentHash, leveldb::DB *db);
  Block Next();
};

class Blockchain{
public:
  std::string tip;
  leveldb::DB* db;
  Blockchain();
  ~Blockchain();
  //std::vector<Block*> blocks;  
  void AddBlock(std::string data);
  BlockchainIterator* Iterator();
};
