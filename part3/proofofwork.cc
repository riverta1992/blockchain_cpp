//#include <limits>
//#include <boost/multiprecision/cpp_int.hpp>
#ifndef Block_H_
#include "block.h"
#endif

#ifndef ProofOfWork_H_
#include "proofofwork.h"
#endif

#ifndef SHA256_H_
#include "../hash-library/sha256.h"
#endif
/*
namespace mp = boost::multiprecision;
constexpr int64_t maxNonce = std::numeric_limits<int64_t>::max();
const targetBits = 24;
*/

std::string IntToHex(int64_t i){
  std::ostringstream ss;
  ss << std::hex << i;
  std::string result = ss.str();
  return result;
}

ProofOfWork::ProofOfWork(Block* b){
  block = b;
}

ProofOfWork::ProofOfWork(Block* b, mp::cpp_int t){
  block = b;
  target = t;
}

std::string ProofOfWork::prepareData(int nonce){
  std::string data = block->prevBlockHash;
  data += block->data;
  data += IntToHex(block->timestamp);
  data += IntToHex(int64_t(targetBits));
  data += IntToHex(nonce);
  return data;
}

std::tuple<int, std::string> ProofOfWork::Run(){
  mp::cpp_int hashInt;
  //std::byte[32] hash;
  std::string hash,data;
  int nonce = 0;
  SHA256 sha256;
  while(nonce<maxNonce){
    data = prepareData(nonce);
    hash = sha256(data);
    std::cout << "\r" << hash << std::flush;
    // interpret hash as integer
    std::stringstream ss;
    //unsigned int x;
    ss << std::hex << hash;
    ss >> hashInt;
    //ss >> x;
    //hashInt = x;
    if(hashInt < this->target)
      break;
    else
      nonce++;
  }
  std::cout << std::endl << std::endl;
  std::cout << "nonce = " << nonce << std::endl;
  return {nonce, hash};
}

bool ProofOfWork::Validate(){
  mp::cpp_int hashInt;
  std::string data = prepareData(block->nonce);
  SHA256 sha256;
  std::string hash = sha256(data);
  std::stringstream ss;
  ss << std::hex << hash;
  ss >> hashInt;
  bool isValid = (hashInt < target);
  return isValid;
}

ProofOfWork* NewProofOfWork(Block* b){
  mp::cpp_int target = 1;
  target = target << (256-targetBits);
  ProofOfWork *pow = new ProofOfWork(b, target);
  return pow;
}
