#include "consoleInputReader.h"

class FlippingBits {

public:
	void solve(){
		int count = getNextIntInput();
		for(int i = 0; i < count; ++i){
			unsigned int a = getNextUnsignedIntInput();

			std::cout << ~a << std::endl;
		}
	}
};
