#include <stdio.h>
#include <inttypes.h>

int main()
{
    uint32_t a, b;
    scanf("%d %d", &a, &b);
    printf("Suma liczb %d oraz %d wynosi %d\n", a, b, a + b);
    printf("Ro¿nica liczb %d oraz %d wynosi %d\n", a, b, a - b);
    printf("Iloczyn liczb %d oraz %d wynosi %lld\n", a, b, int64_t(a) * int64_t(b));
    if(a % b)
        printf("Iloraz liczb %d oraz %d wynosi %.5lf\n", a, b, double(a) / double(b));
    else
        printf("Iloraz liczb %d oraz %d wynosi %d\n", a, b, a / b);
    printf("Reszta z dzielenia %d przez %d wynosi %d\n", a, b, a % b);
}
