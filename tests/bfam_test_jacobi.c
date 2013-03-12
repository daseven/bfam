#include <bfam.h>

int
check_approx_eq(bfam_long_real_t eps, size_t nx, bfam_long_real_t *P,
    bfam_long_real_t *Pexact)
{
  int failure = 0;
  bfam_long_real_t diff = 0;
  for (size_t i=0; i<nx; ++i)
  {
    diff = BFAM_MAX(BFAM_LONG_REAL_ABS(P[i] - Pexact[i]), diff);
  }

  if (diff > eps)
  {
    failure = 1;
    BFAM_LERROR("Failed Test: %"BFAM_LONG_REAL_PRIe, diff);
  }

  return failure;
}

bfam_long_real_t P_0_0_0[] = {
  7.071067811865475e-01,
  7.071067811865475e-01,
  7.071067811865475e-01,
  7.071067811865475e-01,
  7.071067811865475e-01,
  7.071067811865475e-01,
  7.071067811865475e-01,
  7.071067811865475e-01,
  7.071067811865475e-01,
  7.071067811865475e-01,
};

bfam_long_real_t P_0_0_1[] = {
  -1.224744871391589e+00,
  -9.525793444156804e-01,
  -6.804138174397717e-01,
  -4.082482904638631e-01,
  -1.360827634879544e-01,
   1.360827634879544e-01,
   4.082482904638629e-01,
   6.804138174397717e-01,
   9.525793444156803e-01,
   1.224744871391589e+00,
};

bfam_long_real_t P_0_0_2[] = {
   1.581138830084190e+00,
   6.441676715157812e-01,
  -5.856069741052537e-02,
  -5.270462766947297e-01,
  -7.612890663368320e-01,
  -7.612890663368320e-01,
  -5.270462766947299e-01,
  -5.856069741052537e-02,
   6.441676715157808e-01,
   1.581138830084190e+00,
};

bfam_long_real_t P_0_0_3[] = {
  -1.870828693386972e+00,
  -1.796406152772192e-02,
   7.570568786682527e-01,
   7.621894676761732e-01,
   3.053890459712615e-01,
  -3.053890459712615e-01,
  -7.621894676761731e-01,
  -7.570568786682527e-01,
   1.796406152772115e-02,
   1.870828693386972e+00,
};

bfam_long_real_t P_2_1_3[] = {
  -3.872983346207417e+00,
  -5.817444120846532e-01,
   7.012809351157466e-01,
   6.454972243679030e-01,
  -7.969101535406189e-02,
  -8.048792550760273e-01,
  -8.606629658238709e-01,
   4.223623813765293e-01,
   3.713601315499292e+00,
   9.682458365518544e+00,
};

bfam_long_real_t P_m025_2_5[] = {
  -2.779196835777356e+01,
  -3.496214727847906e+00,
   1.840744719386286e+00,
   7.110677426982215e-01,
  -6.853585653210824e-01,
  -5.691663775602251e-01,
   2.902442683111531e-01,
   4.464568705409493e-01,
  -3.522101360068282e-01,
   7.090480208465177e-01,
};

int
main (int argc, char *argv[])
{
  int failures = 0;

#define LIST_OF_TESTS  \
  X(BFAM_LONG_REAL( 0.0),  BFAM_LONG_REAL(0.0), 0, 10, P_0_0_0) \
  X(BFAM_LONG_REAL( 0.0),  BFAM_LONG_REAL(0.0), 1, 10, P_0_0_1) \
  X(BFAM_LONG_REAL( 0.0),  BFAM_LONG_REAL(0.0), 2, 10, P_0_0_2) \
  X(BFAM_LONG_REAL( 0.0),  BFAM_LONG_REAL(0.0), 3, 10, P_0_0_3) \
  X(BFAM_LONG_REAL( 2.0),  BFAM_LONG_REAL(1.0), 3, 10, P_2_1_3) \
  X(BFAM_LONG_REAL(-0.25), BFAM_LONG_REAL(2.0), 5, 10, P_m025_2_5)

#define X(alpha, beta, N, nx, Pexact)                              \
  {                                                                \
    BFAM_INFO("Testing " #alpha " : " #beta " : " #N " : " #nx     \
              " : " #Pexact);                                      \
    BFAM_ALIGN(32) bfam_long_real_t x[nx];                         \
    BFAM_ALIGN(32) bfam_long_real_t P[nx];                         \
    for (size_t i=0; i<(nx); ++i)                                  \
    {                                                              \
      x[i] = BFAM_LONG_REAL(-1.0) + i*BFAM_LONG_REAL(2.0)/(nx-1);  \
    }                                                              \
    bfam_jacobi_p(alpha, beta, N, nx, x, P);                       \
    failures += check_approx_eq(BFAM_REAL_EPS*100, nx, P, Pexact); \
  }
  LIST_OF_TESTS
#undef X

  if(failures)
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}