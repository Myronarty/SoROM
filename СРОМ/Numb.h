#pragma once
#include "string"
#include "iostream"

#include <regex>

#include <chrono>

using namespace std;
using namespace std::chrono;

struct Number
{
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
	void LSBTH(int k);
	Number LMOG(uint32_t  k) const;
	Number squared(const Number& B);
	Number power(const Number& B);
	Number& operator=(const Number&);
	bool operator==(const Number& B) const;
	Number operator+ (const Number& B);
	Number operator+ (const uint32_t& k);
	Number operator- (const Number& B);
	Number operator* (const Number& B);
	Number operator/ (const Number& B);

	void operator<< (const Number& B);
	int* ToBits() const;
};
