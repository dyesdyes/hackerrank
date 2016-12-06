#include "consoleInputReader.h"

class MaximizingXOR {

public:
	void solve(){
		int L = getNextIntInput();
		int R = getNextIntInput();

		int max = 0;
		for(int i = L; i < R; ++i){
			for(int j = L + 1; j <= R; ++j){
				if ((i ^ j) > max){
					max = (i ^ j);
				}
			}
		}
    
		std::cout << max << std::endl;
	}
};