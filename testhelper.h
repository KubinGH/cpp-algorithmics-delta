#pragma once
#include <fstream>

#if defined(TESTING) && defined(TEST_FILENAME)
#define INIT_TESTER ifstream cin(TEST_FILENAME ".in");

#define FINISH_TEST cin.close(); \
                    cout << endl << "=== $ Expected output $ ===" << endl; \
                    ifstream expout(TEST_FILENAME ".out"); \
                    cout << expout.rdbuf(); \
                    expout.close();
#endif
#if defined(TESTING) && !defined(TEST_FILENAME)
#define INIT_TESTER error("Test filename is not specified")
#define FINISH_TEST error("Test filename is not specified")
#endif
#if !defined(TESTING)
#define INIT_TESTER _Pragma("message(\"Testing is not enabled\")")
#define FINISH_TEST _Pragma("message(\"Testing is not enabled\")")
#endif
