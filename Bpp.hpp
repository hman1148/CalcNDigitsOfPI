#pragma once

#include <cmath>
#include <iostream>
#include <mutex>

class Bpp
{
  public:
    static int getDecimal(long n);
    static const int NUM = 1000;

  private:
    static std::mutex mutex;
    static long mulMod(long a, long b, long m);
    static long modInverse(long a, long n);
    static long powMod(long a, long b, long m);
    static bool isPrime(long n);
    static long nextPrime(long n);
};

int Bpp::getDecimal(long n)
{
    std::lock_guard<std::mutex> lock(Bpp::mutex);
    long av, a, vmax, N, num, den, k, kq, kq2, t, v, s, i;
    double sum;

    N = static_cast<long>((n + 20) * std::log(10) / std::log(2));

    sum = 0;

    for (a = 3; a <= (2 * N); a = nextPrime(a))
    {

        vmax = static_cast<long>(std::log(2 * N) / std::log(a));
        av = 1;
        for (i = 0; i < vmax; i++)
            av *= a;

        s = 0;
        num = 1;
        den = 1;
        v = 0;
        kq = 1;
        kq2 = 1;

        for (k = 1; k <= N; k++)
        {

            t = k;
            if (kq >= a)
            {
                do
                {
                    t /= a;
                    v--;
                } while (t % a == 0);
                kq = 0;
            }
            kq++;
            num = mulMod(num, t, av);

            t = (2 * k - 1);
            if (kq2 >= a)
            {
                if (kq2 == a)
                {
                    do
                    {
                        t /= a;
                        v++;
                    } while (t % a == 0);
                }
                kq2 -= a;
            }
            den = mulMod(den, t, av);
            kq2 += 2;

            if (v > 0)
            {
                t = modInverse(den, av);
                t = mulMod(t, num, av);
                t = mulMod(t, k, av);
                for (i = v; i < vmax; i++)
                    t = mulMod(t, a, av);
                s += t;
                if (s >= av)
                    s -= av;
            }
        }

        t = powMod(10, n - 1, av);
        s = mulMod(s, t, av);
        sum = fmod(sum + static_cast<double>(s) / static_cast<double>(av), 1.0);
    }

    int foundDecimal = static_cast<int>(sum * 1e9);
    int totalDigits = static_cast<int>(std::floor(std::log10(foundDecimal)));

    int significant = 0;
    if (totalDigits >= 8)
    {
        significant = static_cast<int>(foundDecimal / std::pow(10, totalDigits));
    }

    return significant;
}

long Bpp::mulMod(long a, long b, long m)
{
    std::lock_guard<std::mutex> lock(Bpp::mutex);
    return static_cast<long>((a * b) % m);
}

long Bpp::modInverse(long a, long n)
{
    std::lock_guard<std::mutex> lock(Bpp::mutex);
    long i = n, v = 0, d = 1;
    while (a > 0)
    {
        long t = i / a, x = a;
        a = i % x;
        i = x;
        x = d;
        d = v - t * x;
        v = x;
    }
    v %= n;
    if (v < 0)
        v = (v + n) % n;
    return v;
}

long Bpp::powMod(long a, long b, long m)
{
    std::lock_guard<std::mutex> lock(Bpp::mutex);
    if (b == 0)
        return 1;
    else if (b == 1)
        return a % m;

    long temp = powMod(a, b / 2, m);
    if (b % 2 == 0)
        return (temp * temp) % m;
    else
        return (((temp * temp) % m) * a) % m;
}

bool Bpp::isPrime(long n)
{
    std::lock_guard<std::mutex> lock(Bpp::mutex);
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0 || n < 2)
        return false;

    long sqrtN = static_cast<long>(std::sqrt(n)) + 1;
    for (long i = 6; i <= sqrtN; i += 6)
    {
        if (n % (i - 1) == 0 || n % (i + 1) == 0)
            return false;
    }
    return true;
};

long Bpp::nextPrime(long n)
{
    std::lock_guard<std::mutex> lock(Bpp::mutex);
    if (n < 2)
        return 2;
    if (n == 9223372036854775783L)
    {
        std::cerr << "Next prime number exceeds Long.MAX_VALUE: " << LONG_MAX << std::endl;
        return -1;
    }
    for (long i = n + 1;; i++)
        if (isPrime(i))
            return i;
}