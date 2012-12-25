#ifndef crypto_stream_aes128ctr_H
#define crypto_stream_aes128ctr_H

#define crypto_stream_aes128ctr_KEYBYTES 16
#define crypto_stream_aes128ctr_NONCEBYTES 16
#define crypto_stream_aes128ctr_BEFORENMBYTES 1408

#ifdef __cplusplus

extern std::string crypto_stream_aes128ctr(size_t,const std::string &,const std::string &);
extern std::string crypto_stream_aes128ctr_xor(const std::string &,const std::string &,const std::string &);

extern "C" {
#endif

extern int crypto_stream_aes128ctr(unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_aes128ctr_xor(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_aes128ctr_beforenm(unsigned char *,const unsigned char *);
extern int crypto_stream_aes128ctr_afternm(unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_aes128ctr_xor_afternm(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);

#ifdef __cplusplus
}
#endif

#define crypto_stream_aes128ctr_IMPLEMENTATION "crypto_stream/aes128ctr/portable"
#define crypto_stream_aes128ctr_VERSION "-"

#endif
