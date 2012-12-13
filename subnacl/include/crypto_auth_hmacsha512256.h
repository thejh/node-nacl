#ifndef crypto_auth_hmacsha512256_H
#define crypto_auth_hmacsha512256_H

#define crypto_auth_hmacsha512256_BYTES 32
#define crypto_auth_hmacsha512256_KEYBYTES 32

#ifdef __cplusplus

extern std::string crypto_auth_hmacsha512256(const std::string &,const std::string &);
extern void crypto_auth_hmacsha512256_verify(const std::string &,const std::string &,const std::string &);

extern "C" {
#endif

extern int crypto_auth_hmacsha512256(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *);
extern int crypto_auth_hmacsha512256_verify(const unsigned char *,const unsigned char *,unsigned long long,const unsigned char *);

#ifdef __cplusplus
}
#endif

#define crypto_auth_hmacsha512256_IMPLEMENTATION "crypto_auth/hmacsha512256/ref"
#define crypto_auth_hmacsha512256_VERSION "-"

#endif
