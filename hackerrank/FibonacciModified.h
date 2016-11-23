#include <vector>
#include <sstream>

#include "consoleInputReader.h"

class BigIntVector;

BigIntVector operator*(BigIntVector left,const BigIntVector& right);
BigIntVector operator+(BigIntVector left,const BigIntVector& right);
BigIntVector operator-(BigIntVector left,const BigIntVector& right);


/* extremely shitty code that tries to create a BigInt class, but it's still too slow for hackerrank and I'm too lazy right now */
// TODO just clean this up; it is really bad
class BigIntVector{
public:
	/*
	BigIntVector(BigIntVector&& move){
		value = move.value;
	}
	*/

	BigIntVector(int val){
		while(val > 0){
			value.push_back(val % 10);
			val /= 10;
		}
	}

	friend bool operator<(BigIntVector& left,const BigIntVector& right){
		if (left.size() != right.size()){
			return left.size() < right.size();
		}

		for (int i = left.size() - 1; i >= 0; --i){
			if (left.at(i) != right.at(i)){
				return left.at(i) < right.at(i);
			}
		}

		return false;
	}

	BigIntVector& operator+=(const BigIntVector& right){
		int remainder = 0;
		for (int i = 0; i < std::max(size(),right.size()); ++i){
			if (i >= size()){
				value.push_back(0);
			}
			int r = (i < right.size()) ? right.at(i) : 0;
			int res = at(i) + r + remainder;
			value[i] = res % 10;
			remainder = res / 10;
		}
		if (remainder != 0){
			value.push_back(remainder);
		}

		return *this;
	}

	BigIntVector& operator-=(const BigIntVector& right){
		if (*this < right){
			return *this; // just return whatever, we won't encounter this in our case
		}

		for (int i = 0; i < right.size(); ++i){
			if (at(i) < right.at(i)){
				value[i] += 10;
				int j = i;
				while(++j < size()){
					if (at(j) > 0){
						value[j]--;
						break;
					}else {
						value[j] = 9;
					}
				}
			}

			value[i] -= right.at(i);
		}

		return *this;
	}

	BigIntVector& operator*=(const BigIntVector& right){
		BigIntVector result = karatsubaMultiply(*this,right);

		for (int i = 0; i < result.size();++i){
			if (i >= size()){
				value.push_back(result.at(i));
			} else {
				value[i] = result.at(i);
			}
		}
		
		return *this;
	}

	std::string str(){
		std::stringstream ss;
		bool MSD = false;
		for (int i = size() - 1; i >= 0; --i){
			if (!MSD){
				if (at(i) == 0)
					continue;
				else
					MSD = true;
			}
			ss << at(i);
		}
		return ss.str();
	}

private:
	BigIntVector(){}
	BigIntVector(std::vector<short> val) : value(val){}

	BigIntVector karatsubaMultiply(const BigIntVector& left,const BigIntVector& right){
		if (left.size() == 1 && right.size() == 1){
			return BigIntVector(left.at(0) * right.at(0));
		}
		if (left.size() == 1 || right.size() == 1){
			return multiply(left,right);
		}

		BigIntVector x1 = getSecondHalfOfDigits(left);
		BigIntVector x2 = getFirstHalfOfDigits(left);
		BigIntVector y1 = getSecondHalfOfDigits(right);
		BigIntVector y2 = getFirstHalfOfDigits(right);

		BigIntVector a = karatsubaMultiply(x1,y1);
		BigIntVector c = karatsubaMultiply(x2,y2);
		BigIntVector b = karatsubaMultiply(x1 + x2,y1 + y2) - a - c;
		
		int size = x2.size();
		return powBase10(a,2*size) + powBase10(b,size) + c;
	}

	BigIntVector multiply(const BigIntVector& left,const BigIntVector& right){
		BigIntVector out;
		for (int i = 0; i < left.size(); ++i){
			std::vector<short> val(i,0);
			int remainder = 0;
			for (int j = 0; j < right.size(); ++j){
				int res = left.at(i) * right.at(j) + remainder;
				val.push_back(res % 10);
				remainder = res / 10;
			}
			if (remainder != 0){
				val.push_back(remainder);
			}
			out += BigIntVector(val);
		}
		return out;
	}

	BigIntVector powBase10(const BigIntVector& left, int power){
		std::vector<short> base(power,0);
		appendValue(left,base);
		return BigIntVector(base);
	}

	BigIntVector getFirstHalfOfDigits(BigIntVector val){
		std::vector<short> vals;
		for (int i = 0; i < val.size() / 2; ++i){
			vals.push_back(val.at(i));
		}
		return BigIntVector(vals);
	}

	BigIntVector getSecondHalfOfDigits(BigIntVector val){
		int s = val.size() / 2;
		std::vector<short> vals;
		for (int i = s; i < val.size(); ++i){
			vals.push_back(val.at(i));
		}
		return BigIntVector(vals);
	}

	void appendValue(const BigIntVector& val, std::vector<short>& appended){
		for (int i = 0; i < val.size();++i){
			appended.push_back(val.at(i));
		}
	}

	int size() const{
		return value.size();
	}

	int at(int i) const{
		return value[i];
	}
	
	std::vector<short> value;
};

BigIntVector operator*(BigIntVector left,const BigIntVector& right){
	left *= right;
	return left;
}

BigIntVector operator+(BigIntVector left,const BigIntVector& right){
	left += right;
	return left;
}

BigIntVector operator-(BigIntVector left,const BigIntVector& right){
	left -= right;
	return left;
}

class FibonacciModified {
public:
	void solve(){
		int t1 = getNextIntInput();
		int t2 = getNextIntInput();
		int n = getNextIntInput();

		std::vector<BigIntVector> values;
		values.push_back(t1);
		values.push_back(t2);
		for (int i = 2; i < n;++i){
			BigIntVector next = values[i-2] + values[i-1] * values[i-1];
			values.push_back(next);
		}

		std::cout << values[n-1].str() << std::endl;
	}
};