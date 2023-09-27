/*
 * Blockchain in C++
 * Date:2023-09-16
 *
 */
#include <vector>

#ifndef SHA256_H_
#include <sha256.h>
#endif

#ifndef Block_H_
#include "block.h"
#endif

#ifndef ProofOfWork_H_
#include "proofofwork.h"
#endif

static int64_t getUnixTimeStamp(const std::time_t* t){
  std::time_t st = t==nullptr ? std::time(nullptr):*t;
  auto secs = static_cast<std::chrono::seconds>(st).count();
  return static_cast<int64_t>(secs);
}
Block::Block(){
  timestamp = 0;
  data = "";
  prevBlockHash = "";
  hash = "";
  nonce = 0;
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
/*
template <class Archive>
void Block::serialize(Archive& ar, unsigned int){
  ar & boost::serialization::make_nvp("timestamp", timestamp);
  ar & boost::serialization::make_nvp("data", data);
  ar & boost::serialization::make_nvp("prevBlockHash", prevBlockHash);
  ar & boost::serialization::make_nvp("hash", hash);
  ar & boost::serialization::make_nvp("nonce", nonce);
}
*/

/*
std::stringstream Serialize(Block block){
  std::stringstream ss;
  boost::archive::text_oarchive ar(ss);
  ar << boost::serialization::make_nvp("Block", block);
  return ss;
}
*/

/*
Block* DeserializeBlock(std::stringstream ss){
  Block block;
  ar >> boost::serialization::make_nvp("Block", block);
  return;
}
*/
/*
std::string Serialize(std::shared_ptr<Block> block){
  std::stringstream ss;
  cereal::JSONOutputArchive jsonOutputArchive(ss);
  jsonOutputArchive(cereal::make_nvp("block", block));
  return ss.str();
}

Block* Deserialize(std::string s){
  std::stringstream ss;
  ss << s;
  cereal::JSONInputArchive jsonInputArchive(ss);
  Block *block = NewBlock("","");
  jsonInputArchive(cereal::make_nvp("block",block));
  return block;
}
*/
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
