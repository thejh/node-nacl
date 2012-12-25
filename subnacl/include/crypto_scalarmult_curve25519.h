#ifndef crypto_scalarmult_curve25519_H
#define crypto_scalarmult_curve25519_H

#define crypto_scalarmult_curve25519_BYTES 32
#define crypto_scalarmult_curve25519_SCALARBYTES 32

#ifdef __cplusplus

extern std::string crypto_scalarmult_curve25519(const std::string &,const std::string &);
extern std::string crypto_scalarmult_curve25519_base(const std::string &);

extern "C" {
#endif

extern int crypto_scalarmult_curve25519(unsigned char *,const unsigned char *,const unsigned char *);
extern int crypto_scalarmult_curve25519_base(unsigned char *,const unsigned char *);

#ifdef __cplusplus
}
#endif

#define crypto_scalarmult_curve25519_IMPLEMENTATION "crypto_scalarmult/curve25519/ref"
#define crypto_scalarmult_curve25519_VERSION "-"

#endif
