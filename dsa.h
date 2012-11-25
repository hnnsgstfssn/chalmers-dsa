#ifndef H_DSA
#define H_DSA

#define DSA_MIN_Q_BITS 160
#define DSA_MIN_P_BITS 1024

/* REPS are used in mpz_probab_prime_p when validating the p, q, g tuple */
#define DSA_REPS 10

#include <gmp.h>

typedef struct DSA_SIG {
  mpz_t r;
  mpz_t s;
} DSA_SIG;

typedef struct DSA {
  mpz_t p;
  mpz_t q;
  mpz_t g;

  mpz_t x; /* private key */
  mpz_t y; /* public key */
} DSA;

DSA_SIG * dsa_sign(DSA *dsa, mpz_t D);

/* 1 if the signature is valid. zero otherwise */
int dsa_verify(DSA *dsa, mpz_t D, DSA_SIG *sig);

/* 1 if the parameters are invalid. zero otherwise */
int dsa_validate_params(DSA *dsa);

void dsa_genkey(DSA *dsa);

#endif /* H_DSA */

