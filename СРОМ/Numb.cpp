#pragma once
#include "Numb.h"

bool Number::HexSyntax(string n)
{
	regex hex("^[A-F0-9]+$");
	return regex_match(n, hex);
}

Number::Number(string s)
{
	int n = s.size();
	if (n > 16385)
	{
		cout << "Too big number" << endl;
		return;
	}

	if (HexSyntax(s) == 0)
	{
		cout << "Strange number" << endl;
		return;
	}

	//bool t = 0;

	for (int i = 0; i < b; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int indx = n - (i * 8 + j) - 1;
			if (indx < 0)
			{
				//t = 1;
				break;
			}
			else if (int(s[indx]) < 58)
			{
				A[i] += (s[indx] - 48) << (j * 4);
			}
			else
			{
				A[i] += (s[indx] - 55) << (j * 4);
			}
		}
		//cout << A[i] << endl;
	}
	s.clear();
}

int Number::High() const
{
	for (int i = b - 1; i > -1; i--)
	{
		if (A[i] != 0)
		{
			return i;
		}
	}
	return -1;
}

int Number::HighB() const
{
	for (int i = b - 1; i > -1; i--)
	{
		if (A[i] != 0)
		{
			for (int j = 31; j > -1; j--)
			{
				if (A[i] & (1u << j))
				{
					return i*32 + j;
				}
			}
		}
	}
	return -1;
}

void Number::Show() const
{
	for (int i = 0; i < b; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}

void Number::ShowHex() const //maybe do better
{
	cout << endl;
	char Ch[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	int k = High();
	/*uint32_t temp = A[k];
	for (int j = 7; j > -1; j--)
	{
		uint32_t t = temp >> (4 * j);
		if (Ch[t] != '0')
		{
			cout << Ch[t];
		}
		temp = temp & ~(t << (4 * j));
	}*/
	if (k >= 0)
	{
		for (int i = k ; i > -1; i--)
		{
			cout << " ";
			uint32_t temp = A[i];
			for (int j = 7; j > -1; j--)
			{
				uint32_t t = temp >> (4 * j);
				cout << Ch[t];
				temp = temp & ~(t << (4 * j));
			}
		}
	}
	cout << endl;
}

int Number::LongCmp(Number B) const
{
	int i = b - 1;
	while (A[i] == B.A[i])
	{
		i--;
		if (i == -1)
		{
			return 0;
		}
	}
	if (A[i] > B.A[i])
	{
		return 1;
	}
	else 
	{
		return -1;
	}
}

void Number::LSDTH(int k)
{
	if (b < k)
	{
		for(int i = 0; i < b; i++)
		{
			A[i] = 0;
		}
		return;
	}
	if (k < 0)
	{
		cout << "error";
		return;
	}
	for (int i = b-1; i >= k; i--)
	{
		A[i] = A[i - k];
	}
	for (int i = k - 1; i >= 0; i--)
	{
		A[i] = 0;
	}
	return;
}

void Number::LSBTH(int k)
{
	int a = this->High();
	Number Temp;
	if (b*w < k)
	{
		for (int i = 0; i < b; i++)
		{
			A[i] = 0;
		}
		return;
	}
	if (k < 0)
	{
		cout << "error";
		return;
	}
	int w_shift = k / w;
	int b_shift = k % w;

	if (b_shift == 0)
	{
		this->LSDTH(k / w);
		return;
	}
	else
	{
		for (int i = 0; i <= a; i++)
		{
			if (i + w_shift < b)
			{
				Temp.A[i + w_shift] |= (A[i] << b_shift);
			}
			if (i + w_shift + 1 < b)
			{
				Temp.A[i + w_shift + 1] |= (A[i] >> (w - b_shift));
			}
		}
	}
	*this = Temp;
	return;
}

Number::Number(const Number&) = default;

Number::Number(Number&&) = default;

Number& Number:: operator=(const Number&) = default;

bool Number:: operator==(const Number& B) const
{
	if (this->LongCmp(B) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

Number Number::operator+(const Number& B)
{
	Number C("0");
	uint64_t carry = 0;
	for (int i = 0; i < b; i++)
	{
		uint64_t temp = uint64_t(this->A[i]) + uint64_t(B.A[i]) + carry;
		//cout << temp << endl;
		C.A[i] = temp & ((uint32_t)-1);
		carry = temp >> w;
	}
	C._carry = carry;
	return C;
}

Number Number::operator+(const uint32_t& k)
{
	Number C;
	uint64_t carry = 0;
	uint64_t temp = uint64_t(this->A[0]) + uint64_t(k);
	C.A[0] = temp & ((uint32_t)-1);
	carry = temp >> w;
	for (int i = 1; i < b; i++)
	{
		if (carry == 0)
		{
			for (int j = i; j < Number::b; j++)
			{
				C.A[j] = this->A[j];
			}
			break;
		}
		temp = uint64_t(this->A[i]) + carry;
		C.A[i] = temp & ((uint32_t)-1);
		carry = temp >> w;
	}
	C._carry = carry;
	return C;
}

Number Number::operator-(const Number& B)
{
	Number C;
	if (LongCmp(B) == -1)
	{
		cout << "Can't do this, man" << endl;
		return C;
	}
	int64_t borrow = 0;
	for (int i = 0; i < b; i++)
	{
		int64_t temp = int64_t(A[i]) - int64_t(B.A[i]) - borrow;

		if (temp >= 0)
		{
			C.A[i] = temp;
			borrow = 0;
		}
		else
		{
			C.A[i] = int32_t(temp + (uint64_t(1) << w));
			borrow = 1;
		}
	}
	return C;
}

Number Number::operator* (const Number& B)
{
	Number C;
	for (int i = 0; i < b; i++)
	{
		Number Temp = this->LMOG(B.A[i]);
		Temp.LSDTH(i);
		C = C + Temp;
	}
	return C;
}

Number Number::LMOG(uint32_t  k) const
{
	Number C;
	uint32_t carry = 0;
	for (int i = 0; i < b; i++)
	{
		uint64_t temp = (uint64_t(A[i]) * k) + carry;
		C.A[i] = temp & ((uint32_t)-1);
		carry = temp >> w;
	}
	C._carry = carry;
	return C;
}

Number Number::operator/ (const Number& B)
{
	Number C;
	int k = B.HighB();
	Number R = *this;
	Number Q;
	while (R.LongCmp(B) != -1)
	{
		int t = R.HighB();
		C = B;
		C.LSBTH(t-k);
		if (R.LongCmp(C) == -1)
		{
			t--;
			C = B;
			C.LSBTH(t-k);
			//cout << 1;
		}
		Number Temp("1");
		Temp.LSBTH(t - k);
		R = R - C;
		Q = Q + Temp;
	}
	return Q;
}

Number Number::squared(const Number& B)
{
	Number C;
	return C;
}

Number Number::power(const Number& B)
{
	Number C("1");
	int p[512] = { 0 };
	int k = High();
	for (int i = k; i > -1; i--)
	{
		cout << " ";
		uint32_t temp = B.A[i];
		for (int j = 7; j > -1; j--)
		{
			uint32_t t = temp >> (4 * j);
			p[i * 8 + j] = t;
			temp = temp & ~(t << (4 * j));
		}
	}
	Number D[16];
	D[0] = C;
	D[1] = *this;
	for (int i = 2; i < 16; i++)
	{
		D[i] = D[i - 1] * (*this);
		//D[i].ShowHex();
	}
	for (int i = 511; i > 0; i--)
	{
		C = C * D[p[i]];
		//cout << p[i] << " ";
		for (int k = 0; k < 4; k++)
		{
			C = C * C;
		}
		//C.Show();
	}
	C = C * D[p[0]];

	return C;
}

void Number::operator<< (const Number& B)
{
	Number C;
	return;
}

int* Number::ToBits() const
{
	int p[512] = { 0 };
	int k = High();
	for (int i = k; i > -1; i--)
	{
		cout << " ";
		uint32_t temp = A[i];
		for (int j = 7; j > -1; j--)
		{
			uint32_t t = temp >> (4 * j);
			p[k - i] = t;
			//cout << p[k - i] << endl;
			temp = temp & ~(t << (4 * j));
		}
	}
	return p;
}
