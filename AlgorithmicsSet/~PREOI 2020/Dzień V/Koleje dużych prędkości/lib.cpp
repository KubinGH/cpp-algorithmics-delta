// Przykłdaowa biblioteka do zadania Koleje dużych prędkości

#include <iostream>
#include <vector>

#include "kdp.cpp"

void sfinansowano(int projekt) {
    std::cout << projekt << "; ";
}

int main() {
    int n, m;
    std::cin >> n >> m;

    inicjuj(n);

    for (int i = 0; i < m; i++) {
        int t;
        std::cin >> t;

        if (t == 0) {
            int id, m1, m2, k;
            std::cin >> id >> m1 >> m2 >> k;

            nowyProjekt(id, m1, m2, k);
        } else {
            int m, k;
            std::cin >> m >> k;

            std::cout << "{ ";
            dofinansowanie(m, k);
            std::cout << "}" << std::endl;
        }
    }
}
