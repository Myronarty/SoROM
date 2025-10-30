#pragma once
#include "string"
#include "iostream"
#include <random>
#include <regex>

#include <chrono>

using namespace std;
using namespace std::chrono;

struct Number
{
	friend struct DoubleNumber;
protected:
	static constexpr int b = 64;
	int w = 32;
	uint64_t _carry = 0;
	uint32_t A[b] = { 0 };
public:
	Number() {};
	Number(string s);
	bool HexSyntax(string n);
	void Show() const;
	void ShowHex() const;
	Number(const Number&);
	Number(Number&&);
	int High() const;
	int HighB() const;
	int LongCmp(Number B) const;
	void LSDTH(int k);
	void RSDTH(int k);
	void LSBTH(int k);
	Number LMOG(uint32_t  k) const;
	Number squared();
	Number power(const Number& B);
	Number GCD(Number B);
	DoubleNumber LSM(Number B);
	Number& operator=(const Number&);
	bool operator==(const Number& B) const;
	Number operator+ (const Number& B);
	Number operator+ (const uint32_t& k);
	Number operator- (const Number& B);
	Number operator* (const Number& B);
	Number operator/ (const Number& B);
	string generate_hex(const int len);
	Number operator<< (int k);
	Number operator>> (int k);
	int* ToBits() const;

	Number SumMod(Number A, Number B);
	Number DifMod(Number A, Number B);
	Number MultMod(Number A, Number B);

	void ShiftRight1();
	void ShiftLeft1();

	Number BarRed(DoubleNumber X, Number N, Number Mu);
	Number LMPB(Number A, Number B);

	DoubleNumber DoubleMult(const Number& B) const;
	DoubleNumber ToDoubleNumber() const;

	//Number mont(const Number& B);
	//Number redc(const Number& B);
};

struct DoubleNumber
{
	friend struct Number;
protected:
	static constexpr int b = 129;
	int w = 32;
	uint64_t _carry = 0;
	uint32_t A[b] = { 0 };
public:
	DoubleNumber() {};
	DoubleNumber(string s);
	bool HexSyntax(string n);
	void Show() const;
	void ShowHex() const;
	DoubleNumber(const DoubleNumber&);
	DoubleNumber(DoubleNumber&&);
	int High() const;
	int HighB() const;
	int LongCmp(DoubleNumber B) const;
	void LSDTH(int k);
	void RSDTH(int k);
	void LSBTH(int k);
	DoubleNumber LMOG(uint32_t  k) const;
	DoubleNumber GCD(Number B);
	DoubleNumber& operator=(const DoubleNumber&);
	bool operator==(const DoubleNumber& B) const;
	DoubleNumber operator+ (const DoubleNumber& B);
	DoubleNumber operator+ (const uint32_t& k);
	DoubleNumber operator- (const DoubleNumber& B);
	DoubleNumber operator* (const DoubleNumber& B);
	DoubleNumber operator/ (const DoubleNumber& B);
	DoubleNumber operator<< (int k);
	DoubleNumber operator>> (int k);

	Number ToNumber() const;
};