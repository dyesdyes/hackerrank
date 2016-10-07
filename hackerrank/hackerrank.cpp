#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <cstdlib>

#include "solutions/EmaSupercomputer.h"

using namespace std;

int getNextIntInput(){
	int value;
	std::cin >> value;

	return value;
}

std::vector<std::string> getNextStringInputs(int count){
	std::string empty;
	std::getline(std::cin,empty);

	std::vector<std::string> values;
	for (int i = 0; i < count; ++i){
		std::string nextValue;
		std::getline(std::cin,nextValue);
		values.push_back(nextValue);
	}

	return values;
}

int main()
{
	int row = getNextIntInput();
	int column = getNextIntInput();
	std::vector<std::string> grid = getNextStringInputs(row);
	
	EmaSupercomputer e;
	std::cout << e.testValidPluses(grid) << std::endl;

	return 0;
}