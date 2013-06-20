#include <bfam.h>
#include <bfam_util.h>

int
check_approx_eq(bfam_long_real_t eps, size_t nx, bfam_long_real_t *P,
    bfam_long_real_t *Pexact)
{
  int failure = 0;
  bfam_long_real_t diff = 0;
  for (size_t i=0; i<nx; ++i)
    diff = BFAM_MAX(BFAM_LONG_REAL_ABS(P[i] - Pexact[i]), diff);

  if (diff > eps)
  {
    failure = 1;
    BFAM_LERROR("Failed Test: %"BFAM_LONG_REAL_PRIe, diff);
  }

  return failure;
}

#define N 3
#define M 4

bfam_long_real_t A[] = {
   2,
  -1,
   0,
   1,
   0,
  -1,
   3,
   7,
  -1
};

bfam_long_real_t A2[] = {
   2,
  -1,
   0,
   1,
   0,
  -1,
   3,
   7,
  -1
};

bfam_long_real_t B[] = {
  4,
 -2,
  0,
 -1,
  3,
  0,
 -1,
  2,
 -1,
 -3,
 -1,
 -1
};


bfam_long_real_t b[] = {
  1,
  2,
  3
};

bfam_long_real_t x[] = {
  BFAM_LONG_REAL( 1.5),
  BFAM_LONG_REAL(-3.5),
  BFAM_LONG_REAL( 0.5)
};

bfam_long_real_t c[] = {
  BFAM_LONG_REAL(-5.0),
  BFAM_LONG_REAL(-4.5),
  BFAM_LONG_REAL( 3.0),
  BFAM_LONG_REAL(-9.0)
};

bfam_long_real_t twoc[] = {
  -10,
  - 9,
    6,
  -18
};

bfam_long_real_t C[] = {
  5,
 -4,
  1,
 -4,
  5,
  1,
  1,
  0,
 34,
 -3,
 -6,
 12
};

bfam_long_real_t D[] = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};

int
main (int argc, char *argv[])
{
  int failures = 0;

  const char *strings[] = {"test1", "test2", "test3", NULL};
  const char *list = "test1,test2,test3";
  char join[BFAM_BUFSIZ];
  bfam_util_strcsl(join, strings);

  failures += strcmp(list, join);

  size_t p[N], q[N];
  bfam_long_real_t work[N];

  bfam_util_lu_factor(N, A, p, q);
  bfam_util_lu_solve(N, A, b, p, q, work);

  failures += check_approx_eq(BFAM_LONG_REAL_EPS*100, N, b, x);

  bfam_util_mvmult(M, N, B, M, x, c);

  failures += check_approx_eq(BFAM_LONG_REAL_EPS*100, M, c, twoc);

  bfam_util_mmmult(M, N, N, B, M, A2, N, D, M);

  failures += check_approx_eq(BFAM_LONG_REAL_EPS*100, M*N, C, D);

  if(failures)
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}
