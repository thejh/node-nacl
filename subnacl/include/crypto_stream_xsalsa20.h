#ifndef crypto_stream_xsalsa20_H
#define crypto_stream_xsalsa20_H

#define crypto_stream_xsalsa20_KEYBYTES 32
#define crypto_stream_xsalsa20_NONCEBYTES 24

#ifdef __cplusplus

extern std::string crypto_stream_xsalsa20(size_t,const std::string &,const std::string &);
extern std::string crypto_stream_xsalsa20_xor(const std::string &,const std::string &,const std::string &);

extern "C" {
#endif

extern int crypto_stream_xsalsa20(unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_xsalsa20_xor(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_xsalsa20_beforenm(unsigned char *,const unsigned char *);
extern int crypto_stream_xsalsa20_afternm(unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_xsalsa20_xor_afternm(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);

#ifdef __cplusplus
}
#endif

#define crypto_stream_xsalsa20_IMPLEMENTATION "crypto_stream/xsalsa20/ref"
#define crypto_stream_xsalsa20_VERSION "-"

#endif
