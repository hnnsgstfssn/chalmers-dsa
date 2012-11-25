#include "dsa.h"

void dsa_genkey(DSA *dsa){
  assert(dsa != NULL);
  gmp_randstate_t rs;
  gmp_randinit_default(rs);
  gmp_randseed_ui(rs, arc4random());

  mpz_set(dsa->x, dsa->q);
  mpz_sub_ui(dsa->x, dsa->q, 1);
  mpz_urandomm(dsa->x, rs, dsa->x);
  mpz_add_ui(dsa->x, dsa->x, 1);

  mpz_powm(dsa->y, dsa->g, dsa->x, dsa->p);
  gmp_randclear(rs);
}
