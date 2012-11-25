#include "dsa.h"
#include <fcntl.h>
#include <unistd.h>

void dsa_genkey(DSA *dsa){
  assert(dsa != NULL);
  gmp_randstate_t rs;
  gmp_randinit_default(rs);
  int source = open("/dev/random", O_RDONLY);
  int seed;
  read(source, &seed, sizeof(seed));
  close(source);
  gmp_randseed_ui(rs, seed);

  mpz_set(dsa->x, dsa->q);
  mpz_sub_ui(dsa->x, dsa->q, 1);
  mpz_urandomm(dsa->x, rs, dsa->x);
  mpz_add_ui(dsa->x, dsa->x, 1);

  mpz_powm(dsa->y, dsa->g, dsa->x, dsa->p);
  gmp_randclear(rs);
}
