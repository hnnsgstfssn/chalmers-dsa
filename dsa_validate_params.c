#include "dsa.h"
#include <assert.h>
#include <stdlib.h>

int dsa_validate_params(DSA *dsa){
  assert(dsa != NULL);
  if(mpz_sizeinbase(dsa->p, 2) < DSA_MIN_P_BITS)
    return 1;

  if(mpz_sizeinbase(dsa->q, 2) < DSA_MIN_Q_BITS)
    return 1;

  /* g > 1 should hold */
  if(mpz_cmp_ui(dsa->g, 1) <= 0)
    return 1;

  if(mpz_cmp(dsa->g, dsa->p) >= 0)
    return 1;

  mpz_t tmp;
  mpz_init(tmp);

  /* tmp = p - 1 */
  mpz_sub_ui(tmp, dsa->p, 1);

  /* q should be divisor of (p-1) */
  if(mpz_divisible_p(tmp, dsa->q) == 0)
    goto clean_exit_invalid;

  /* g^q mod p should == 1 */
  mpz_powm(tmp, dsa->g, dsa->q, dsa->p);
  if(mpz_cmp_ui(tmp, 1) != 0)
    goto clean_exit_invalid;

  /* p and q should be primes */
  if(mpz_probab_prime_p(dsa->p, DSA_REPS) == 0 && mpz_probab_prime_p(dsa->q, DSA_REPS) == 0)
    goto clean_exit_invalid;

  mpz_clear(tmp);
  return 0;

clean_exit_invalid:
  mpz_clear(tmp);
  return 1;
}
