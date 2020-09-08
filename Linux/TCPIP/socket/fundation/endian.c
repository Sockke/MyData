#include <stdio.h>
#include <stdbool.h>

/*
 * 判断主机字节序, 即大小端
 * */

union Endian {
  short num;
  char bytes[sizeof(short)];
}Endian;

bool isSmallEndian() {
  union Endian endian;
  endian.num = 0x1;
  if (endian.bytes[0] == 1) {
    return true;
  } else {
    return false;
  }
}

int main() {
  bool ret = isSmallEndian();
  if (ret) {
    printf("this is small endian\n");
  } else {
    printf("this is big endian\n");
  }

  return 0;
}
