#pragma once
#include "Numb.h"

bool DoubleNumber::HexSyntax(string n)
{
	regex hex("^[A-F0-9]+$");
	return regex_match(n, hex);
}

DoubleNumber::DoubleNumber(string s)
{
	int n = s.size();
	if (n > 1032)
	{
		cout << "Too big DoubleNumber" << endl;
		return;
	}

	if (HexSyntax(s) == 0)
	{
		cout << "Strange DoubleNumber" << endl;
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

int DoubleNumber::High() const
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

int DoubleNumber::HighB() const
{
	for (int i = b - 1; i > -1; i--)
	{
		if (A[i] != 0)
		{
			for (int j = 31; j > -1; j--)
			{
				if (A[i] & (1u << j))
				{
					return i * 32 + j;
				}
			}
		}
	}
	return -1;
}

void DoubleNumber::Show() const
{
	for (int i = 0; i < b; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}

void DoubleNumber::ShowHex() const //maybe do better
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
		for (int i = k; i > -1; i--)
		{
			//cout << " ";
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

int DoubleNumber::LongCmp(DoubleNumber B) const
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

void DoubleNumber::LSDTH(int k)
{
	if (b < k)
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
	for (int i = b - 1; i >= k; i--)
	{
		A[i] = A[i - k];
	}
	for (int i = k - 1; i >= 0; i--)
	{
		A[i] = 0;
	}
	return;
}

void DoubleNumber::RSDTH(int k)
{
	if (b <= k)
	{
		for (int i = 0; i < b; i++)
		{
			A[i] = 0;
		}
		return;
	}

	for (int i = 0; i < b - k; i++)
	{
		A[i] = A[i + k];
	}

	for (int i = b - k; i < b; i++)
	{
		A[i] = 0;
	}
	return;
}

void DoubleNumber::LSBTH(int k)
{
	int a = this->High();
	DoubleNumber Temp;
	if (b * w < k)
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

DoubleNumber::DoubleNumber(const DoubleNumber&) = default;

DoubleNumber::DoubleNumber(DoubleNumber&&) = default;

DoubleNumber& DoubleNumber:: operator=(const DoubleNumber&) = default;

bool DoubleNumber:: operator==(const DoubleNumber& B) const
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

DoubleNumber DoubleNumber::operator+(const DoubleNumber& B)
{
	DoubleNumber C("0");
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

DoubleNumber DoubleNumber::operator+(const uint32_t& k)
{
	DoubleNumber C;
	uint64_t carry = 0;
	uint64_t temp = uint64_t(this->A[0]) + uint64_t(k);
	C.A[0] = temp & ((uint32_t)-1);
	carry = temp >> w;
	for (int i = 1; i < b; i++)
	{
		if (carry == 0)
		{
			for (int j = i; j < DoubleNumber::b; j++)
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

DoubleNumber DoubleNumber::operator-(const DoubleNumber& B)
{
	DoubleNumber C;
	if (this->LongCmp(B) == -1)
	{
		DoubleNumber Temp("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
		int64_t borrow = 0;
		for (int i = 0; i < b; i++)
		{
			int64_t temp = int64_t(B.A[i]) - int64_t(A[i]) - borrow;

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
		C = Temp - C;
		C = C + 1;
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

DoubleNumber DoubleNumber::operator* (const DoubleNumber& B)
{
	DoubleNumber C;
	for (int i = 0; i < b; i++)
	{
		DoubleNumber Temp = this->LMOG(B.A[i]);
		Temp.LSDTH(i);
		C = C + Temp;
	}
	return C;
}

DoubleNumber DoubleNumber::LMOG(uint32_t  k) const
{
	DoubleNumber C;
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

DoubleNumber DoubleNumber::operator/ (const DoubleNumber& B)
{
	DoubleNumber C;
	int k = B.HighB();
	DoubleNumber R = *this;
	DoubleNumber Q;
	while (R.LongCmp(B) != -1)
	{
		int t = R.HighB();
		C = B;
		C.LSBTH(t - k);
		if (R.LongCmp(C) == -1)
		{
			t--;
			C = B;
			C.LSBTH(t - k);
			//cout << 1;
		}
		DoubleNumber Temp("1");
		Temp.LSBTH(t - k);
		R = R - C;
		Q = Q + Temp;
	}
	return Q;
}

DoubleNumber DoubleNumber::operator<<(int k)
{
	int a = this->High();
	DoubleNumber Temp;

	if (b * w < k)
	{
		return Temp;
	}

	if (k < 0)
	{
		cout << "Error: Negative shift amount." << endl;
		return *this;
	}

	int w_shift = k / w;
	int b_shift = k % w;

	if (b_shift == 0)
	{
		this->LSDTH(w_shift);
		return *this;
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
	return *this;
}

DoubleNumber DoubleNumber::operator>>(int k)
{
	// Отримуємо індекс найстаршого блоку
	int a = this->High();
	if (a == -1)
	{
		return *this;
	}

	DoubleNumber Temp; // Тимчасовий об'єкт для збору результату

	// 1. Перевірка на від'ємний зсув
	if (k < 0)
	{
		cout << "Error: Negative shift amount." << endl;
		return *this;
	}

	// 2. Перевірка на занадто великий зсув (обнулення)
	// (Використовуємо <=, оскільки зсув на b*w теж обнуляє число)
	if (b * w <= k)
	{
		return Temp;
	}

	// 3. Розрахунок зсувів
	int w_shift = k / w; // Кількість повних блоків для зсуву
	int b_shift = k % w; // Кількість бітів для зсуву всередині блоку

	// 4. Випадок: зсув кратний 32 (простий зсув блоків)
	if (b_shift == 0)
	{
		this->RSDTH(w_shift); // Використовуємо наш блоковий зсув
		return *this;
	}
	// 5. Випадок: зсув не кратний 32 (складний побітовий зсув)
	else
	{
		// Проходимо по блоках від старшого (a) до молодшого
		for (int i = a; i >= 0; i--)
		{
			// Зсуваємо основну частину A[i] в блок Temp[i - w_shift]
			if (i - w_shift >= 0)
			{
				Temp.A[i - w_shift] |= (A[i] >> b_shift);
			}

			// Зсуваємо "залишок" (молодші біти) з A[i] 
			// в попередній блок Temp[i - w_shift - 1]
			if (i - w_shift - 1 >= 0)
			{
				Temp.A[i - w_shift - 1] |= (A[i] << (w - b_shift));
			}
		}
	}

	// 6. Присвоюємо результат назад поточному об'єкту
	*this = Temp;
	return *this;
}

DoubleNumber Number::DoubleMult(const Number& B) const
{
	DoubleNumber P;

	for (int i = 0; i < 64; i++)
	{
		if (B.A[i] == 0) continue;

		uint64_t carry = 0;
		for (int j = 0; j < 64; j++)
		{
			uint64_t temp = (uint64_t)this->A[j] * B.A[i] + P.A[i + j] + carry;

			P.A[i + j] = (uint32_t)temp;
			carry = temp >> 32;
		}

		int k = i + 64;
		while (carry > 0 && k < 129)
		{
			uint64_t temp = (uint64_t)P.A[k] + carry;
			P.A[k] = (uint32_t)temp;
			carry = temp >> 32;
			k++;
		}
	}
	return P;
}

Number DoubleNumber::ToNumber() const
{
	Number R;
	for (int i = 0; i < 64; i++) 
	{
		R.A[i] = this->A[i];
	}

	return R;
}

DoubleNumber Number::ToDoubleNumber() const
{
	DoubleNumber R;
	for (int i = 0; i < 64; i++)
	{
		R.A[i] = this->A[i];
	}

	return R;
}