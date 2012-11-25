#include "dsa.h"

DSA_SIG *dsa_sign(DSA *dsa, mpz_t D){
  if(dsa_validate_params(dsa))
    return NULL;

  DSA_SIG *sig = malloc(sizeof(DSA_SIG));
  mpz_init_set_ui(sig->r, 0);
  mpz_init_set_ui(sig->s, 0);

  gmp_randstate_t rs;
  gmp_randinit_default(rs);
  gmp_randseed_ui(rs, arc4random());

  mpz_t k;
  mpz_init(k);

  while(mpz_cmp_ui(sig->r, 0) == 0 || mpz_cmp_ui(sig->s, 0) == 0){
    mpz_set(k, dsa->q);
    mpz_sub_ui(k, k, 1);
    mpz_urandomm(k, rs, k);
    mpz_add_ui(k, k, 1);

    mpz_powm(sig->r, dsa->g, k, dsa->p);

    mpz_mod(sig->r, sig->r, dsa->q);

    mpz_set(sig->s, D);

    mpz_addmul(sig->s, dsa->x, sig->r);

    assert(mpz_invert(k, k, dsa->q) != 0);

    mpz_mul(sig->s, sig->s, k);

    mpz_mod(sig->s, sig->s, dsa->q);
  }

  mpz_clear(k);
  gmp_randclear(rs);
  return sig;
}
