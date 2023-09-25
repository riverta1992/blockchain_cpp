/*
 * Blockchain in C++
 * Date:2023-09-16
 *
 */
#include <chrono>
#include <string>

static int64_t getUnixTimeStamp(const std::time_t* t=nullptr);

class Block{
public:
  int64_t timestamp;
  std::string data;
  std::string prevBlockHash;
  std::string hash;
  int64_t nonce;
  Block(int64_t ts, std::string d, std::string pBH, std::string h, int64_t nonce);
  void SetHash();
};

Block* NewBlock(std::string data, std::string prevBlockHash);
Block* NewGenesisBlock();
