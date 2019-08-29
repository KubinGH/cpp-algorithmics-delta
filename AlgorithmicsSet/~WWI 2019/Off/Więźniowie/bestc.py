import sys
sys.path.append("/home/kubin/Documents/GitHub/siogo/siogo")

import os, base64, time

import old_selenium.selenium_siodriver as siodriver
from old_selenium.configs import DriverConfigStaszic, make_simple_chrome_driver

driver = siodriver.SeleniumSIODriver(DriverConfigStaszic, make_simple_chrome_driver)

import sec

driver.login(lambda: "Kubin", lambda: base64.b64decode(sec.password).decode())


for magic in range(40, 50):
    print(f"{magic}... ", end="", flush=True)

    template = """
    bool pierwszy_raz = true;
    int ile_wiezniow = 0;
    int izolatka(int nr_wieznia, int nr_dnia, bool zarowka) {
        if (nr_wieznia == %d) {
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
    """

    with open("tmp.cpp", "w") as f:
        f.write(template % magic)

    driver.submit_solution('wwi-2019-off', 'wiezniowie', os.path.join(os.getcwd(), 'tmp.cpp'), True)

    print("done", flush=True)

    for i in range(5):
        print(f"{5 - i}... ", end="", flush=True)
        time.sleep(1)
    print()
