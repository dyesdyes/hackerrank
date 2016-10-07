#pragma once

#include <iostream>
#include <string>
#include <vector>

int getNextIntInput(){
	int value;
	std::cin >> value;

	return value;
}

std::vector<int> getNextIntInputs(){
	int size;
	std::cin >> size;

	std::vector<int> values(size);
	for (int i = 0; i < size; ++i){
		int nextValue;
		std::cin >> nextValue;
		values.push_back(nextValue);
	}

	return values;
}

std::vector<std::string> getNextStringInputs(){
	int size;
	std::cin >> size;

	std::string empty;
	std::getline(std::cin,empty);

	std::vector<std::string> values;
	for (int i = 0; i < size; ++i){
		std::string nextValue;
		std::getline(std::cin,nextValue);
		values.push_back(nextValue);
	}

	return values;
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