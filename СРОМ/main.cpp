#pragma once
#include "Numb.h"
#include <intrin.h>
#include <iomanip>
using Clock = std::chrono::steady_clock;
using std::chrono::microseconds;
using std::chrono::duration_cast;

int main()
{
	Number A("");
	Number B("");
	Number N("");
	Number C = A.GCD(B);
	C.ShowHex();
	Number D = N.SumMod(A, B);
	D.ShowHex();
	Number E = N.DifMod(A, B);
	E.ShowHex();
	Number F = N.MultMod(A, B);
	F.ShowHex();
	Number G = N.LMPB(A, B);
	G.ShowHex();
	return 0;
}