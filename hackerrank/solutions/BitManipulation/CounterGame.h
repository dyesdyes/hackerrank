#include <string>

#include "consoleInputReader.h"

class CounterGame {

public:
	void solve(){
		int caseCount = getNextIntInput();
		for(int i = 0; i < caseCount; ++i){
			unsigned long long counter = getNextUnsignedLongLongInput();

			std::cout << findWinner(counter) << std::endl;
		}
	}

private:
	int setBits(unsigned long long int n) {
		int count = 0 ;
		while(n) {
    		n &= (n-1) ;
			count ++ ;
		}
		return count ;
	}

	std::string findWinner(unsigned long long counter){
		int bits = setBits(counter-1); // counter - 1 because substracting by 1 will flip the right most bits
		return bits % 2 == 0 ? "Richard" : "Louise";
	}
};