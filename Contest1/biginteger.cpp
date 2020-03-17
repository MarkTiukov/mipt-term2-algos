#include <iostream>
#include <vector>
#include <string>

class BigInteger {
	// TODO operations to realize:
	//  + вне
	//  -
	//  -=
	//  /
	//  /=
	//  %
	//  %=
	//  унарный минус внутри
	//  префиксный ++ вне
	//  постфиксный ++
	//  префиксный --
	//  постфиксный --
	//  there are more options (литеральный суффикс)


	std::vector<int> number;
	int sign = 0; // "0" --> 0, "1" --> positive, "-1" --> negative

	bool absBigger(const BigInteger& a) { // abs(this) > abs(a)
		bool result = false; // remains false if a == b
			if (a.size() == this->size()) {
				for (int i = a.size() - 1; i >= 0; --i) {
					if (a.at(i) == this->at(i))
						continue;
					result = a.at(i) < this->at(i);
					break;
				}
			} else {
				result = a.size() < this->size() ? true : false;
			}
		return result;
	}

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

	BigInteger(long long number) {
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

	BigInteger(long number) {
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

	BigInteger operator -()  const {
		BigInteger result = *this;
		result.sign *= -1;
		return result;
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
			for (int i = 0; i < this->number.size() || i < a.size(); ++i) {
				int toAdd = i < a.size() ? a.number[i] : 0;
				this->number[i] += toAdd + remainder;
				remainder = this->number[i] / 10;
				this->number[i] %= 10;
			}
			if (remainder > 0)
				this->number.push_back(remainder);
		} else { // one is positive, one is negative
			int isBigger = false;
			if (this->absBigger(a))
				isBigger = true;
			this->sign = isBigger ? this->sign : a.sign;
			int remainder = 0;
			for (int i = 0; i < this->number.size() || i < a.size(); ++i) {
				if (i >= this->number.size()) {
					this->number.push_back(0);
				}
				int currentDigit = 0;
				if (i < a.number.size())
					currentDigit = a.number[i];
				if (isBigger) {
					this->number[i] = this->number[i] - currentDigit + remainder;
				} else {
					this->number[i] = currentDigit - this->number[i] + remainder;
				}
				if (this->number[i] < 0) {
					this->number[i] += 10;
					remainder = -1;
				} else remainder = 0;
			}
			while (this->number.size() > 1 && this->number[this->number.size() - 1] == 0) {
				this->number.pop_back();
			}
			if (this->number.size() == 1 && this->number[0] == 0)
				this->sign = 0;

		}
		return *this;
	}



};
////////////////////////////////////////////////////////////////////////////////


BigInteger operator +(const BigInteger& a, const BigInteger& b) {
	BigInteger result(a);
	result += b;
	return result;
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

	std::cout << "a == " << a <<  std::endl;
	std::cout << "b == " << b << std::endl;
	BigInteger c = a + b;
	// a += b;
	std::cout << "a + b == " << c << std::endl;
}