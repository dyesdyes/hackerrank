#include <vector>
#include <unordered_set>

#include "consoleInputReader.h"

class LonelyInteger {

public:
	void solveBitManipulation(){
		std::vector<int> values = parseInputs();

		int a = 0;
		for (int i = 0; i < values.size(); ++i){
			a ^= values[i];
		}

		std::cout << a << std::endl;
	}

	void solveNormal(){
		std::vector<int> values = parseInputs();

		std::unordered_set<int> uniqueValues;

		for (int i = 0; i < values.size(); ++i){
			if (uniqueValues.count(values[i]) > 0){
				uniqueValues.erase(values[i]);
			} else {
				uniqueValues.insert(values[i]);
			}
		}

		std::cout << *uniqueValues.begin() << std::endl;
	}

private:

	std::vector<int> parseInputs(){
		int n = getNextIntInput();
		std::vector<int> values;
		for (int i = 0; i < n; ++i){
			int a = getNextIntInput();
			values.push_back(a);
		}
		return values;
	}
};

