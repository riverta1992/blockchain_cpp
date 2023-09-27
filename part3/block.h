/*
 * Blockchain in C++
 * Date:2023-09-16
 *
 */
#include <chrono>
#include <string>
/*
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
*/
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <memory>

static int64_t getUnixTimeStamp(const std::time_t* t=nullptr);

class Block{
public:
  int64_t timestamp;
  std::string data;
  std::string prevBlockHash;
  std::string hash;
  int64_t nonce;
  Block();
  Block(int64_t ts, std::string d, std::string pBH, std::string h, int64_t nonce);
  void SetHash();
  /* boost
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, unsigned int );
  */
  template<class Archive>
  void serialize(Archive &archive){
    archive(
	    CEREAL_NVP(timestamp),
	    CEREAL_NVP(data),
	    CEREAL_NVP(prevBlockHash),
	    CEREAL_NVP(hash),
	    CEREAL_NVP(nonce));
  }
};

Block* NewBlock(std::string data, std::string prevBlockHash);
Block* NewGenesisBlock();
//std::string Serialize(std::shared_ptr<Block> block);
//Block* Deserialize(std::string s);
