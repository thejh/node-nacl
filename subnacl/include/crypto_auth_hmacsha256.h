#ifndef crypto_auth_hmacsha256_H
#define crypto_auth_hmacsha256_H

#define crypto_auth_hmacsha256_BYTES 32
#define crypto_auth_hmacsha256_KEYBYTES 32

#ifdef __cplusplus

extern std::string crypto_auth_hmacsha256(const std::string &,const std::string &);
extern void crypto_auth_hmacsha256_verify(const std::string &,const std::string &,const std::string &);

extern "C" {
#endif

extern int crypto_auth_hmacsha256(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *);
extern int crypto_auth_hmacsha256_verify(const unsigned char *,const unsigned char *,unsigned long long,const unsigned char *);

#ifdef __cplusplus
}
#endif

#define crypto_auth_hmacsha256_IMPLEMENTATION "crypto_auth/hmacsha256/ref"
#define crypto_auth_hmacsha256_VERSION "-"

#endif
