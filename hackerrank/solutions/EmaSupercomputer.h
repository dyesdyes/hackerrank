#pragma once

#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

struct ValidPlus{
	ValidPlus(){
		row = 0;
		column = 0;
		size = 0;
		maxSize = 0;
	}

	ValidPlus(size_t row,size_t column,size_t size){
		this->row = row;
		this->column = column;
		this->size = size;
		this->maxSize = size;
	}

	void reduce(){size--;}
	void restoreToMaxSize(){size = maxSize;}

	int area(){
		if (size == 0)
			return 0;
		return (size - 1) * 4 + 1;
	}

	size_t row;
	size_t column;
	size_t size;
	size_t maxSize;

	// checks they won't intersect
	bool isDistinct(ValidPlus other){
		if (size == 0 || other.size == 0){
			return true;
		}

		int difX = abs((int)row - (int)other.row);
		int difY = abs((int)column - (int)other.column);

		int minSize = size < other.size ? size - 1 : other.size - 1;
		int maxSize = size > other.size ? size - 1 : other.size - 1;

		// if same row
		if (difX == 0){
			return difY > minSize + maxSize;
		}
		
		// if same column
		if (difY == 0){
			return difX > minSize + maxSize;
		}

		if (difX > minSize && difY > minSize){
			return true;
		}
		if (difX <= minSize){
			return difY > maxSize;
		}
		if (difY <= minSize){
			return difX > maxSize;
		}
		return false;
	}

	bool operator<(const ValidPlus &other) const {
		return size > other.size; // dirty to sort in descending order right away
	}
};

class EmaSupercomputer {
public:
	int testValidPluses(std::vector<std::string> &grid){
		vector<ValidPlus> validPluses;
		findAllValidPluses(grid,validPluses);
		sort(validPluses.begin(),validPluses.end()); // sort in descending order
		return getMaxProductSize(validPluses);
	}

private:

	void findAllValidPluses(std::vector<std::string> &grid,vector<ValidPlus> &validPluses){
		for(int row = 0; row < grid.size(); ++row){
			for(int column = 0; column < grid[row].length(); ++column){
				if (grid[row][column] != 'B'){
					int validPlusSize = findValidPlusMaxSize(grid,row,column);
					ValidPlus validPlus(row,column,validPlusSize);
					validPluses.push_back(validPlus);
				}
			}
		}
	}

	int findValidPlusMaxSize(std::vector<std::string> &grid,int row,int column){
		int validPlusSize = 1;
		while(true){
			if (row - validPlusSize < 0 || row + validPlusSize >= grid.size()){
				break;
			}
			if (column - validPlusSize < 0 || column + validPlusSize >= grid[row].length()){
				break;
			}
			if (grid[row-validPlusSize][column] == 'B' || 
				grid[row+validPlusSize][column] == 'B' || 
				grid[row][column-validPlusSize] == 'B' || 
				grid[row][column+validPlusSize] == 'B'){
					break;
			}
			validPlusSize++;
		}
		return validPlusSize;
	}

	int getMaxProductSize(vector<ValidPlus> validPluses){
		int globalMax = 0;
		for (int i = 0; i < validPluses.size(); ++i){
			int localMax = 0;
			for (int j = 1; j < validPluses.size(); ++j){
				while(validPluses[i].size > 0 && !validPluses[i].isDistinct(validPluses[j])){ // reduce size until it doesn't intersect
					validPluses[i].reduce(); 
				}
				int local = validPluses[i].area() * validPluses[j].area();
				if (local > localMax){
					localMax = local;
				}
				int reducedSize = validPluses[i].size;
				validPluses[i].restoreToMaxSize();
			}
			if (localMax > globalMax){
				globalMax = localMax;
			}
		}

		return globalMax;
	}
};