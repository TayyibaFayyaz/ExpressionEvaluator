#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class HugeInteger
{
	int* Vs = nullptr;
	int size;
	bool IsNeg;
	void Read(ifstream& Rdr);
	void DeepCopy(const HugeInteger& HI);
	void Allocate();
	void Clear();
	HugeInteger ADDQuantityWise(const HugeInteger& HI)const;
	HugeInteger SUBQuantityWise(const HugeInteger& HI)const;
	bool LessThanQuatityWise(const HugeInteger& HI)const;
	bool GreaterThanQuatityWise(const HugeInteger& HI)const;
	bool EqualQuatityWise(const HugeInteger& HI)const;
	void Trim();
public:
	HugeInteger();
	HugeInteger(ifstream& Rdr);
	HugeInteger(const HugeInteger& HI);
	HugeInteger(int num);
	/*HugeInteger(string N);*/
	string HItoS();
	const int operator[](int i)const;
	int& operator[](int i);
	const HugeInteger operator+(const HugeInteger& HI)const;
	const HugeInteger operator+=(const HugeInteger& HI);
	const HugeInteger operator++();
	const HugeInteger operator++(int i);
	const HugeInteger operator-()const;
	const HugeInteger operator-(const HugeInteger& HI)const;
	const HugeInteger operator-=(const HugeInteger& HI);
	const HugeInteger operator--();
	const HugeInteger operator--(int i);
	const HugeInteger& operator=(const HugeInteger& HI);
	bool operator<(const HugeInteger& HI)const;
	bool operator>(const HugeInteger& HI)const;
	bool operator!=(const HugeInteger& HI)const;
	bool operator==(const HugeInteger& HI)const;
	bool operator<=(const HugeInteger& HI)const;
	bool operator>=(const HugeInteger& HI)const;
	const HugeInteger SimpMultiplication(const HugeInteger& HI)const;
	const HugeInteger operator*(const HugeInteger& H)const;
	const HugeInteger operator/(const HugeInteger& H)const;
	const HugeInteger operator*=(const HugeInteger& H);
	const HugeInteger operator/=(const HugeInteger& H);
	const HugeInteger operator%(const HugeInteger& H)const;
	const HugeInteger operator%=(const HugeInteger& H);
	friend istream& operator>>(istream& console, HugeInteger& HI);
	friend ostream& operator<<(ostream& console, const HugeInteger& HI);
	friend ifstream& operator>>(ifstream& console, HugeInteger& HI);
	friend ofstream& operator<<(ofstream& console, HugeInteger& HI);
};

