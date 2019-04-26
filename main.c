#include <stdio.h>
#include <time.h>
#include "./src/imagegd.h"

double benchmark_gd(int n, const char*input);

int main() {
  printf("=> benchmark gd: %.2fms\n", benchmark_gd(5, "/tmp/test.jpeg"));
}

double benchmark_gd(int n, const char* input) {
  double total = 0;
  int i = 0;
  for(i=0; i<n; i++){
    clock_t begin = clock();
    image_resize("/tmp/test.jpeg", "./images/output.jpeg", 200, 1, 90, 0);
    clock_t end = clock();
    total += (double)(end - begin) / CLOCKS_PER_SEC;
  }
  return total / n;
}
