#include <stdio.h>
int main() {
  int arr[3][2] = {{1, 2}, {3, 4}, {5, 6}};
  int* parr = (int*)arr;
  int i;
  for (i = 0; i < 3*2; ++i) {
    printf("%d ", parr[i]);
  }
  printf("\n");
  return 0;
}
