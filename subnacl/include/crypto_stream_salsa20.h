#ifndef crypto_stream_salsa20_H
#define crypto_stream_salsa20_H

#define crypto_stream_salsa20_KEYBYTES 32
#define crypto_stream_salsa20_NONCEBYTES 8

#ifdef __cplusplus

extern std::string crypto_stream_salsa20(size_t,const std::string &,const std::string &);
extern std::string crypto_stream_salsa20_xor(const std::string &,const std::string &,const std::string &);

extern "C" {
#endif

extern int crypto_stream_salsa20(unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_salsa20_xor(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_salsa20_beforenm(unsigned char *,const unsigned char *);
extern int crypto_stream_salsa20_afternm(unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_salsa20_xor_afternm(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);

#ifdef __cplusplus
}
#endif

#define crypto_stream_salsa20_IMPLEMENTATION "crypto_stream/salsa20/ref"
#define crypto_stream_salsa20_VERSION "-"

#endif
