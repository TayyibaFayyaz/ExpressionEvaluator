#include "HugeInteger.h"

HugeInteger::HugeInteger()
{
	size = 0;
	Vs = nullptr;
	IsNeg = false;
}

string HugeInteger::HItoS()
{
	string R;
	if (IsNeg)
	{
		R = "-";
	}
	for (int i = size - 1; i >= 0; i--)
	{
		R += char(Vs[i]) + 48;
	}
	return R;
}

void HugeInteger::Read(ifstream& Rdr)
{
	char sign;
	Rdr >> sign;
	//((sign == '+') ? IsNeg = false : IsNeg = true);
	if (sign == '+')
	{
		IsNeg = false;
	}
	else
	{
		IsNeg = true;
	}
	string N;
	Rdr >> N;
	size = N.size();
	Vs = new int[size];
	for (int i = 0; i < size; i++)
	{
		Vs[size - 1 - i] = (N.at(i) - '0');
	}
	Trim();
}

HugeInteger::HugeInteger(ifstream& Rdr)
{
	Read(Rdr);
}

void HugeInteger::DeepCopy(const HugeInteger& HI)
{
	IsNeg = HI.IsNeg;
	int* Cs = new int[HI.size];
	for (int i = 0; i < HI.size; i++)
	{
		Cs[i] = HI.Vs[i];
	}
	delete[] Vs;
	Vs = Cs;
	size = HI.size;
}

HugeInteger::HugeInteger(const HugeInteger& HI)
{
	DeepCopy(HI);
}

HugeInteger::HugeInteger(int num)
{
	if (num == 0)
	{
		size = 1;
		IsNeg = false;
		Vs = new int[size];
		Vs[0] = 0;
	}
	else
	{
		size = log10(abs(num)) + 1;
		((num < 0) ? IsNeg = true : IsNeg = false);
		((num < 0) ? num = -1 * num : num = num);
		Vs = new int[size];
		int ind = 0;
		while (num != 0)
		{
			Vs[ind] = num % 10;
			num /= 10;
			ind++;
		}
	}
}

const int HugeInteger::operator[](int i)const
{
	return ((i >= size) ? 0 : Vs[i]);
}

int& HugeInteger::operator[](int i)
{
	return Vs[i];
}

void HugeInteger::Allocate()
{
	Vs = new int[size];
}

void HugeInteger::Trim()
{
	if ((*this)[size - 1] == 0 && size != 1)
	{
		int* Cs = new int[size - 1];
		for (int i = 0; i < size - 1; i++)
		{
			Cs[i] = Vs[i];
		}
		delete[] Vs;
		Vs = Cs;
		size--;
		Trim();
	}
	return;
}

HugeInteger HugeInteger::ADDQuantityWise(const HugeInteger& HI)const
{
	HugeInteger R;
	R.size = size + 1;
	R.Allocate();
	int carry = 0;
	for (int i = 0; i < size + 1; i++)
	{
		R[i] = ((*this)[i] + HI[i] + carry) % 10;
		carry = ((*this)[i] + HI[i] + carry) / 10;
	}
	R.Trim();
	return R;
}

HugeInteger HugeInteger::SUBQuantityWise(const HugeInteger& HI)const
{
	HugeInteger R;
	R.size = size;
	R.Allocate();
	int carry = 0;
	for (int i = 0; i < size; i++)
	{
		R[i] = ((*this)[i] - HI[i] - carry);
		if (R[i] < 0)
		{
			R[i] += 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
	}
	R.Trim();
	return R;
}

bool HugeInteger::LessThanQuatityWise(const HugeInteger& HI)const
{
	if (size < HI.size)
	{
		return true;
	}
	else if (size > HI.size)
	{
		return false;
	}
	else
	{
		for (int i = size - 1; i >= 0; i--)
		{
			if ((*this)[i]< HI[i])
			{
				return true;
			}
			else if ((*this)[i] > HI[i])
			{
				return false;
			}
		}
		return false;
	}
}

bool HugeInteger::GreaterThanQuatityWise(const HugeInteger& HI)const
{
	return HI.LessThanQuatityWise(*this);
}

bool HugeInteger::EqualQuatityWise(const HugeInteger& HI)const
{
	return !LessThanQuatityWise(HI) && !GreaterThanQuatityWise(HI);
}

const HugeInteger& HugeInteger::operator=(const HugeInteger& HI)
{
	Clear();
	DeepCopy(HI);
	return *this;
}

const HugeInteger HugeInteger::operator+(const HugeInteger& HI)const
{
	HugeInteger R;
	if (IsNeg == HI.IsNeg)
	{
		if (GreaterThanQuatityWise(HI))
		{
			R = ADDQuantityWise(HI);
		}
		else
		{
			R = HI.ADDQuantityWise(*this);
		}
		R.IsNeg = IsNeg;
	}
	else
	{
		if (GreaterThanQuatityWise(HI))
		{
			R = SUBQuantityWise(HI);
			R.IsNeg = IsNeg;
		}
		else
		{
			R = HI.SUBQuantityWise(*this);
			R.IsNeg = HI.IsNeg;
		}
	}
	return R;
}

const HugeInteger HugeInteger::operator+=(const HugeInteger& HI)
{
	*this = *this + HI;
	return *this;
}

const HugeInteger HugeInteger::operator++()
{
	HugeInteger Unit(1);
	(*this) = (*this) + Unit;
	return *this;
}

const HugeInteger HugeInteger::operator++(int i)
{
	HugeInteger Temp;
	Temp = *this;
	HugeInteger Unit(1);
	(*this) = (*this) + Unit;
	return Temp;
}

const HugeInteger HugeInteger::operator-()const
{
	HugeInteger R(*this);
	R.IsNeg = !R.IsNeg;
	return R;
}

const HugeInteger HugeInteger::operator-(const HugeInteger& HI)const
{
	HugeInteger R;
	R = (*this) + (-HI);
	return R;
}

const HugeInteger HugeInteger::operator-=(const HugeInteger& HI)
{
	*this = *this - HI;
	return *this;
}

const HugeInteger HugeInteger::operator--()
{
	HugeInteger Unit(1);
	(*this) = (*this) - Unit;
	return *this;
}

const HugeInteger HugeInteger::operator--(int i)
{
	HugeInteger Temp;
	Temp = *this;
	HugeInteger Unit(1);
	(*this) = (*this) - Unit;
	return Temp;
}

bool HugeInteger::operator<(const HugeInteger& HI)const
{
	if (IsNeg && HI.IsNeg)
	{
		return HI.LessThanQuatityWise(*this);
	}
	else if (!IsNeg && !HI.IsNeg)
	{
		return LessThanQuatityWise(HI);
	}
	else if (!IsNeg && HI.IsNeg)
	{
		return false;
	}
	else if (IsNeg && !HI.IsNeg)
	{
		return true;
	}
}

bool HugeInteger::operator>(const HugeInteger& HI)const
{
	return (HI < (*this));
}

bool HugeInteger::operator<=(const HugeInteger& HI)const
{
	return !((*this) > HI);
}

bool HugeInteger::operator>=(const HugeInteger& HI)const
{
	return !((*this) < HI);
}

bool HugeInteger::operator==(const HugeInteger& HI)const
{
	return !((*this) < HI) && !((*this) > HI);
}

bool HugeInteger::operator!=(const HugeInteger& HI)const
{
	return !(*this == HI);
}

const HugeInteger HugeInteger::SimpMultiplication(const HugeInteger& HI)const
{
	HugeInteger R(*this);
	for (HugeInteger i(1); i <= HI; i++)
	{
		R += *this;
	}
	return R;
}

const HugeInteger HugeInteger::operator*(const HugeInteger& H)const
{
	HugeInteger R(*this);
	bool N1 = R.IsNeg;
	R.IsNeg = false;
	HugeInteger T(0);
	HugeInteger B(H);
	bool N2 = B.IsNeg;
	B.IsNeg = false;
	HugeInteger C(1);
	HugeInteger Zero(0);
	if (B == Zero || R == Zero)
	{
		return Zero;
	}
	do
	{
		while (C + C <= B)
		{
			R += R;
			C += C;
		}
		B = B - C;
		T += R;
		R = *this;
		R.IsNeg = false;
		C = 1;
	} while (B >= Zero);
	T.IsNeg = false;
	if (N1 == N2 || T == Zero)
	{
		T.IsNeg = false;
	}
	else
	{
		T.IsNeg = true;
	}
	return T;
}

const HugeInteger HugeInteger::operator*=(const HugeInteger& H)
{
	*this = *this * H;
	return *this;
}

const HugeInteger HugeInteger::operator/(const HugeInteger& H)const
{
	HugeInteger R(*this);
	bool N1 = R.IsNeg;
	R.IsNeg = false;
	HugeInteger T(0);
	HugeInteger B(H);
	bool N2 = B.IsNeg;
	B.IsNeg = false;
	HugeInteger C(1);
	HugeInteger Zero(0);
	try
	{
		if (H == Zero)
		{
			throw "Division by 0!";
		}
		while (R >= B)
		{
			while (B + B <= R)
			{
				B += B;
				C += C;
			}
			R -= B;
			T += C;
			C = 1;
			B = H;
			B.IsNeg = false;
		}
		if (N1 == N2 || T == Zero)
		{
			T.IsNeg = false;
		}
		else
		{
			T.IsNeg = true;
		}
	}
	catch (const char* n)
	{
		cout << endl << "Undefined: Division by 0! " << "Answer Set to Zero" << endl;
		T = Zero;
	}	
	return T;
}

const HugeInteger HugeInteger::operator%(const HugeInteger& H)const
{
	HugeInteger R(*this);
	bool N1 = R.IsNeg;
	R.IsNeg = false;
	HugeInteger T(0);
	HugeInteger B(H);
	bool N2 = B.IsNeg;
	B.IsNeg = false;
	HugeInteger C(1);
	HugeInteger Zero(0);
	while (R >= B)
	{
		while (B + B <= R)
		{
			B += B;
			C += C;
		}
		R -= B;
		T += C;
		C = 1;
		B = H;
		B.IsNeg = false;
	}
	R.IsNeg = false;
	if (R == Zero)
	{
		R.IsNeg = false;
	}
	else
	{
		R.IsNeg = this->IsNeg;
	}
	return R;
}

const HugeInteger HugeInteger::operator%=(const HugeInteger& H)
{
	*this = *this % H;
	return *this;
}

const HugeInteger HugeInteger::operator/=(const HugeInteger& H)
{
	*this = *this / H;
	return *this;
}

void HugeInteger::Clear()
{
	delete[] Vs;
	Vs = nullptr;
	size = 0;
	IsNeg = false;
}

istream& operator>>(istream& console, HugeInteger& HI)
{
	char sign;
	console >> sign;
	((sign == '+') ? HI.IsNeg = false : HI.IsNeg = true);
	string N;
	console >> N;
	HI.size = N.size();
	HI.Vs = new int[HI.size];
	for (int i = 0; i < HI.size; i++)
	{
		HI.Vs[HI.size - 1 - i] = (N.at(i) - '0');
	}
	return console;
}

ostream& operator<<(ostream& console, const HugeInteger& HI)
{
	console << ((HI.IsNeg) ? '-' : '+');
	for (int i = HI.size - 1; i >= 0; i--)
	{
		console << HI.Vs[i];
	}
	return console;
}

ifstream& operator>>(ifstream& console, HugeInteger& HI)
{
	HI.Read(console);
	return console;
}

ofstream& operator<<(ofstream& console, HugeInteger& HI)
{
	console << ((HI.IsNeg) ? '-' : '+');
	for (int i = HI.size - 1; i >= 0; i--)
	{
		console << HI[i];
	}
	return console;
}