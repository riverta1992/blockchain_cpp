#include <cassert>
#include "leveldb/db.h"
#include <iostream>

int main(){
  
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "./tmp", &db);
  assert(status.ok());

  // read and write
  /*
  std::string value;
  leveldb::Status s = db->Get(leveldb::ReadOptions(), key1, &value);
  if (s.ok()) s = db->Put(leveldb::WriteOptions(), key2, value);
  if (s.ok()) s = db->Delete(leveldb::WriteOptions(), key1);
  */
  std::string key1 = "year";
  std::string value1 = "1992";
  std::string key2 = "name";
  std::string value2 = "taro";
  std::string value;
  leveldb::Status s = db->Put(leveldb::WriteOptions(), key1, value1);
  if (s.ok()) s = db->Put(leveldb::WriteOptions(), key2, value2);
  if (s.ok()) s = db->Get(leveldb::ReadOptions(), key1, &value);
  std::cout << value << std::endl;
  
  // close db
  delete db;
  return 0;
}