#pragma once

#include <algorithm>
#include <string>

class BiggerIsGreater {

public:
	std::string nextPermutation(std::string value){
		int i = value.length() - 2;
		char maxChar = value.back();
		while (i >= 0){
			char currentChar = value[i];
			if (currentChar < maxChar){
				std::size_t posToSwapWith = getNextHigherChar(i,value);
				swap(i,posToSwapWith,value);
				break;
			} else{
				maxChar = currentChar;
			}
			--i;
		}

		if (i >= 0){
			std::string::iterator ite = std::next(value.begin(),i+1);
			std::sort(ite,value.end());
			return value;
		}
		return "no answer";
	}

private:

	void swap(std::size_t pos1,std::size_t pos2,std::string& value){
		char temp = value[pos1];
		value[pos1] = value[pos2];
		value[pos2] = temp;
	}

	std::size_t getNextHigherChar(std::size_t pos,std::string value){
		std::size_t nextHigherPos = pos;
		for (int i = pos + 1; i < value.size(); ++i){
			if (value[i] > value[pos] && (pos == nextHigherPos || value[i] < value[nextHigherPos])){
				nextHigherPos = i;
			}
		}
		return nextHigherPos;
	}
};