#include <iostream>
#include <cmath>

#include "consoleInputReader.h"

class SumvsXOR {

public:
	void solve(){
		unsigned long long n = getNextUnsignedLongLongInput();

		unsigned long long temp = n;
		int oneCount = 0;
		int i = 0;
		while(temp > 0) {
			if ((temp & 1) == 1){
				++oneCount;
			}
			i++;
			temp >>= 1;
		}
		unsigned long long computation = pow(2,i - oneCount);
    
		std::cout << computation << std::endl;
	}
};