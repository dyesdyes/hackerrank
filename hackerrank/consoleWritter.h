#pragma once

#include <sstream>
#include <iostream>
#include <string>
#include <vector>

void output(const std::vector<int> &vec){
	std::ios_base::sync_with_stdio(false);
	std::stringstream ss;
	for(int i = 0; i < vec.size(); ++i){
		if (i > 0){
			ss << " ";
		}
		ss << vec.at(i);
	}
	std::cout << ss.str() << std::endl;
}

void output(const std::vector<int> &vec,const std::string &ifEmpty){
	if (vec.size() == 0){
		std::cout << ifEmpty << std::endl;
		return;
	}
	for(int i = 0; i < vec.size(); ++i){
		std::cout << vec.at(i) << " ";
	}
	std::cout << std::endl;
}

void output(const std::vector<std::string> &grid){
	for(int i = 0; i < grid.size(); ++i){
		std::cout << grid[i] << std::endl;
	}
}