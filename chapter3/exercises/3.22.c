#include <printf.h>

int fact_do(int n) {
  int result = 1;

  do {
    result *= n;
    n--;
  } while (n > 1);

  return result;
}

int main() {
  printf("20! %d\n", fact_do(20));
  printf("19! %d\n", fact_do(19));
  printf("18! %d\n", fact_do(18));
  printf("17! %d\n", fact_do(17));
  printf("16! %d\n", fact_do(16));
  printf("15! %d\n", fact_do(15));
  printf("14! %d\n", fact_do(14));
  printf("13! %d\n", fact_do(13));
  printf("12! %d\n", fact_do(12));
  printf("11! %d\n", fact_do(11));
  printf("10! %d\n", fact_do(10));
  printf("9! %d\n", fact_do(9));
  printf("8! %d\n", fact_do(8));
  printf("7! %d\n", fact_do(7));
  printf("6! %d\n", fact_do(6));
  printf("5! %d\n", fact_do(5));
  printf("4! %d\n", fact_do(4));
  printf("3! %d\n", fact_do(3));
  printf("2! %d\n", fact_do(2));
  printf("1! %d\n", fact_do(1));
}