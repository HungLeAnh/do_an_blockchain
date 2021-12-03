#include "Users.h"

Users::Users(std::string name, std::string checklist)
{
	this->name = name;
	this->checklist = checklist;
}

Users::Users()
{
}

void Users::CreateFile(std::string name)
{

}

void Users::Update(Data data)
{
	std::fstream listofbc;
	listofbc.open(checklist, std::fstream::in);
	//read checklist to get file name for checking
	while (!listofbc.eof())
	{
		std::string filename;
		getline(listofbc, filename);
		std::fstream updatefile;
		updatefile.open(filename, std::fstream::out|std::fstream::app);
		char checkEOF;
		//update data to all file

	}
}

bool Users::CheckBlockChain()
{
	std::fstream listofbc;
	listofbc.open(checklist, std::fstream::in);
	//read checklist to get file name for checking
	while (!listofbc.eof())
	{
		std::string filename;
		getline(listofbc, filename);
		std::fstream checkfile;
		checkfile.open(filename, std::fstream::in);
		char checkEOF;
		std::vector<Block> check;
		//read data from file with file name
		while (checkfile.get(checkEOF)) {
			checkfile.unget();
			int index;
			size_t hash, prehash;
			checkfile >> index;
			Data savedData;
			savedData.addDataFromFile(checkfile);
			checkfile >> hash;
			checkfile >> prehash;
			Block savedBlock(index, savedData, hash, prehash);
			check.push_back(savedBlock);
			char dumbChar = checkfile.get();
		}
		//Check this user chain with check
		std::vector<Block>::iterator Checkit=check.begin();
		std::vector<Block> thischain = userBlock.getChain();
		std::vector<Block>::iterator Thisit= thischain.begin();

		for (; Checkit != check.end(); ++Checkit,++Thisit)
		{
			Block currentCheckBlock = *Checkit;
			Block currentThisBlock = *Thisit;
			if (CheckBlock(currentCheckBlock, currentThisBlock)==false)
				return false;
		}
		checkfile.close();
	}
	return true;
}

Blockchain* Users::GetChain()
{
	return &userBlock;
}

void Users::addBlock(Data data)
{
	if (CheckBlockChain()) {
		this->userBlock.addBlock(data);
		Update(data);
	}
	else {
		printf("Chain is not valid to add new block");
	}
}

bool Users::CheckBlock(Block a,Block b)
{
	if (a.getIndex() == b.getIndex()) {
		if (a.getHash() == b.getHash()) {
			if (a.getPreviousHash() == b.getPreviousHash()) {
				return true;
			}
		}
	}
	return false;
}
