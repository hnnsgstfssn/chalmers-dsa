// Includes
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "dsa.h"

int main(int argc, char **argv){
  DSA *dsa = malloc(sizeof(DSA));

  mpz_init(dsa->p);
  mpz_init(dsa->q);
  mpz_init(dsa->g);

  gmp_scanf("p=%Zu\nq=%Zu\ng=%Zu\n", dsa->p, dsa->q, dsa->g);

  if(dsa_validate_params(dsa))
  {
    printf("invalid group\n");
    return EXIT_FAILURE;
  }
  printf("valid group\n");


  char szCase[33];
  scanf("%32s\n", szCase);

  if(strcmp(szCase, "verify") == 0){
    mpz_init(dsa->y);

    gmp_scanf("y=%Zu\n", dsa->y);

    mpz_t D;
    mpz_init(D);
    DSA_SIG *sig = malloc(sizeof(DSA_SIG));
    mpz_init(sig->r);
    mpz_init(sig->s);

    while(gmp_scanf("D=%ZX\nr=%Zu\ns=%Zu\n", D, sig->r, sig->s) != EOF){
      if(dsa_verify(dsa, D, sig))
        printf("signature_valid\n");
      else
        printf("signature_invalid\n");
    }
    mpz_clear(sig->r);
    mpz_clear(sig->s);
    free(sig);
    mpz_clear(D);
  } else if(strcmp(szCase, "genkey") == 0){
    mpz_init(dsa->x);
    mpz_init(dsa->y);

    unsigned int n;
    scanf("n=%u\n",&n);

    for(unsigned int i = 0; i < n; ++i){

      dsa_genkey(dsa);

      gmp_printf("x=%Zu\n", dsa->x);
      gmp_printf("y=%Zu\n", dsa->y);

    }
    mpz_clear(dsa->x);
    mpz_clear(dsa->y);
  }
  else if(strcmp(szCase, "sign") == 0){
    mpz_init(dsa->x);
    mpz_init(dsa->y);

    // Digest and signature components
    mpz_t D;
    mpz_init(D);
    DSA_SIG *sig;

    gmp_scanf("x=%Zu\ny=%Zu\n", dsa->x, dsa->y);

    while(gmp_scanf("D=%ZX\n", D) != EOF){
      sig = dsa_sign(dsa, D);

      gmp_printf("r=%Zu\n", sig->r);
      gmp_printf("s=%Zu\n", sig->s);

      free(sig);
    }
    mpz_clear(D);
  } else {
    printf("bad case\n");
    return EXIT_FAILURE;
  }

  mpz_clear(dsa->p);
  mpz_clear(dsa->q);
  mpz_clear(dsa->g);
  free(dsa);

  return EXIT_SUCCESS;
}
