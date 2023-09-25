/*
 * Blockchain in C++
 * Date:2023-09-16 ---> 2023-09-17
 * Author:riverta
 */
#include <vector>

#ifndef Block_H_
#include "block.h"
#endif

class Blockchain{
public:
  Blockchain();
  std::vector<Block*> blocks;  
  void AddBlock(std::string data);
};
