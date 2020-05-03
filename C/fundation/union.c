#include <stdio.h>
#include <stdbool.h>

/*
  union联合体, 所有的成员共用同一块空间, 该空间大小是union中占空间最大的变量
  struct结构体, 结构体中有成员变量

  字节对齐:
  受编译器默认对齐值与所占空间最大的成员变量大小有关, 按两者中的最小值进行对齐
*/

/*
  用union来将无符号整数值分割成ip地址
  给你一个整数, 让你把其转化成ip
*/
union IPDivide {
  size_t ipNum;
  struct {
    unsigned char part1;
    unsigned char part2;
    unsigned char part3;
    unsigned char part4;
  };
}ipDivide;
// 3232277347 -> 大端:192.168.163.99, 小端: 99.163.168.192
int main() {
  ipDivide.ipNum = 3232277347;
  char ip[13] = {0};
  sprintf(ip, "%d.%d.%d.%d", ipDivide.part1, ipDivide.part2, ipDivide.part3, ipDivide.part4);
  printf("ip:%s\n", ip);
}

#if 0
/*
  用union来判断大小端
  a = 1
  如果计算机以大端存储, 那么a字节序: 0000 0000  0000 0001
  如过计算机以小端存储, 那么a字节序: 0000 0001  0000 0000
  c是前1个字节, 如果为0是大端, 如果为1是小端
*/
union {
  int a;
  char c;
}endian;

bool isSmall() {
  endian.a = 1;
  return endian.c == 1;
}

int main() {
  if (isSmall() == true) {
    printf("小端\n");
  } else {
    printf("大端\n");
  }
  return 0;
}
#endif

#if 0
/*
  i的字节序列为: 0011 1001  0011 1000
  因为该计算机是按小端进行存储, 因此i要先转换为大端序列进行计算
  i的大端字节序: 0011 1000  0011 1001
*/
union {
  int i;
  char a[2];
}*p, u;

int main() {
  p = &u;
  p->a[0] = 0x39;
  p->a[1] = 0x38;
  printf("i = %d\n", p->i);
  return 0;
}
#endif
