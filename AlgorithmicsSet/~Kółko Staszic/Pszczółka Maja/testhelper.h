#pragma once
#include <fstream>

#if defined(TESTING) && defined(TEST_FILENAME)
#define INIT_TESTER ifstream cin(TEST_FILENAME ".in");

#define FINISH_TEST cin.close(); \
                    cout << endl << "=== $ Expected output $ ===" << endl; \
                    ifstream expout(TEST_FILENAME ".out"); \
                    cout << expout.rdbuf(); \
                    expout.close();
#else
#define INIT_TESTER
#define FINISH_TEST
#endif
