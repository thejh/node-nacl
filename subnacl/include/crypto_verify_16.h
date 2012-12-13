#ifndef crypto_verify_16_H
#define crypto_verify_16_H

#define crypto_verify_16_BYTES 16

#ifdef __cplusplus


extern "C" {
#endif

extern int crypto_verify_16(const unsigned char *,const unsigned char *);

#ifdef __cplusplus
}
#endif

#define crypto_verify_16_IMPLEMENTATION "crypto_verify/16/ref"
#define crypto_verify_16_VERSION "-"

#endif
