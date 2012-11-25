A simple DSA implementation for a cryptography class at [Chalmers University of Technology](http://www.chalmers.se/en).

Assignment description is found in ´assignment.txt´.

Testdata given in assignment is located in `testdata/`.

Notable:
- Uses [GMP](http://www.gmplib.org)
- The digest is defined as a `mpz_t`
- Depends on `/dev/random`

A copy of the DSA spec can be found in section 4 of `fips_186-3.pdf`.
