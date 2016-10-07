#pragma once

#include <iostream>
#include <vector>

class BombermanGame {
public:
	BombermanGame(){}
	~BombermanGame(){}

	void play(std::vector<std::string> &charGrid,int turn){
		if (turn == 1){
			return;
		}

		if (turn % 2 == 0){
			fillCompletelyWithBombs(charGrid);
			return;
		}

		turn = (turn % 4 == 1) ? 5 : 3;

		std::vector<std::vector<unsigned int>> grid(charGrid.size(),std::vector<unsigned int>(charGrid[0].length()));
		toIntGrid(charGrid,grid);

		for (int currentTurn = 3; currentTurn <= turn; ++currentTurn){
			if (currentTurn % 2 == 0){
				fillEmptyCellsWithBombs(grid,currentTurn+SHIFT);
			}
			else{
				detonateBombs(grid,currentTurn+SHIFT);
			}
		}

		toCharGrid(charGrid,grid);
	}

private:
	static const int NO_BOMB = 0;
	static const int SHIFT = 1; // to save the value 0 for no bomb, we shift everything by 1, so the initial bomb is at turn 1 (and not 0)

	void fillCompletelyWithBombs(std::vector<std::string> &grid){
		for(int row = 0; row < grid.size(); ++row){
			for(int column = 0; column < grid[row].length(); ++column){
				grid[row][column] = 'O';
			}
		}
	}
	
	void toIntGrid(std::vector<std::string> &grid,std::vector<std::vector<unsigned int>> &intGrid){
		for(int row = 0; row < grid.size(); ++row){
			for(int column = 0; column < grid[row].length(); ++column){
				intGrid[row][column] = (grid[row][column] == '.') ? 2 + SHIFT : SHIFT;
			}
		}
	}

	void toCharGrid(std::vector<std::string> &grid,std::vector<std::vector<unsigned int>> &intGrid){
		for(int row = 0; row < intGrid.size(); ++row){
			for(int column = 0; column < intGrid[row].size(); ++column){
				grid[row][column] = (intGrid[row][column] == 0) ? '.' : 'O';
			}
		}
	}

	void fillEmptyCellsWithBombs(std::vector<std::vector<unsigned int>> &grid,int currentTurn){
		for(int row = 0; row < grid.size(); ++row){
			for(int column = 0; column < grid[row].size(); ++column){
				if (grid[row][column] == NO_BOMB){
					grid[row][column] = currentTurn;
				}
			}
		}
	}

	// goes through the grid and detonates all the bombs that should be detonated during this turn
	void detonateBombs(std::vector<std::vector<unsigned int>> &grid,int currentTurn){
		for(int row = 0; row < grid.size(); ++row){
			for(int column = 0; column < grid[row].size(); ++column){
				if (grid[row][column] == currentTurn - 3){
					detonateBomb(grid,row,column,currentTurn);
				}
			}
		}
	}

	// detonates the bomb placed at the given position (it assumes it IS a bomb, no check)
	void detonateBomb(std::vector<std::vector<unsigned int>> &grid,int row,int column,int currentTurn){
		if (row - 1 >= 0){
			if (grid[row-1][column] == currentTurn - 3){
				detonateBomb(grid,row-1,column,currentTurn);
			} else{
				grid[row-1][column] = NO_BOMB;
			}
		}

		if (column - 1 >= 0){
			if (grid[row][column-1] == currentTurn - 3){
				detonateBomb(grid,row,column-1,currentTurn);
			} else{
				grid[row][column-1] = NO_BOMB;
			}
		}

		grid[row][column] = NO_BOMB;

		if (column + 1 < grid[row].size()){
			if (grid[row][column+1] == currentTurn - 3){
				detonateBomb(grid,row,column+1,currentTurn);
			} else{
				grid[row][column+1] = NO_BOMB;
			}
		}

		if (row + 1 < grid.size()){
			if (grid[row+1][column] == currentTurn - 3){
				detonateBomb(grid,row+1,column,currentTurn);
			} else{
				grid[row+1][column] = NO_BOMB;
			}
		}
	}
};