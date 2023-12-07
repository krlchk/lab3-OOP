#pragma once
#include <iostream>

class Fraction
{
private:
	int num;
	int den;
	int sign;

	void reduce();

	static Fraction absAddition(const Fraction&, const Fraction&);
	static Fraction absSubtraction(const Fraction&, const Fraction&);

public:
	Fraction();
	Fraction(int, int);

	bool operator>(const Fraction&) const;
	bool operator<(const Fraction&) const;
	bool operator>=(const Fraction&) const;
	bool operator<=(const Fraction&) const;
	bool operator==(const Fraction&) const;
	bool operator!=(const Fraction&) const;

	Fraction operator+(const Fraction&) const;
	Fraction operator-(const Fraction&) const;
	Fraction operator*(const Fraction&) const;
	Fraction operator/(const Fraction&) const;

	std::string toString();
};

int getSign(int);
int absInt(int);
int gcd(int, int);
