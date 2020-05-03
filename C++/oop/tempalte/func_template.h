#pragma once
#include <iostream>
#include <cstring>
using namespace std;

// 函数模板
template<class T>
bool myCompare(T a, T b) {
  cout << "myCompare"  << endl;
  return a > b;
}

// 函数模板的特化
template<>
bool myCompare<const char*>(const char* a, const char* b) {
  cout << "const char* myCompare" << endl;
  return strcmp(a, b)  > 0;
}

