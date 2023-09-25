#include <limits>
#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;
constexpr int64_t maxNonce = std::numeric_limits<int64_t>::max();
const int64_t targetBits = 24;

std::string IntToHex(int64_t i);

class ProofOfWork{
public:
  Block* block;
  mp::cpp_int target;
  ProofOfWork(Block* b);
  ProofOfWork(Block* b, mp::cpp_int t);
  std::string prepareData(int nonce);
  std::tuple<int,std::string> Run();
  bool Validate();
  /*
  std::string prepareData(){
    data = (pow.blocks.prevBlockHash
	    + pow.block.data,
	    + IntToHex(pow.block.timestamp),
	    + IntToHex(int64_t(targetBits)),
	    + IntToHex(nonce));
    return data;
  }
  std::tuple<int, std::string> Run(){
    mp::cpp_int hashInt;
    //std::byte[32] hash;
    std::string hash;
    int nonce = 0;
    Sha256 sha256;
    while(nonce<maxNonce){
      data = prepareData(nonce);
      hash = sha256(data);
      std::cout << '\r' << hash << std::end;
      // interpret hash as integer
      std::stringstream ss;
      //unsigned int x;
      ss << std::hex << hash;
      ss >> hashInt;
      //ss >> x;
      //hashInt = x;
      if(hashInt < pow.target)
	break;
      else
	nonce++;
    }
    std::cout << std::endl << std::endl;
    return {nonce, hash};
  }
  bool Validate(){
    mp::cpp_int hashInt;
    std::string data = pow.prepareData(pow.block.nonce);
    std::string hash = sha256(data);
    std::stringstream ss;
    ss << std::hex << hash;
    ss >> hashInt;
    bool isValid = (hashInt < pow.target);
    return isValid;
  }
  */
};

ProofOfWork* NewProofOfWork(Block* b);
