#pragma once
#include "Numb.h"

Number Number::SumMod(Number A, Number B)
{
    Number C = A + B;

    if (C.LongCmp(*this) != -1)
    {
        C = C - (*this * (C / *this));
    }

    return C;
}

Number Number::DifMod(Number A, Number B)
{
    Number C = A - B;

    if (C.LongCmp(*this) != -1)
    {
        C = C - (*this * (C / *this));
    }

    return C;
}

Number Number::MultMod(Number A, Number B)
{
    DoubleNumber P = A.DoubleMult(B);
    DoubleNumber N = this->ToDoubleNumber();
    if (P.LongCmp(N) != -1)
    {
        P = P - (N * (P / N));
    }
    Number C = P.ToNumber();

    return C;
}

bool delimost_na_dva(uint32_t a)
{
	return (a & 1) == 0;
}

Number Number::GCD(Number B)
{
    Number A = *this;
    Number D("1");
    while (delimost_na_dva(A.A[0]) && delimost_na_dva(B.A[0]))
    {
        A.ShiftRight1();
        B.ShiftRight1();
        D.ShiftLeft1();
    }
    while (delimost_na_dva(A.A[0]))
    {
        A.ShiftRight1();
    }
    while (B.High() != -1)
    {
        while (delimost_na_dva(B.A[0]))
        {
            B.ShiftRight1();
        }
        Number Temp = A;
        if (A.LongCmp(B) == 1)
        {
            A = B;
            B = Temp - B;
        }
        else
        {
            B = B - A;
        }
    }
    D = D * A;
    return D;
}

DoubleNumber Number::LSM(Number B)
{
    DoubleNumber lsm = this->DoubleMult(B) / (this->GCD(B)).ToDoubleNumber();
    return lsm;
}

Number Number::BarRed(DoubleNumber X, Number N, Number Mu)
{
    int k = N.High();
    DoubleNumber Temp_X = X;

    Temp_X.RSDTH(k);
    DoubleNumber Temp_Q = Temp_X.ToNumber().DoubleMult(Mu);
    Temp_Q.RSDTH(k + 2);
    Number Q = Temp_Q.ToNumber();

    DoubleNumber Temp = Q.DoubleMult(N);

    DoubleNumber R = X - Temp;

    DoubleNumber N_D = N.ToDoubleNumber();

    while (R.LongCmp(N_D) != -1)
    {
        R = R - N_D;
    }

    return R.ToNumber();
}

Number Number::LMPB(Number A, Number B)
{
    Number C("1");
    Number N = *this;
    int k = N.High();

    DoubleNumber Temp_Mu;

    if (2 * (k + 1) < 129)
    {
        Temp_Mu.A[2 * (k + 1)] = 1; //LSDTH(1, 2k)
    }
    else
    {
        cout << "N is too big to have Mu." << endl;
        return Number("0");
    }

    Number Mu = (Temp_Mu / N.ToDoubleNumber()).ToNumber();

    int t = B.HighB();
    if (t == -1)
    {
        return C;
    }

    for (int i = 0; i < t / 32; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            if ((B.A[i] & (uint32_t(1) << j)) != 0)
            {
                C = BarRed(C.DoubleMult(A), N, Mu);
            }
            A = BarRed(A.DoubleMult(A), N, Mu);
        }
    }

    for (int j = 0; j <= t % 32; j++)
    {
        if ((B.A[t / 32] & (uint32_t(1) << j)) != 0)
        {
            C = BarRed(C.DoubleMult(A), N, Mu);
        }
        A = BarRed(A.DoubleMult(A), N, Mu);
    }

    return C;
}
