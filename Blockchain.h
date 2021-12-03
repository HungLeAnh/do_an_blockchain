//
//  Blockchain.h
//  BlockChainExample
//
//  Created by Jon on 1/10/18.
//  Copyright © 2018 Crypto Enthusiasts. All rights reserved.
//

#ifndef Blockchain_h
#define Blockchain_h

#include <vector>
#include <string>
#include <fstream>
#include "Block.h"

// Blockchain Class
class Blockchain
{
private:
    std::vector<Block> chain;
    std::fstream saveFile;

public:
    // Constuctor
    Blockchain();

    // Public Functions
    Block createGenesisBlock(std::string name);
    std::vector<Block> getChain();
    Block* getLatestBlock();
    bool isChainValid();
    void loadBlockFromFile(std::string name);
    void saveBlock(Block block);
    void addBlock(Data data);
    void printChain();
    int getDayfromDate(std::string date);
    int getMonthfromDate(std::string date);
    int getYearfromDate(std::string date);
    void searchPackageCode(std::string _packageCode);
    double amountInStorage();
    void alertStorage();
    void profitOfInter();
    void searchFromDatetoDate(int m1, int y1, int m2, int y2);
    void barChartOfYear(int year);
};

#endif /* Blockchain_h */
