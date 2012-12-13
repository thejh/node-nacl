#include "crypto_verify_32.h"
#include "crypto_auth_hmacsha512256.h"

int crypto_auth_hmacsha512256_verify(const unsigned char *h,const unsigned char *in,unsigned long long inlen,const unsigned char *k)
{
  unsigned char correct[32];
  crypto_auth_hmacsha512256(correct,in,inlen,k);
  return crypto_verify_32(h,correct);
}
