#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

/*
  手撕strcpy, strcmp, strcat等函数 
*/
// strcpy
char* str_cpy(char* des, const char* src) {
  char* d = des;
  const char* s = src;
  int len = strlen(src);
  for (int i = len; i >= 0; --i) {
    d[i] = s[i];
  }
  return des;
}

// strcat
char* str_cat(char* des, const char* src) {
  char* d = des;
  const char* s = src;
  while (*d != '\0') {++d;}
  int len = strlen(src);
  for (int i = len; i >= 0; --i) {
    d[i] = s[i];
  }
  return des;
}

// strstr
char* str_str(char* des, const char* src) {
  char* d = des;
  const char* s = src;
  int len1 = strlen(des);
  for (int i = 0; i < len1; ++i) {
    d = des + i;
    s = src;
    while (*d != '\0' && *s != '\0' && *d == *s) {++d; ++s;}
    if (*s == '\0') {return des + i;}
  }
  return nullptr;
}

// strchr
char* str_chr(char* des, int src) {
  char* d = des;
  while (*d != '\0') {
    if (*d == src) {return d;}
    ++d;
  }
  return nullptr;
}

// strncpy
char* str_ncpy(char* des, const char* src, size_t size) {
  char* d = des;
  const char* s = src;
  for (int i = size-1; i >= 0; --i) {
    d[i] = s[i];
  }
  return des;
}

// strncat
char* str_ncat(char* des, const char* src, size_t size) {
  char* d = des;
  const char* s = src;
  while (*d != '\0') {++d;}
  for (int i = size-1; i >= 0; --i) {
    d[i] = s[i];
  }
  d[size] = '\0';
  return des;
}

// memcpy
void* mem_cpy(void* des, const void* src, size_t size) {
  char* d = (char*)des;
  const char* s = (char*)src;
  for (int i = size-1; i >= 0; --i) {
    d[i] = s[i];
  }
  return des;
}


int main() {
  char s2[100] = "hello world sock";
  char* s1 = s2 + 6;
  char* s3 = (char*)mem_cpy(s1, s2, 2);
  cout << s3 << endl;

  //char s1[100] = "hello world";
  //const char* s2 = "sock";
  //char* s3 = (char*)mem_cpy(s1, s2, 4);
  //cout << s3 << endl;
  //cout << strlen(s3) << endl;
  return 0;
}
