#include <bits/stdc++.h>
#define cbrt(x) pow(x, 1.0/3)
#define frrt(x) pow(x, 1.0/4)
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define FIRST_TAX(x) (min(x, sqrt(x) + max(0.0, log(x))))
#define SECOND_TAX(x) ((2 * cbrt(x)) + (x/10))
#define THIRD_TAX(x) (max(0, log(x * ((x*x) + 5000))) + (x/2))
#define FOURTH_TAX(x) ((x / 7) + frrt(x))
#define TAXED(x) (x - get_tax(x))
#define SF 3
#define MUL 1.5
#define ITER 27

double get_tax(double camount)
{
    // Starts at ~0.3, rises to ~0.45,
    // then falls at a (logarithmic?) rate
    // down to 0.15 of the original number.
    // Average 0.25? So we use that for approximations. (1/4)
    double tax = 0;
    if(camount >= 10000)
        camount -= 10000;
    else
        return 0;
    if(camount)
    {
        tax += FIRST_TAX(min(camount, 90000));
        camount -= min(camount, 90000);
    }
    if(camount)
    {
        tax += SECOND_TAX(min(camount, 900000));
        camount -= min(camount, 900000);
    }
    if(camount)
    {
        tax += THIRD_TAX(min(camount, 9000000));
        camount -= min(camount, 9000000);
    }
    if(camount)
    {
        tax += FOURTH_TAX(camount);
        camount = 0;
    }
    return tax;
}

int main()
{
    uint32_t icount;
    scanf("%u", &icount);
    for(uint32_t i = 0; i < icount; i++)
    {
        double target;
        scanf("%lf", &target);
        double f = SF;
        double guess = target + (target / 2), taxed;
        for(uint32_t _i = 0; _i < ITER; _i++)
        {

            taxed = TAXED(guess);
            if(target == taxed)
                break;
            else if(target < taxed)
                guess -= guess / f;
            else
                guess += guess / f;
            f *= MUL;
        }
        printf("%.15f\n", guess);
    }
}
