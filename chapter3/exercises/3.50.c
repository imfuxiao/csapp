
#include <printf.h>
int fcvt2(int *ip, float *fp, double *dp, long l) {
  int i = *ip;
  float f = *fp;
  double d = *dp;
  *ip = (int) (*dp);
  *fp = (float) i;
  *dp = (double) l;
  return (double) f;
}

int main() {
  double a = 2.0;
  float b = (float) a;
  printf("%f", b);
}

