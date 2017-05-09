#!/bin/bash

g++ -std=c++11 cpp11.cpp && ./a.out
g++ -I~/dkuyu/bin/boost_1_60_0 cpp03.cpp && ./a.out

# ideally, nothing should be printed in standard output
