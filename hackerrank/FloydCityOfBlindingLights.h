#include <climits>
#include <vector>
#include <iostream>

#include "consoleInputReader.h"

class FloydCityOfBlindingLights {
public:
	FloydCityOfBlindingLights(){}
	~FloydCityOfBlindingLights(){}

	void solve(){
		std::vector<std::pair<int,int>> questions;
		int nodeCount = getNextIntInput();
		std::vector<std::vector<int>> grid(nodeCount,std::vector<int>(nodeCount,INT_MAX));
		parseInput(nodeCount,questions,grid);

		for(int k = 0; k < nodeCount;++k){
			for(int i = 0; i < nodeCount;++i){
				for(int j = 0; j < nodeCount;++j){
					if (grid[i][k] != INT_MAX && grid[k][j] != INT_MAX && grid[i][j] > grid[i][k] + grid[k][j]){
						grid[i][j] = grid[i][k] + grid[k][j];
					}
				}
			}
		}

		for(int i = 0; i < questions.size(); ++i){
			if (questions[i].first < nodeCount && questions[i].second < nodeCount){
				int minPathWeight = grid[questions[i].first][questions[i].second];
				int valToDisplay = (minPathWeight == INT_MAX) ? -1 : minPathWeight;
				std::cout << valToDisplay << std::endl;
			}
		}
	}

private:
	void parseInput(int nodeCount,std::vector<std::pair<int,int>>& questions,std::vector<std::vector<int>>& grid){
		int edgeCount = getNextIntInput();
		for(int i = 0; i < nodeCount; ++i){
			grid[i][i] = 0;
		}
		for(int i = 0; i < edgeCount; ++i){
			int a = getNextIntInput() - 1;
			int b = getNextIntInput() - 1;
			int weight = getNextIntInput();
			grid[a][b] = weight;
		}
		int queryCount = getNextIntInput();
		for(int i = 0; i < queryCount; ++i){
			int a = getNextIntInput() - 1;
			int b = getNextIntInput() - 1;
			questions.push_back(std::pair<int,int>(a,b));
		}
	}
};
