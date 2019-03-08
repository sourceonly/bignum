

#include <natural_number.h>


struct number *find_gcd(struct number *x1, struct number *x2) {


  if (compare_abs(x1,x2) == DIGITAL_GT) return find_gcd(x2,x1);
  struct number *res, *rm, *zero;

  res=natural_div(x2,x1);
  rm=natural_remain(x2,x1);

  zero=create_zero();
  if (compare_abs(rm,zero)==DIGITAL_EQ) {
    destroy_number(zero);
    destroy_number(res);
    destroy_number(rm);
    return x1;
  }
  destroy_number(res);
  return find_gcd(rm,x1);
}

int main() {
  struct number *x1, *x2, *gcd;
  x1=number_from_string("58092");
  x2=number_from_string("28");
  gcd=find_gcd(x1,x2);
  write_down(gcd);
}
