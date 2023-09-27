/*
 * Blockchain in C++
 * Date:2023-09-16 ---> 2023-09-17
 * Author:riverta
 */
#ifndef Blockchain_H_
#include "blockchain.h"
#endif

#include <iostream>

Blockchain::Blockchain(){
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "./blockchain.db", &db);
  
  std::string tip;
  leveldb::Status s = db->Get(leveldb::ReadOptions(), "l", &tip);
  if(!s.ok()){
    std::cout << "No existing blockchain found. Creating a new one..." << std::endl;
    Block* genesis = NewGenesisBlock();
    //std::shared_ptr<Block> genesis = NewGenesisBlock();
    //boost::archive::text_oarchive ar(ss);
    //ar << boost::serialization::make_nvp("Block", *genesis);

    // Serialize by cereal
    std::stringstream ss;
    cereal::JSONOutputArchive jsonOutputArchive(ss);
    jsonOutputArchive(cereal::make_nvp("block", *genesis));
    s = db->Put(leveldb::WriteOptions(), genesis->hash, ss.str());
    ss.clear();
    
    //s = db->Put(leveldb::WriteOptions(), genesis.Hash, genesis.Serialize());
    if(!s.ok()){
      std::cout << s.ToString() << std::endl;
    }
    
    db->Put(leveldb::WriteOptions(), "l", genesis->hash);
    if(!s.ok()){
      std::cout << s.ToString() << std::endl;
    }
    
    tip = genesis->hash;
    //blocks.push_back(genesis);
  }
  this->tip = tip;
  this->db = db;
};

Blockchain::~Blockchain(){
  delete this->db;
}

void Blockchain::AddBlock(std::string data){
  /*
    auto prevBlock = blocks.back();
    Block* newBlock = NewBlock(data, prevBlock->hash);
    blocks.push_back(newBlock);
  */
  std::string lastHash;
  leveldb::Status s = this->db->Get(leveldb::ReadOptions(), "l", &lastHash);
  Block *block = NewBlock(data, lastHash);
  //Block *block = NewBlock(data, lastHash);
  /*
  std::stringstream ss;
  boost::archive::text_oarchive ar(ss);
  ar << boost::serialization::make_nvp("Block", *block);
  */
  
  // Serialize by cereal
  std::stringstream ss;
  cereal::JSONOutputArchive jsonOutputArchive(ss);
  jsonOutputArchive(cereal::make_nvp("block", *block));
  s = this->db->Put(leveldb::WriteOptions(), block->hash, ss.str());
  ss.clear();
  
  s = this->db->Put(leveldb::WriteOptions(), "l", block->hash);

  this->tip = block->hash;
}

BlockchainIterator::BlockchainIterator(std::string currentHash, leveldb::DB *db){
  this->currentHash = currentHash;
  this->db = db;
}

BlockchainIterator* Blockchain::Iterator(){
  BlockchainIterator *bci = new BlockchainIterator(this->tip, this->db);
  return bci;
}

Block BlockchainIterator::Next(){
  //Block *block = new Block();
  
  /* Deserialize Block*/
  //Block *block = NewBlock("", "");
  //std::stringstream ss;  
  std::string s0;
  leveldb::Status s = db->Get(leveldb::ReadOptions(), this->currentHash, &s0);
  Block block;
  if(s.ok()){
    //std::cout << "s0:\n" << s0 << std::endl;
    std::stringstream ss;
    ss << s0 << "}";// black magic
    cereal::JSONInputArchive jsonInputArchive(ss);
    jsonInputArchive(cereal::make_nvp("block",block));
  }else{
    std::cout << s.ToString() << std::endl;
    exit(1);
  }
  this->currentHash = block.prevBlockHash;
  
  return block;
}
