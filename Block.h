//
//  Block.h
//  BlockChainExample
//
//  Created by Jon on 1/10/18.
//  Copyright © 2018 Crypto Enthusiasts. All rights reserved.
//

#ifndef Block_h
#define Block_h

#include "Data.h"

// Block Class
class Block
{
private:
    int index;
    int nonce;
    size_t blockHash;
    size_t previousHash;
    size_t generateHash();

    Data data;

public:
    // Constuctor
    Block(int idx, Data d, size_t prevHash);
    Block(int indx, Data d, size_t hash, size_t preHash);
    // Get Index
    int getIndex();

    // Get Original Hash
    size_t getHash();

    // Get Previous Hash
    size_t getPreviousHash();

    // Transaction Data
    // Would ordinarily be a private member with a "getter": getData()
    Data getData();
    void MineBlock(uint32_t nDifficulty);
    // Validate Hash
    bool isHashValid();
    void PrintBlock();
};

#endif /* Block_h */
