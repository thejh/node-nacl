#ifndef crypto_onetimeauth_poly1305_H
#define crypto_onetimeauth_poly1305_H

#define crypto_onetimeauth_poly1305_BYTES 16
#define crypto_onetimeauth_poly1305_KEYBYTES 32

#ifdef __cplusplus

extern std::string crypto_onetimeauth_poly1305(const std::string &,const std::string &);
extern void crypto_onetimeauth_poly1305_verify(const std::string &,const std::string &,const std::string &);

extern "C" {
#endif

extern int crypto_onetimeauth_poly1305(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *);
extern int crypto_onetimeauth_poly1305_verify(const unsigned char *,const unsigned char *,unsigned long long,const unsigned char *);

#ifdef __cplusplus
}
#endif

#define crypto_onetimeauth_poly1305_IMPLEMENTATION "crypto_onetimeauth/poly1305/ref"
#define crypto_onetimeauth_poly1305_VERSION "-"

#endif
