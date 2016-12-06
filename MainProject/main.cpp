
#include <iostream>
#include <string>

#include "ShortPalindrome.h"

int main(){
	std::string val;
	std::getline(std::cin,val);

	ShortPalindrome g;
	std::cout << g.solve(val) << std::endl;

	return 0;
}