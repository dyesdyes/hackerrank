#include <vector>

class AppleAndOrange {
public:
	std::pair<int,int> getAppleAndOrangeCountOnTheHouse(
		int startHouse,
		int endHouse,
		int appleTree,
		int orangeTree,
		int appleCount,
		int orangeCount,
		std::vector<int> apples,
		std::vector<int> oranges){

			int applesOnHouse = 0;
			for (int i = 0; i < apples.size(); ++i){
				if (apples[i] + appleTree >= startHouse && apples[i] + appleTree <= endHouse){
					applesOnHouse++;
				}
			}
			int orangesOnHouse = 0;
			for (int i = 0; i < oranges.size(); ++i){
				if (oranges[i] + orangeTree >= startHouse && oranges[i] + orangeTree <= endHouse){
					orangesOnHouse++;
				}
			}

			return std::pair<int,int>(applesOnHouse,orangesOnHouse);
	}


};