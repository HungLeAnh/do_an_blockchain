#pragma once
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
//
//  Data.h
//  BlockChainExample
//
//  Created by Jon on 1/10/18.
//  Copyright © 2018 Crypto Enthusiasts. All rights reserved.
//

#ifndef Data_h
#define Data_h

struct Data
{
    bool mode=0;          // true - in ; false - out
    double amount=0;
    double price=0;
    std::string date="null";
    std::string packageCode="null";
    std::string address="null";
    std::string name="null";
    std::string type="null";
    time_t timestamp;

    Data() {};

    Data(bool _mode, double _amt, double _price, std::string _packageCode, std::string _name,
        std::string _address, std::string _type, std::string _date, time_t _time)
    {
        mode = _mode;
        amount = _amt;
        price = _price;
        packageCode = _packageCode;
        address = _address;
        name = _name;
        type = _type;
        timestamp = _time;
        date = _date;
    };
    void addData() {
        printf("Enter mode: ");
        std::cin >> mode;
        printf("Enter amount: ");
        std::cin >> amount;
        printf("Enter price: ");
        std::cin >> price;
        printf("Enter date: ");
        std::cin >> date;
        printf("Enter package Code: ");
        std::cin >> packageCode;
        printf("Enter address: ");
        std::cin.ignore();
        std::getline(std::cin, address);
        printf("Enter name: ");
        //std::cin.ignore();
        std::getline(std::cin, name);
        printf("Enter type: ");
        //std::cin.ignore();
        std::getline(std::cin, type);
        time_t newtime;
        timestamp = time(&newtime);
    }
    void addDataFromFile(std::fstream& savedData) {
        savedData >> mode;
        savedData >> amount;
        savedData >> price;
        savedData >> packageCode;
        savedData >> date;
        savedData.ignore();
        getline(savedData,address);
        getline(savedData, name);
        getline(savedData, type);
        savedData >> timestamp;
    }
};

#endif /*Data_h */
