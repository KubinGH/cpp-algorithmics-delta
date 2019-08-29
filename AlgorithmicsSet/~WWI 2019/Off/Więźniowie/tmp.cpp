
    bool pierwszy_raz = true;
    int ile_wiezniow = 0;
    int izolatka(int nr_wieznia, int nr_dnia, bool zarowka) {
        if (nr_wieznia == 39) {
        if (zarowka) ile_wiezniow ++;
        if (ile_wiezniow == 99) return 2;
            return 0;
        }
        if (!zarowka && pierwszy_raz) {
            pierwszy_raz = false;
            return 1;
        }
        return zarowka;
    }
    