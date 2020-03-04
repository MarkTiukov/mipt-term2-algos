#include <iostream>
#include <vector>
#include <string>

class BigInteger {
	std::vector<int> number;
	int sign = 0; // "0" --> 0, "1" --> positive, "-1" --> negative

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
		if (number > 0)
			this->sign = 1;
		else
			this->sign = 0 ? number == 0 : -1;
		number = std::abs(number);
		for (int i = 0; number / 10 > 0; ++i) {
			this->number.push_back(number % 10);
			number /= 10;
		}
		this->number.push_back(number);
	}

	BigInteger(const BigInteger &a) {
		this->number = a.number;
		this->sign = a.sign;
	}

	BigInteger(std::string str) {
		if (str[0] == '-') {
			this->sign = -1;
			str = str.substr(1, str.length());
		}
		this->number = std::vector<int>(str.length());
		for (int i = 0; i < str.length(); ++i){
			this->number[i] = int(str[str.length() - 1 - i]-'0');
		}
	}

	std::string toString() const {
		std::string result = "";
		result += this->sign  == -1 ? "-" : "";
		for (int i = this->number.size() - 1; i >= 0; --i) {
			result += std::to_string(this->number[i]);
		}
		return result;
	}

	BigInteger operator +=(const BigInteger& a) {

	}

};

BigInteger operator +(const BigInteger& a, const BigInteger& b) {

}

std::ostream& operator <<(std::ostream& out, const BigInteger& a) {
	out << a.toString();
	return out;
}

std::istream& operator >>(std::istream& in, BigInteger& a) {
	std::string str;
	in >> str;
	a = BigInteger(str);
	return in;
}

int main() {
	BigInteger a;
	std::cin >> a;
	std::cout << a << std::endl;
}