cmake_minimum_required(VERSION 3.17)
project(TP1 C)

set(CMAKE_C_STANDARD 90)

add_executable(TP1 main.c utilities.c utilities.h trie.c trie.h)