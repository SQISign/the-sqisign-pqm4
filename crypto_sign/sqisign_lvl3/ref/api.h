// SPDX-License-Identifier: Apache-2.0

#ifndef api_h
#define api_h

#include <stddef.h>
#include <sqisign_namespace.h>

#define CRYPTO_SECRETKEYBYTES 529
#define CRYPTO_PUBLICKEYBYTES 97
#define CRYPTO_BYTES 224

#define CRYPTO_ALGNAME "SQIsign_lvl3"

SQISIGN_API
int
crypto_sign_keypair(unsigned char *pk, unsigned char *sk);

SQISIGN_API
int
crypto_sign(unsigned char *sm, size_t *smlen,
            const unsigned char *m, size_t mlen,
            const unsigned char *sk);

SQISIGN_API
int
crypto_sign_open(unsigned char *m, size_t *mlen,
                 const unsigned char *sm, size_t smlen,
                 const unsigned char *pk);

#endif /* api_h */
