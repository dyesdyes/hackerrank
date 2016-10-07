#pragma once

#include <vector>
#include <algorithm>
#include <sstream>
#include "../consoleInputReader.h"

class MaximumPerimeterTriangle {
public:
	std::string displayMaximumPerimeterTriangle(std::vector<int> values){
		std::sort(values.begin(),values.end());

		std::vector<int> chosenValues;
		int i = values.size();
		while (chosenValues.size() < 3 && --i >= 0){
			if (chosenValues.size() == 2){
				int a = chosenValues.at(0);
				int b = chosenValues.at(1);
				int c = values.at(i);
				if (a >= b + c){
					chosenValues.erase(chosenValues.begin());
				}

			}
			chosenValues.push_back(values.at(i));
		}

		if (chosenValues.size() == 3){
			std::ostringstream oss;
			oss << chosenValues.at(2) << " " << chosenValues.at(1) << " " << chosenValues.at(0) << std::endl;
			return oss.str();
		}
		return "-1";
	}
};