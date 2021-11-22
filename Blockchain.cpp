//
//  Blockchain.cpp
//  BlockChainExample
//
//  Created by Jon on 1/10/18.
//  Copyright © 2018 Crypto Enthusiasts. All rights reserved.
//

#include <stdio.h>
#include <ctime>
#include <string>

#include "Block.h"
#include "Blockchain.h"

#include <vector>

// Blockchain Constructor
Blockchain::Blockchain()
{
    
}

// Public Chain Getter
std::vector<Block> Blockchain::getChain() {
    return chain;
}

// Create Genesis Block
Block Blockchain::createGenesisBlock()
{
    saveFile.open("Blockdata.txt", std::ios::out | std::ios::in);
    // Get Current Time
    std::time_t current;

    // Setup Initial Transaction Data
    Data d(0,0,0,"Genesis", "Genesis","Genesis", "Genesis", "Genesis", time(&current));
    // Return Genesis Block
    Block genesis(0, d, 0);
    chain.push_back(genesis);
    saveBlock(genesis);
    return genesis;
}

// We only need pointer here
// to demonstrate manipulation of transaction data
Block* Blockchain::getLatestBlock()
{
    return &chain.back();
}

void Blockchain::addBlock(Data d)
{
    int index = (int)chain.size();
    std::size_t previousHash = (int)chain.size() > 0 ? getLatestBlock()->getHash() : 0;
    Block newBlock(index, d, previousHash);
    newBlock.MineBlock(0);
    chain.push_back(newBlock);
    saveBlock(newBlock);
}

int Blockchain::getDayfromDate(std::string date)
{
    std::string daystring = date.substr(0, 2);
    int day = std::stoi(daystring);
    return day;
}

int Blockchain::getMonthfromDate(std::string date)
{
    std::string monthstring = date.substr(3, 5);
    int month = std::stoi(monthstring);
    return month;
}

int Blockchain::getYearfromDate(std::string date)
{
    std::string yearstring = date.substr(6, 10);
    int year = std::stoi(yearstring);
    return year;
}

void Blockchain::searchPackageCode(std::string _packageCode)
{
    std::vector<Block>::iterator it;
    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        if (currentBlock.getData().packageCode == _packageCode) 
        {
            currentBlock.PrintBlock();
        }
    }
}

bool Blockchain::isChainValid()
{
    std::vector<Block>::iterator it;

    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        if (!currentBlock.isHashValid())
        {
            return false;
        }

        // Don't forget to check if this is the first item
        if (it != chain.begin())
        {
            Block previousBlock = *(it - 1);
            if (currentBlock.getPreviousHash() != previousBlock.getHash())
            {
                return false;
            }
        }
    }

    return true;
}

void Blockchain::printChain() {
    std::vector<Block>::iterator it;

    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        currentBlock.PrintBlock();
    }
}

void Blockchain::saveBlock(Block block)
{
    saveFile << block.getIndex() << std::endl;
    saveFile << block.getData().mode << std::endl;
    saveFile << block.getData().amount << std::endl;
    saveFile << block.getData().price << std::endl;
    saveFile << block.getData().packageCode << std::endl;
    saveFile << block.getData().date << std::endl;
    saveFile << block.getData().address << std::endl;
    saveFile << block.getData().name << std::endl;
    saveFile << block.getData().type << std::endl;
    saveFile << block.getData().timestamp << std::endl;
    saveFile << block.getHash() << std::endl;
    saveFile << block.getPreviousHash() << std::endl;
}

void Blockchain::loadBlockFromFile()
{
    saveFile.open("Blockdata.txt", std::ios::out | std::ios::in | std::ios::app);
    std::fstream blockData;
    blockData.open("Blockdata.txt", std::ios::in);
    char checkEOF;
    while (blockData.get(checkEOF)) {
        blockData.unget();
        int index;
        size_t hash, prehash;
        blockData >> index;
        Data savedData;
        savedData.addDataFromFile(blockData);
        blockData >> hash;
        blockData >> prehash;
        Block savedBlock(index,savedData,hash,prehash);
        chain.push_back(savedBlock);
        char dumbChar = blockData.get();
    }
}

void Blockchain::alertStorage() {

    double inAmount = 0, outAmount = 0;
    std::vector<Block>::iterator it;
    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        if (currentBlock.getData().mode == 1)
        {
            inAmount += currentBlock.getData().amount;
        }
        else
        {
            outAmount += currentBlock.getData().amount;
        }
    }
    if (inAmount - outAmount <= 1000) {
        std::cout << "!!!ALERT STORAGE IS LOW!!! \nNeed to import more to the warehouse\n";
    }
}

void Blockchain::amountInStorage() {
    double inAmount = 0, outAmount = 0;
    std::vector<Block>::iterator it;
    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        if (currentBlock.getData().mode == 1)
        {
            inAmount += currentBlock.getData().amount;
        }
        else
        {
            outAmount += currentBlock.getData().amount;
        }
    }
    std::cout << "Amount is :" << inAmount - outAmount << "kg\n";
}

void Blockchain::profitOfInter() {
    double inPrice = 0, outPrice = 0;
    std::vector<Block>::iterator it;

    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        if (currentBlock.getData().timestamp)
            if (currentBlock.getData().mode == 1)
            {
                inPrice += currentBlock.getData().price;
            }
            else
            {
                outPrice += currentBlock.getData().price;
            }
    }
    std::cout << "Profit of Interprise all the time is :" << inPrice - outPrice << "dollar\n";
}

void Blockchain::searchFromDatetoDate(int m1, int y1, int m2, int y2)
{
    double inPrice = 0, outPrice = 0;
    double inAmount = 0, outAmount = 0;
    int inOders = 0, outOders = 0;
    std::vector<Block>::iterator it=chain.begin();
    it++;
    for (; it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        bool cond = false;
        if (getYearfromDate(currentBlock.getData().date) == y1)
        {
            if (getMonthfromDate(currentBlock.getData().date) > m1) {
                cond = true;
            }
        }
        else if (getYearfromDate(currentBlock.getData().date) == y2)
        {
            if (getMonthfromDate(currentBlock.getData().date) < m2) {
                cond = true;
            }
        }
        else if (getYearfromDate(currentBlock.getData().date) > y1 &&
            getYearfromDate(currentBlock.getData().date) < y2)
        {
            cond = true;
        }
        if (cond == true)
        {
            if (currentBlock.getData().mode == 1)
            {
                inPrice += currentBlock.getData().price;
            }
            else
            {
                outPrice += currentBlock.getData().price;
            }
        }
    }
}