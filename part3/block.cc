/*
 * Blockchain in C++
 * Date:2023-09-16
 *
 */
#include <vector>

#ifndef SHA256_H_
#include "../hash-library/sha256.h"
#endif

#include "block.h"

#ifndef ProofOfWork_H_
#include "proofofwork.h"
#endif

static int64_t getUnixTimeStamp(const std::time_t* t){
  std::time_t st = t==nullptr ? std::time(nullptr):*t;
  auto secs = static_cast<std::chrono::seconds>(st).count();
  return static_cast<int64_t>(secs);
}
Block::Block(int64_t ts, std::string d, std::string pBH, std::string h, int64_t n){
  timestamp = ts;
  data = d;
  prevBlockHash = pBH;
  hash = h;
  nonce = n;
}

void Block::SetHash(){
  std::string ts = std::to_string(timestamp);
  std::string headers = prevBlockHash + data + ts;
  SHA256 sha256;
  hash = sha256(headers);
}

Block* NewBlock(std::string data, std::string prevBlockHash){
  Block *b = new Block(getUnixTimeStamp(), data, prevBlockHash, "", 0);
  ProofOfWork* pow = NewProofOfWork(b);
  auto [nonce, hash] = pow->Run();
  
  //b->SetHash();
  b->hash = hash;
  b->nonce = nonce;
  
  return b;
}

Block* NewGenesisBlock(){
  return NewBlock("Genesis Block", "");
}
