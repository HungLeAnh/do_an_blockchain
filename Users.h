#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <stdio.h>
#include<vector>

#include "Blockchain.h"
#include "Data.h"

class Users
{
public:
	Users(std::string name,std::string chechlist);
	Users();
	void CreateFile(std::string name);
	void Update(Data data);
	bool CheckBlockChain();
	Blockchain* GetChain();
	void addBlock(Data data);
	bool CheckBlock(Block a,Block b);
private:
	std::string name;
	std::string checklist;
	Blockchain userBlock;
};

