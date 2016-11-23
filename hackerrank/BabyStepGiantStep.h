#include "consoleInputReader.h"

class BabyStepGiantStep {
public:
	void solve(){
		int testCases = getNextIntInput();
		for (int i = 0; i < testCases; ++i){
			int a = getNextIntInput();
			int b = getNextIntInput();
			int d = getNextIntInput();
			std::cout << solveCase(a,b,d) << std::endl;
		}
	}

private:
	int solveCase(int a, int b, int d){
		if (d == 0)
			return 0;

		int max = std::max(a,b);
		int min = std::min(a,b);
		
		if (d == min)
			return 1;

		if (d < max && d != min)
			return 2;

		int out = d / max;
		int rest = d % max;

		if (rest != 0){
			return out + 1;
		}
		return out;
	}
};