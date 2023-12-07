#include "Fraction.h"

#include <string>
#include <cmath>

Fraction::Fraction() : num(0), den(1), sign(1)
{
}

Fraction::Fraction(int num, int den)
{
    if (den == 0)
        throw std::exception("The denominator cannot be zero!");
    this->num = absInt(num);
    this->den = absInt(den);
    this->sign = (getSign(num) == getSign(den)) ? 1 : -1;
    reduce();
}

bool Fraction::operator>(const Fraction& other) const
{
    return this->num * other.den * sign > other.num * this->den * sign;
}

bool Fraction::operator<(const Fraction& other) const
{
    return this->num * other.den * sign < other.num * this->den * sign;
}

bool Fraction::operator>=(const Fraction& other) const
{
    return this->num * other.den * sign >= other.num * this->den * sign;
}

bool Fraction::operator<=(const Fraction& other) const
{
    return this->num * other.den * sign <= other.num * this->den * sign;
}

bool Fraction::operator==(const Fraction& other) const
{
    return this->num * other.den * sign == other.num * this->den * sign;
}

bool Fraction::operator!=(const Fraction& other) const
{
    return this->num * other.den * sign != other.num * this->den * sign;
}

Fraction Fraction::operator+(const Fraction& other) const
{
    int num, den, sign;
    if (this->sign == other.sign)
    {
        Fraction temp = absAddition(*this, other);
        num = temp.num;
        den = temp.den;
        sign = this->sign;
    }
    else
    {
        Fraction temp1(this->num, this->den);
        Fraction temp2(other.num, other.den);
        if (temp1 > temp2)
        {
            Fraction temp = absSubtraction(temp1, temp2);
            num = temp.num;
            den = temp.den;
            sign = this->sign;
        }
        else if (temp1 < temp2)
        {
            Fraction temp = absSubtraction(temp2, temp1);
            num = temp.num;
            den = temp.den;
            sign = other.sign;
        }
        else
        {
            num = 0;
            den = 1;
            sign = 1;
        }
    }
    return Fraction(sign * num, den);
}

Fraction Fraction::operator-(const Fraction& other) const
{
    int num, den, sign;
    if (this->sign != other.sign)
    {
        Fraction temp = absAddition(*this, other);
        num = temp.num;
        den = temp.den;
        sign = this->sign;
    }
    else if (*this > other)
    {
        Fraction temp1(this->num, this->den);
        Fraction temp2(other.num, other.den);
        Fraction temp = absSubtraction(temp1, temp2);
        num = temp.num;
        den = temp.den;
        sign = this->sign;
    }
    else if (*this < other)
    {
        Fraction temp1(this->num, this->den);
        Fraction temp2(other.num, other.den);
        Fraction temp = absSubtraction(temp2, temp1);
        num = temp.num;
        den = temp.den;
        sign = -this->sign;
    }
    else
    {
        num = 0;
        den = 1;
        sign = 1;
    }
    return Fraction(sign * num, den);
}

Fraction Fraction::operator*(const Fraction& other) const
{
    return Fraction((this->sign * other.sign) * this->num * other.num, this->den * other.den);
}

Fraction Fraction::operator/(const Fraction& other) const
{
    return Fraction((this->sign * other.sign) * this->num * other.den, other.num * this->den);
}

std::string Fraction::toString()
{
    std::string result = (sign < 0) ? "-" : "";
    result += std::to_string(num);
    result += "/";
    result += std::to_string(den);
    return result;
}

void Fraction::reduce()
{
    int x = gcd(this->num, this->den);
    this->num /= x;
    this->den /= x;
}

Fraction Fraction::absAddition(const Fraction& first, const Fraction& second)
{
    return Fraction(first.num * second.den + second.num * first.den, first.den * second.den);
}

Fraction Fraction::absSubtraction(const Fraction& first, const Fraction& second)
{
    return Fraction(first.num * second.den - second.num * first.den, first.den * second.den);
}

int getSign(int number)
{
    return (number < 0) ? -1 : 1;
}

int absInt(int number)
{
    return (number < 0) ? -number : number;
}

int gcd(int a, int b)
{
    while (a != 0 && b != 0)
    {
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    return a + b;
}
