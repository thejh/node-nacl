#include "crypto_box_curve25519xsalsa20poly1305.h"

int crypto_box_curve25519xsalsa20poly1305(
  unsigned char *c,
  const unsigned char *m,unsigned long long mlen,
  const unsigned char *n,
  const unsigned char *pk,
  const unsigned char *sk
)
{
  unsigned char k[crypto_box_curve25519xsalsa20poly1305_BEFORENMBYTES];
  crypto_box_curve25519xsalsa20poly1305_beforenm(k,pk,sk);
  return crypto_box_curve25519xsalsa20poly1305_afternm(c,m,mlen,n,k);
}

int crypto_box_curve25519xsalsa20poly1305_open(
  unsigned char *m,
  const unsigned char *c,unsigned long long clen,
  const unsigned char *n,
  const unsigned char *pk,
  const unsigned char *sk
)
{
  unsigned char k[crypto_box_curve25519xsalsa20poly1305_BEFORENMBYTES];
  crypto_box_curve25519xsalsa20poly1305_beforenm(k,pk,sk);
  return crypto_box_curve25519xsalsa20poly1305_open_afternm(m,c,clen,n,k);
}
