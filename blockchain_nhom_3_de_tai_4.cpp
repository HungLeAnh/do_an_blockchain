//
//  Block.cpp
//  BlockChainExample
//
//  Created by Jon on 1/10/18.
//  Copyright © 2018 Crypto Enthusiasts. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <vector>

#include "Data.h"
#include "Block.h"
#include "Blockchain.h"

using namespace std;

int main()
{
    // Start Blockchain
    
    char ch;
    printf("===================================\n");
    printf("Are you the initial chain? (y or n)");
    std::cin >> ch;
    Blockchain blockchain;
    if (ch == 'n') {
        blockchain.loadBlockFromFile();
        printf("\nIs chain still valid? %d\n", blockchain.isChainValid());
    }
    else if (ch == 'y') {
        blockchain.createGenesisBlock();
    }
        // Data for first block
        time_t data1Time;
        int mode = 0;
        //mode = 1 add block
        //mode = 2 print all block
        //mode = 3 search block by packageCode
        while (true) {
            printf("===================================\n");
            printf("(1) Add block\n");
            printf("(2) Print all block\n");
            printf("(3) Search block by package Code\n");
            printf("(4) Check the amount of rice in storage\n");
            printf("(5) Check the profit of interprise\n");
            printf("(6) Count the number of oders from date to date\n");
            printf("===================================\n");
            scanf_s("%d", &mode);

            switch (mode)
            {
            case 1: 
            {
                Data data;
                data.addData();
                blockchain.addBlock(data);
                break;
            }
            case 2:
            {
                blockchain.printChain();
                break;
            }
            case 3:
            {
                std::string packageCode;
                printf("Enter packageCode: ");
                std::cin >> packageCode;
                blockchain.searchPackageCode(packageCode);
                break;
            }
            case 4:
            {
                blockchain.amountInStorage();
                break;
            }
            case 5:
            {
                blockchain.profitOfInter();
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
                blockchain.searchFromDatetoDate(m1, y1, m2, y2);
                break;
            }
            default:
                break;
            }

    }

    //Data data1(1,3,55000,"031510215", "Joe", "1 VVN","st25","15/3/2021", time(&data1Time));
    //blockchain.addBlock(data1);

    //time_t data2Time;
    //Data data2(1, 1, 20000, "031510521", "Martha", "TP.HCM", "st25", "1/1/2021", time(&data2Time));
    //blockchain.addBlock(data2);

    //// Let's see what's in the blockchain blockchain!
    //blockchain.printChain();

    //// Is it valid?
    //printf("\nIs chain still valid? %d\n", blockchain.isChainValid());

    return 0;
}
