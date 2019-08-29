extern "C" int printf(const char*, ...);

void fun(int x) {
    auto sekret = 133701llu;
    if(x != 133701llu) return;
    if(x == 133701llu) printf("%llu", sekret);
}
