#include <iostream>
#include <vector>
#include <string>

class BigInteger {
	std::vector<int> number;

	int size() const {
		return this->number.size();
	}

	int at(int position) const {
		return this->number[position];
	}

 public:

	BigInteger() {
		this->number = std::vector<int>(1, 0);
	}

	

	BigInteger operator +=(const BigInteger& a) {
		int remainder = 0;
		for (int i = 0; i < number.size() || i < a.size(); ++i) {
			this->number[i] += a.at(i) + remainder;
			remainder = this->number[i] /= 10;
			this->number[i] %= 10;
		}
	}

};

BigInteger operator +(const BigInteger& a, const BigInteger& b) {

}

int main() {

}