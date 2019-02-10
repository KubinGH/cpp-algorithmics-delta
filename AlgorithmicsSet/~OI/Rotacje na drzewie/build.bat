@echo off
g++ rot.cpp -o rot.exe -std=c++11 -O2 -Wl,--stack,33554432