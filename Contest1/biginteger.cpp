#include <iostream>
#include <vector>
#include <string>

int myMax(int a, int b);
int myMin(int a, int b);

class BigInteger {
	// TODO operations to realize:
	//  +
	//  +=
	//  -
	//  -=
	//  /
	//  /=
	//  %
	//  %=
	//  унарный минус
	//  префиксный ++
	//  постфиксный ++
	//  префиксный --
	//  постфиксный --
	//  there are more options (литеральный суффикс)


	std::vector<int> number;
	int sign = 0; // "0" --> 0, "1" --> positive, "-1" --> negative

 public:

	int size() const {
		return this->number.size();
	}

	int at(int position) const {
		return this->number[position];
	}

	int getSign() const {
		return this->sign;
	}

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
		this->sign = 1;
		if (str[0] == '-') {
			this->sign = -1;
			str = str.substr(1, str.length());
		}
		if (str == "0") {
			this->sign = 0;
			this->number = std::vector<int>(1);
			this->number.push_back(0);
		} else {
			this->number = std::vector<int>(str.length());

			for (int i = 0; i < str.length(); ++i) {
				this->number[i] = int(str[str.length() - 1 - i] - '0');
			}
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

	explicit operator int() { // prints an error line if current number is not compared to int
		int result = 0;
		try {
			result = std::stoi(this->toString());
		} catch (...) {
			std::cout << std::endl << "ERROR: current BigInteger is not compared to int" << std::endl;
		}
		return result;
	}

	explicit operator bool() { // prints an error line if current number is not compared to int
		if (this->sign == 0)
			return false;
		return true;
	}

	BigInteger& operator +=(const BigInteger& a) {
		if (this->sign == 0) {
			this->number = a.number;
			this->sign = a.sign;
			return *this;
		}
		if (a.sign == 0)
			return *this;
		if (a.sign * this->sign > 0) { // both positive or both negative
			int remainder = 0;
			// filling with 0 this number
			for (int i = this->number.size(); i < a.size(); ++i) {
				this->number.push_back(0);
			}

			// summing
			for (int i = 0; i < myMax(this->number.size(), a.size()); ++i) {
				int toAdd = i < a.size() ? a.number[i] : 0;
				this->number[i] += toAdd + remainder;
				remainder = this->number[i] / 10;
				this->number[i] %= 10;
			}
			if (remainder > 0)
				this->number.push_back(remainder);
		} else { // one is positive, one is negative

		}
		return *this;
	}

};
////////////////////////////////////////////////////////////////////////////////


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

bool operator <(const BigInteger& a, const BigInteger& b) {
	bool result = false; // remains false if a == b
	if (a.getSign() == b.getSign()) {
		if (a.size() == b.size()) {
			for (int i = a.size() - 1; i >= 0; --i) {
				if (a.at(i) == b.at(i))
					continue;
				result = a.at(i) < b.at(i);
				break;
			}
		} else {
			if (a.getSign() > 0) {
				result = a.size() < b.size() ? true : false; // in case of positive numbers
			} else {
				result = a.size() > b.size() ? true : false; // in case of negative numbers
			}
		}
	} else {
		result = a.getSign() < b.getSign() ? true : false; // in case a >= 0, b < 0 etc
	}
	return result;
}

bool operator >(const BigInteger& a, const BigInteger& b) {
	return b < a;
}

bool operator ==(const BigInteger& a, const BigInteger& b) {
	return !(a < b) && !(a > b);
}

bool operator <=(const BigInteger& a, const BigInteger& b) {
	return !(a > b);
}

bool operator >=(const BigInteger& a, const BigInteger& b) {
	return !(a < b);
}

bool operator !=(const BigInteger& a, const BigInteger& b) {
	return !(a == b);
}



int main() {
	BigInteger a;
	BigInteger b;
	std::cin >> a >> b;
	std::cout << "a == " << a << std::endl;
	std::cout << "b == " << b << std::endl;

	a += b;
	std::cout << "new a == a + b: " << a << std::endl;
}

int myMax(int a, int b) {
	return a > b ? a : b;
}

int myMin(int a, int b) {
	return a < b ? a : b;
}
