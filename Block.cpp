#include "Block.h"
//
//  Block.cpp
//  BlockChainExample
//
//  Created by Jon on 1/10/18.
//  Copyright © 2018 Crypto Enthusiasts. All rights reserved.
//

#include <stdio.h>
#include <string>

#include "Block.h"
#include "Data.h"

// Constructor with params
Block::Block(int idx, Data d, size_t prevHash)
{
    index = idx;
    data = d;
    previousHash = prevHash;
    blockHash = generateHash();
}

Block::Block(int indx, Data d, size_t hash, size_t preHash)
{
    index = indx;
    data = d;
    blockHash = hash;
    previousHash = preHash;
}

// private functions
int Block::getIndex()
{
    return index;
}

/*
 Generates hash for current block
 - Includes previousHash in generation
 - ^ Very important
*/
size_t Block::generateHash()
{
    // creating string of transaction data
    std::string toHashS = std::to_string(data.amount) + 
                                         data.packageCode + 
                                         data.name + 
                                         data.address + 
                                         data.type +
                                         data.date +
                          std::to_string(data.price) +
                          std::to_string(data.timestamp);

    // 2 hashes to combine
    std::hash<std::string> tDataHash; // hashes transaction data string
    std::hash<std::string> prevHash; // re-hashes previous hash (for combination)

    // combine hashes and get size_t for block hash
    return tDataHash(toHashS) ^ (prevHash(std::to_string(previousHash)) << 1);
}

// Public Functions
size_t Block::getHash()
{
    return blockHash;
}

size_t Block::getPreviousHash()
{
    return previousHash;
}

Data Block::getData()
{
    return data;
}

void Block::MineBlock(uint32_t nDifficulty)
{
    char* cstr = new char[nDifficulty + 1];
    for (uint32_t i = 0; i < nDifficulty; ++i)
    {
        cstr[i] = '0';
    }
    cstr[nDifficulty] = '\0';

    std::string str(cstr);
    char* s = new char[str.length() + nDifficulty];
    std::string a;
    do
    {
        nonce++;
        blockHash = generateHash();
        snprintf(s, sizeof s, "%zu", blockHash);
        std::string a(s);
    } while (a.substr(0, nDifficulty) != str);

    std::cout << "Block mined: " << blockHash << std::endl;
}

bool Block::isHashValid()
{
    return generateHash() == getHash();
}

void Block::PrintBlock()
{
    printf("\nBlock ===================================");
    printf("\nIndex: %d", index);
    printf("\nMode: %d", data.mode);
    printf("\nAmount: %lf", data.amount);
    printf("\nPrice: %lf", data.price);
    printf("\nDate: %s", data.date.c_str());
    printf("\nPackageCode: %s", data.packageCode.c_str());
    printf("\nAddress: %s", data.address.c_str());
    printf("\nName: %s", data.name.c_str());
    printf("\ntype: %s", data.type.c_str());
    printf("\nTimestamp: %d", data.timestamp);
    printf("\nHash: %zu", blockHash);
    printf("\nPrevious Hash: %zu", previousHash);
    printf("\nIs Block Valid?: %d\n", isHashValid());
}
