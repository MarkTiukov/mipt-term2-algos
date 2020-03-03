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
		//std::cout << "here2" << std::endl;
		this->number = std::vector<int>(1, 0);
	}

	std::string toString() const {
		//std::cout << "HERE" << std::endl;
		std::string result = "";
		for (int i : this->number) {
			//std::cout << "i " << i << "; " << this->number[i] << std::endl;
			result += std::to_string(this->number[i]);
		}
		//std::cout << result << std::endl;
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
	//std::cout << "here" << std::endl;
	out << a.toString();
	return out;
}

int main() {
	BigInteger big = BigInteger();
	std::cout << "My biginteger equals -- " <<  big << std::endl;
}