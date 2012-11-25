#include "dsa.h"
#include <assert.h>
#include <stdlib.h>

int dsa_verify(DSA *dsa, mpz_t D, DSA_SIG *sig){
  assert(dsa != NULL);
  assert(sig != NULL);
  if(dsa_validate_params(dsa))
    return -1;
  if(mpz_cmp_ui(sig->r, 0) <= 0 || mpz_cmp_ui(sig->s, 0) <= 0)
    return 0;
  if(mpz_cmp(sig->r, dsa->q) >= 0 || mpz_cmp(sig->s, dsa->q) >= 0)
    return 0;
  mpz_t w, u1, u2, v;
  mpz_init(w);
  mpz_init(u1);
  mpz_init(u2);
  mpz_init(v);
  if(mpz_invert(w, sig->s, dsa->q) == 0)
    goto clean_exit_invalid;
  mpz_set(u1, D);
  mpz_mul(u1, u1, w);
  mpz_mod(u1, u1, dsa->q);

  mpz_set(u2, sig->r);
  mpz_mul(u2, u2, w);
  mpz_mod(u2, u2, dsa->q);

  mpz_powm(u1, dsa->g, u1, dsa->p);
  mpz_powm(u2, dsa->y, u2, dsa->p);
  mpz_mul(v, u1, u2);
  mpz_mod(v, v, dsa->p);
  mpz_mod(v, v, dsa->q);

  if(mpz_cmp(v, sig->r) == 0)
    return 1;

clean_exit_invalid:
  mpz_clear(w);
  mpz_clear(u1);
  mpz_clear(u2);
  mpz_clear(v);
  return 0;
}
