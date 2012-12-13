#ifndef crypto_hash_sha256_H
#define crypto_hash_sha256_H

#define crypto_hash_sha256_BYTES 32

#ifdef __cplusplus

extern std::string crypto_hash_sha256(const std::string &);

extern "C" {
#endif

extern int crypto_hash_sha256(unsigned char *,const unsigned char *,unsigned long long);

#ifdef __cplusplus
}
#endif

#define crypto_hash_sha256_IMPLEMENTATION "crypto_hash/sha256/ref"
#define crypto_hash_sha256_VERSION "-"

#endif
