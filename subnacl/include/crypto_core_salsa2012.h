#ifndef crypto_core_salsa2012_H
#define crypto_core_salsa2012_H

#define crypto_core_salsa2012_OUTPUTBYTES 64
#define crypto_core_salsa2012_INPUTBYTES 16
#define crypto_core_salsa2012_KEYBYTES 32
#define crypto_core_salsa2012_CONSTBYTES 16

#ifdef __cplusplus


extern "C" {
#endif

extern int crypto_core_salsa2012(unsigned char *,const unsigned char *,const unsigned char *,const unsigned char *);

#ifdef __cplusplus
}
#endif

#define crypto_core_salsa2012_IMPLEMENTATION "crypto_core/salsa2012/ref"
#define crypto_core_salsa2012_VERSION "-"

#endif
