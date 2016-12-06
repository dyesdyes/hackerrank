#include <iostream>

class XorSequence{
public:
	void solve(){
		int Q;
		std::cin >> Q;
		for(int a0 = 0; a0 < Q; a0++){
			long L;
			long R;
			std::cin >> L >> R;

			long result = 0;
			while (L % 4 != 0 && L <= R){
				result ^= getArrayValue(L);
				L++;
			}
			while (R % 4 != 3 && L <= R){
				result ^= getArrayValue(R);
				R--;
			}

			long div = (R + 1 - L) / 4;
			result ^= (div % 2 == 0) ? 0 : 2;
		
			std::cout << result << std::endl;
		}
	}

private:
	long getArrayValue(long index){
		switch(index % 4){
			case 0:
				return index;
			case 1:
				return 1;
			case 2:
				return index + 1;
			case 3:
				return 0;
		}
		return -1;
	}
};

