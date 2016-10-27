#include <vector>

#include "consoleInputReader.h"

class SansaAndXOR {
public:
	void solve(){
		int caseCount = getNextIntInput();
		for(int i = 0; i < caseCount; ++i){
			std::vector<int> values = parseInputs();
			int N = values.size();
			if (N % 2 == 0){
				std::cout << 0 << std::endl;
			} else{
				int val = 0;
				for (int j = 0; j < N; j+=2){
					val ^= values[j];
				}
				std::cout << val << std::endl;
			}
		}
	}

private:
	std::vector<int> parseInputs(){
		int valCount = getNextIntInput();
		std::vector<int> values;
		for(int i = 0; i < valCount; ++i){
			int a = getNextIntInput();
			values.push_back(a);
		}
		return values;
	}
};
