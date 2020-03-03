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

	BigInteger(int number) {
		this->number = std::vector<int>();
		for (int i = 0; number / 10 > 0; ++i) {
			this->number.push_back(number % 10);
			number /= 10;
		}
		this->number.push_back(number);
	}

	std::string toString() const {
		std::string result = "";
		for (int i = this->number.size() - 1; i >= 0; --i) {
			result += std::to_string(this->number[i]);
		}
		return result;
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

std::ostream& operator <<(std::ostream& out, const BigInteger& a) {
	out << a.toString();
	return out;
}

int main() {
	BigInteger big = BigInteger(1234567890);
	std::cout << big << std::endl;
}