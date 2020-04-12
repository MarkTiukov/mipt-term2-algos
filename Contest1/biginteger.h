#include <iostream>
#include <vector>
#include <string>

class BigInteger {
    // TODO operations to realize:
    // Rational

    std::vector<int> number;
    int sign = 0; // "0" --> 0, "1" --> positive, "-1" --> negative

    bool absBigger(const BigInteger& a) { // abs(this) > abs(a)
        bool result = false; // remains false if a == b
        if (a.size() == this->size()) {
            for (size_t i = a.size(); i-- > 0;) { //size_t i = a.size() - 1; i >= 0; --i
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

    BigInteger& multiplyOnDegree10(int degree) {
        std::vector<int> tmp = std::vector<int>(degree, 0);
        for (int i : this->number){
            tmp.push_back(i);
        }
        this->number = tmp;
        return *this;
    }

 public:

    size_t size() const {
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

    BigInteger(const int num) {
        int number = num;
        this->number = std::vector<int>();
        if (number > 0)
            this->sign = 1;
        else
            this->sign = number == 0 ? 0 : -1;
        number = std::abs(number);
        while(number / 10 > 0) {
            this->number.push_back(number % 10);
            number /= 10;
        }
        this->number.push_back(number);
    }

    /*
     BigInteger(long long number) {
            this->number = std::vector<int>();
            if (number > 0)
                    this->sign = 1;
            else
                    this->sign = 0 ? number == 0 : -1;
            number = std::abs(number);
            while (number / 10 > 0) {
                    this->number.push_back(number % 10);
                    number /= 10;
            }
            this->number.push_back(number);
    }
    */

    /* BigInteger(long number) {
            this->number = std::vector<int>();
            if (number > 0)
                    this->sign = 1;
            else
                    this->sign = 0 ? number == 0 : -1;
            number = std::abs(number);
            while (number / 10 > 0) {
                    this->number.push_back(number % 10);
                    number /= 10;
            }
            this->number.push_back(number);
    } */

    BigInteger(const BigInteger& a) {
        this->number = a.number;
        this->sign = a.sign;
    }

    BigInteger(const std::string line) {
        std::string str = line;
        this->sign = 1;
        if (str[0] == '-') {
            this->sign = -1;
            str = str.substr(1, str.length());
        }
        if (str == "0") {
            this->sign = 0;
            this->number = std::vector<int>(1, 0);
        } else {
            while(str[0] == '0'){
                str = str.substr(1);
            }
            this->number = std::vector<int>(str.length());

            for (size_t i = 0; i < str.length(); ++i) {
                this->number[i] = int(str[str.length() - 1 - i] - '0');
            }
        }
    }

    std::string toString() const {
        std::string result = "";
        result += this->sign  == -1 ? "-" : "";
        for (size_t i = this->number.size(); i-- > 0;) { //size_t i = this->number.size() - 1; i >= 0; --i
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
            for (size_t i = this->number.size(); i < a.size(); ++i) {
                this->number.push_back(0);
            }
            // summing
            for (size_t i = 0; i < this->number.size() || i < a.size(); ++i) {
                int toAdd = i < a.size() ? a.number[i] : 0;
                this->number[i] += toAdd + remainder;
                remainder = this->number[i] / 10;
                this->number[i] %= 10;
            }
            if (remainder > 0)
                this->number.push_back(remainder);
        } else { // one is positive, one is negative
            bool isBigger = false;
            if (this->absBigger(a))
                isBigger = true;
            this->sign = isBigger ? this->sign : a.sign;
            int remainder = 0;
            for (size_t i = 0; i < this->number.size() || i < a.size(); ++i) {
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

    BigInteger& operator -=(const BigInteger& a) {
        *this += -a;
        return *this;
    }

    BigInteger& operator *=(const BigInteger& a);

    BigInteger& operator /=(const BigInteger& a);

    BigInteger& operator %=(const BigInteger& a);

    BigInteger& operator ++() {
        return *this += 1;
    }

    BigInteger operator ++(int) {
        BigInteger copy = *this;
        *this += 1;
        return copy;
    }

    BigInteger& operator --() {
        return *this -= 1;
    }

    BigInteger operator --(int) {
        BigInteger copy = *this;
        *this -= 1;
        return copy;
    }

    BigInteger absoluteValue() {
        BigInteger result = *this;
        result.sign *= result.sign;
        return result;
    }

};
////////////////////////////////////////////////////////////////////////////////


BigInteger operator +(const BigInteger& a, const BigInteger& b) {
    BigInteger result(a);
    result += b;
    return result;
}

BigInteger operator -(const BigInteger& a, const BigInteger& b) {
    BigInteger result(a);
    result -= b;
    return result;
}

BigInteger operator *(const BigInteger& a, const BigInteger& b) {
    BigInteger result(a);
    result *= b;
    return result;
}

BigInteger operator /(const BigInteger& a, const BigInteger& b) {
    BigInteger result(a);
    result /= b;
    return result;
}

BigInteger operator %(const BigInteger& a, const BigInteger& b) {
    BigInteger result(a);
    result %= b;
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
            for (size_t i = a.size(); i-- > 0;) { //size_t i = a.size() - 1; i >= 0; --i
                if (a.at(i) == b.at(i))
                    continue;
                result = a.at(i) < b.at(i);
                if (a.getSign() < 0)
                    result = !result;
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

BigInteger& BigInteger::operator *=(const BigInteger &a) {
    this->sign *= a.sign;
    if (this->sign == 0) {
        this->number = std::vector<int>(1, 0);
        return *this;
    }

    if (a.size() == 1) {
        int remainder = 0;
        for (size_t i = 0; i < this->size(); ++i) {
            this->number[i] = this->number[i] * a.number[0] + remainder;
            remainder = this->number[i] / 10;
            this->number[i] %= 10;
        }
        if (remainder > 0)
            this->number.push_back(remainder);
        while (this->number.size() > 1 && this->number[this->number.size() - 1] == 0) {
            this->number.pop_back();
        }
        return *this;
    }

    if (this->size() == 1) {
        int currentNumber = this->number[0];
        this->number.clear();
        int remainder = 0;
        for (size_t i = 0; i < a.size(); ++i) {
            this->number.push_back(a.number[i] * currentNumber + remainder);
            remainder = this->number[i] / 10;
            this->number[i] %= 10;
        }
        if (remainder > 0)
            this->number.push_back(remainder);
        while (this->number.size() > 1 && this->number[this->number.size() - 1] == 0) {
            this->number.pop_back();
        }
        return *this;
    }

    size_t length =  ((a.size() > this->size() ? a.size() : this->size()) + 1) / 2;
    BigInteger x1;
    x1.sign = 1;
    x1.number.clear();
    BigInteger x2 = BigInteger();
    x2.sign = 1;
    x2.number.clear();
    BigInteger y1 = BigInteger();
    y1.sign = 1;
    y1.number.clear();
    BigInteger y2 = BigInteger();
    y2.sign = 1;
    y2.number.clear();

    if (this->size() < length) {
        x1 = BigInteger(0);
    } else {
        for (size_t i = length; i < this->size(); ++i) {
            x1.number.push_back(this->number[i]);
        }
    }

    for (size_t i = 0; i < this->size() && i < length; ++i) {
        x2.number.push_back(this->number[i]);
    }

    if (a.size() < length) {
        y1 = BigInteger(0);
    } else {
        for (size_t i = length; i < a.size(); ++i) {
            y1.number.push_back(a.number[i]);
        }
    }

    for (size_t i = 0; i < a.size() && i < length; ++i) {
        y2.number.push_back(a.number[i]);
    }

    BigInteger x1y1 = x1;
    x1y1 *= y1;
    BigInteger x2y2 = x2;
    x2y2 *= y2;
    BigInteger sums = x1 + x2;
    sums *= (y1 + y2);

    this->number.clear();

    BigInteger tmp = (sums - x1y1 - x2y2).multiplyOnDegree10(length);
    tmp += x2y2;
    tmp += x1y1.multiplyOnDegree10(length * 2);

    this->number = tmp.number;
    while (this->number.size() > 1 && this->number[this->number.size() - 1] == 0) {
        this->number.pop_back();
    }
    return *this;
}

BigInteger& BigInteger::operator /=(const BigInteger &a) {
    if (this->sign == 0) {
        return *this;
    }
    BigInteger answer = 0;
    answer.number.clear();
    BigInteger dividend = *this;
    BigInteger divisor = a;
    divisor.sign = 1;
    dividend.sign = 1;
    while (divisor <= dividend) {
        divisor *= 10;
    }
    while (divisor.size() >= a.size()) {
        size_t counter = 0;
        while (divisor <= dividend) {
            dividend -= divisor;
            counter++;
        }
        answer.number.push_back(counter);
        for (size_t i = 0; i < size_t(divisor.number.size()) - 1; i++) {
            std::swap(divisor.number[i], divisor.number[i + 1]);
        }
        divisor.number.pop_back();
    }
    for (size_t i = 0; i < answer.number.size() / 2; i++) {
        std::swap(answer.number[i], answer.number[answer.number.size() - 1 - i]);
    }
    while (answer.number.size() > 1 && answer.number[answer.number.size() - 1] == 0) {
        answer.number.pop_back();
    }
    answer.sign = (a.sign * this->sign);
    if (answer.size() == 1 && answer.number[0] == 0)
        answer.sign = 0;
    *this = answer;
    return *this;
}

BigInteger& BigInteger::operator %=(const BigInteger &a) {
    BigInteger integerPart = *this / a;
    *this -= (integerPart * a);
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////

BigInteger gcd(const BigInteger &a, const BigInteger &b) {
    if (a % b == BigInteger(0))
        return BigInteger(b);
    else {
        BigInteger aCopy = a;
        BigInteger bCopy = b;
        while (bCopy != BigInteger(0)) {
            aCopy %= bCopy;
            std::swap(aCopy, bCopy);
        }
        return aCopy;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////



class Rational {
 private:
    BigInteger numerator;
    BigInteger denominator;

    void makeIrreducible();
    Rational reverse() const;

 public:

    Rational() {
        this->numerator = BigInteger(0);
        denominator = BigInteger(1);
    }
    Rational(const int a) {
        this->numerator = BigInteger(a);
        this->denominator = BigInteger(1);
    }
    Rational(const BigInteger &a) {
        this->numerator = BigInteger(a);
        this->denominator = BigInteger(1);
    }
    Rational(const int a, const int b) : numerator(a), denominator(b) {
        this->makeIrreducible();
    }

    Rational(const BigInteger &a, const BigInteger &b) : numerator(a), denominator(b) {
        this->makeIrreducible();
    }

    BigInteger getNumerator() const {
        return this->numerator;
    }

    BigInteger getDenominator() const {
        return this->denominator;
    }

    std::string toString();

    std::string asDecimal(size_t precision = 0) const ;

    Rational operator -() const {
        Rational result = *this;
        result.numerator = -result.numerator;
        return result;
    }

    Rational& operator +=(const Rational& a) {
        this->numerator *= a.denominator;
        this->numerator += this->denominator * a.numerator;
        this->denominator *= a.denominator;
        this->makeIrreducible();
        return *this;
    }

    Rational& operator -=(const Rational& a) {
        *this += -a;
        return *this;
    }

    Rational& operator *=(const Rational& a) {
        this->numerator *= a.numerator;
        this->denominator *= a.denominator;
        this->makeIrreducible();
        return *this;
    }

    Rational& operator /=(const Rational& a) {
        *this *= a.reverse();
        return *this;
    }

};

Rational operator +(const Rational &a, const Rational &b) {
    Rational result = a;
    result += b;
    return result;
}

Rational operator -(const Rational& a, const Rational& b) {
    Rational result = a;
    result -= b;
    return result;
}

Rational operator *(const Rational& a, const Rational& b) {
    Rational result = a;
    result *= b;
    return result;
}

Rational operator /(const Rational& a, const Rational& b) {
    Rational result = a;
    result /= b;
    return result;
}


bool operator <(const Rational& a, const Rational& b) {
    return a.getNumerator() * b.getDenominator() < a.getDenominator() * b.getNumerator();
}

bool operator >(const Rational& a, const Rational& b) {
    return b < a;
}

bool operator ==(const Rational& a, const Rational& b) {
    return !(a < b || a > b);
}

bool operator <=(const Rational& a, const Rational& b)  {
    return a < b || a == b;
}


bool operator >=(const Rational& a, const Rational& b) {
    return b <= a;
}

bool operator !=(const Rational& a, const Rational& b) {
    return !(a == b);
}

void Rational::makeIrreducible() {
    BigInteger reduce = gcd(this->numerator, this->denominator);
    this->numerator /= reduce;
    this->denominator /= reduce;
    if (this->denominator < BigInteger(0)) {
        this->denominator *= -1;
        this->numerator *= -1;
    }
}

std::string Rational::toString() {
    std::string result = this->numerator.toString();
    if (this->denominator != BigInteger(1))
        result += "/" + this->denominator.toString();
    return result;
}

std::string Rational::asDecimal(size_t precision) const {
    Rational tmp = *this;
    tmp.numerator = tmp.numerator.absoluteValue();
    std::string result = *this < 0 ? "-" : "";
    result += (tmp.numerator / tmp.denominator).toString() + ".";
    tmp -= tmp.numerator / tmp.denominator;
    for (unsigned int i = 0; i < precision; ++i) {
        tmp *= 10;
        result += (tmp.numerator / tmp.denominator).toString();
        tmp -= tmp.numerator / tmp.denominator;
    }
    return result;
}

Rational Rational::reverse() const {
    Rational result;
    result.numerator = this->denominator;
    result.denominator = this->numerator;
    result.makeIrreducible();
    return result;
}