#ifndef crypto_stream_salsa208_H
#define crypto_stream_salsa208_H

#define crypto_stream_salsa208_KEYBYTES 32
#define crypto_stream_salsa208_NONCEBYTES 8

#ifdef __cplusplus

extern std::string crypto_stream_salsa208(size_t,const std::string &,const std::string &);
extern std::string crypto_stream_salsa208_xor(const std::string &,const std::string &,const std::string &);

extern "C" {
#endif

extern int crypto_stream_salsa208(unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_salsa208_xor(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_salsa208_beforenm(unsigned char *,const unsigned char *);
extern int crypto_stream_salsa208_afternm(unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_salsa208_xor_afternm(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);

#ifdef __cplusplus
}
#endif

#define crypto_stream_salsa208_IMPLEMENTATION "crypto_stream/salsa208/ref"
#define crypto_stream_salsa208_VERSION "-"

#endif
