//
//  Block.cpp
//  BlockChainExample
//
//  Created by Jon on 1/10/18.
//  Copyright © 2018 Crypto Enthusiasts. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

#include "Data.h"
#include "Block.h"
#include "Blockchain.h"
#include "Users.h"

using namespace std;

int main()
{
    // Start Blockchain
    std::fstream listOfBC;
    //listOfBC.open("listofbc.txt", std::fstream::out|std::fstream::in|std::fstream::app);

    char ch;
    printf("===================================\n");
    printf("Are you the initial chain? (y or n)");
    std::cin >> ch;
    printf("===================================\n");
    printf("Enter your name: ");
    std::string name;
    std::cin >> name;
    Users user;
    user = Users(name, "listofbc.txt");
    Blockchain blockchain;
    if (ch == 'n') {
        //load file 
        user.GetChain()->loadBlockFromFile(name);
//        blockchain.loadBlockFromFile();
        printf("\nIs chain still valid? %d\n", user.GetChain()->isChainValid());
    }
    else if (ch == 'y') {
        //create new file and genesis block
        //user.CreateFile(name);
        listOfBC.open("listofbc.txt", std::fstream::in);
        std::string genesis;   
        getline(listOfBC, genesis);
        listOfBC.close();
        if (genesis ==  "") {
            user.GetChain()->createGenesisBlock(name);
        }
        else {
            user.CreateFile(name);
            user.GetChain()->loadGenisisBlockFromFile(genesis);
        }
        listOfBC.open("listofbc.txt", std::fstream::out | std::fstream::app);
        std::string filename = name + ".txt";
        listOfBC << filename << std::endl;
        listOfBC.close();
        //blockchain.createGenesisBlock();
    }
    // Data for first block
    time_t data1Time;
    int mode = 0;
    while (true) {
        std::cout << std::endl;
        user.GetChain()->alertStorage();
        std::cout << std::endl;
        printf("==================MENU=================\n");
        printf("(1) Add block\n");
        printf("(2) Print all block\n");
        printf("(3) Search block by package Code\n");
        printf("(4) Check the amount of rice in storage\n");
        printf("(5) Check the profit of interprise\n");
        printf("(6) Count the number of oders from date to date\n");
        printf("(7) Print Bar Chart of a year\n");
        printf("===================================\n");
        scanf_s("%d", &mode);

        switch (mode)
        {
        case 1:
        {
            Data data;
            data.addData();
            if (data.mode == 0 && data.amount > user.GetChain()->amountInStorage())
                std::cout << "Can't export! Storage is not enough\n";
            else
                user.addBlock(data);
            break;
        }
        case 2:
        {
            user.GetChain()->printChain();
            break;
        }
        case 3:
        {
            std::string packageCode;
            printf("Enter packageCode: ");
            std::cin >> packageCode;
            user.GetChain()->searchPackageCode(packageCode);
            break;
        }
        case 4:
        {
            double amount = user.GetChain()->amountInStorage();
            std::cout << "There are " << amount << "kg in Warehouse";
            break;
        }
        case 5:
        {
            user.GetChain()->profitOfInter();
            break;
        }
        case 6:
        {
            int m1, m2, y1, y2;
            std::cout << "From month:";
            std::cin >> m1;
            std::cout << "year:";
            std::cin >> y1;
            std::cout << std::endl;
            std::cout << "To month:";
            std::cin >> m2;
            std::cout << " year:";
            std::cin >> y2;
            std::cout << std::endl;
            user.GetChain()->searchFromDatetoDate(m1, y1, m2, y2);
            break;
        }
        case 7:
        {
            int year;
            std::cout << "Enter the year:";
            std::cin >> year;
            std::cout << std::endl;
            user.GetChain()->barChartOfYear(year);
        }
        default:
            break;
        }

    }

    return 0;
}