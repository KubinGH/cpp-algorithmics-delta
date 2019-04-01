#include <bits/stdc++.h>
#include "cskolib.h"
#include <cstdarg>
#include <cstdlib>
#include <iostream>
#include <random>
//#include "oi.h"

namespace __skok {

long long __tab[100002];
int __N, __numop, __subtask;
bool __inicjal = false;
int __koniec = 0;

void __fail(string s)
{
	cout << s << endl;
	exit(1);
}

void __check(bool shouldBe) {
    if (__inicjal != shouldBe) {
        if (__inicjal == false)
            __fail("[ogolne] Nie zainicjowano biblioteki");
        else
            __fail("[ogolne] Probowano wielokrotnie zainicjowac biblioteke");
    }
    if (__koniec == 1)
        __fail("[ogolne] Wywolano funkcje po zakonczeniu");
}


pair<int, int> __inicjuj() {
    //		fprintf(stderr, "inicjuj\n");
    __check(false);

    std::cin >> __subtask >> __N;

    __inicjal = true;
    __numop = 0;
    for (int i=0; i<__N; i++)
        std::cin >> __tab[i];
    sort(__tab, __tab+__N);

    return {__subtask, __N};
}
   

const long long INF = 1000000000000000001;


pair<long long, long long> __zapytanie(long long s, long long t) {
    //		fprintf(stderr, "\n");
    //		fprintf(stderr, "zapytanie\n");
    __check(true);
    if (s>t)
    {
        exit(1);
    }

	long long wyn1=-1, wyn2=-1;
    int ile=0;
   	int pocz=0, kon=__N-1, sr=(pocz+kon)/2;
	while (pocz<kon)
	{
		if (__tab[sr]>=s)
			kon=sr;
		else
			pocz=sr+1;
		sr=(pocz+kon)/2;
	}
	if (t >= __tab[pocz] && __tab[pocz] >= s)
		wyn1=__tab[pocz];
	ile-=pocz;
		
	pocz=0; kon=__N-1; sr=(pocz+kon)/2;
	while (pocz<kon)
	{
		if (__tab[sr]<=t)
			pocz=sr;
		else
			kon=sr-1;
		sr=(pocz+kon+1)/2;
	}
	if (s <= __tab[pocz] && __tab[pocz] <= t)
		wyn2=__tab[pocz];
	ile+=pocz+1;

    if (__subtask == 1)
        __numop++;
    else
        __numop += ile+1;
	
	//cerr << "odp\n" << endl;
    return {wyn1, wyn2};
}

void __odpowiedz(long long x)
{
    __check(true);
    __koniec = 1;
    long long opt = 0;
    for (int i=0; i<__N-1; i++)
		opt=max(opt, __tab[i+1]-__tab[i]);
	if (opt!=x)
	{
		cout << "Niepoprawna odpowiedz\n";
		return;
	}
	double pkt = 0;
	if (__subtask == 1)
	{
		if (__numop*2 <= __N+1)
			pkt = 100;
	}
	else
	{
		if (__numop <= 3*__N)
			pkt = 100;
		else
			pkt = (double)60/(70*sqrt((double)__numop/__N+1)-1);
	}
	cout << "OK\n";
    cout << "M dla zapytań programu wynosi " << __numop << "\n";
    cout << "I jest warte " << pkt << " punktow\n";
}
};


pair<int, int> inicjuj() {
    return __skok::__inicjuj();
}

pair<long long, long long> min_max(long long s, long long t) {
    return __skok::__zapytanie(s, t);
}


void odpowiedz(long long x) {
    __skok::__odpowiedz(x);
}
