#ifndef LIGHTNING_BITCOIN_PRIVKEY_H
#define LIGHTNING_BITCOIN_PRIVKEY_H
#include "config.h"
#include <ccan/short_types/short_types.h>
#include <ccan/structeq/structeq.h>
#include <wally_bip39.h>

#define PRIVKEY_LEN 32

/* General 256-bit secret, which must be private.  Used in various places. */
struct secret {
	u8 data[32];
};

/* You probably shouldn't compare secrets in non-const time! */
bool secret_eq_consttime(const struct secret *a, const struct secret *b);

/* This is a private key.  Keep it secret. */
struct privkey {
	struct secret secret;
};

struct mnemonic {
    char words[BIP39_WORDLIST_LEN];
    char passphrase[255];
};

/* marshal/unmarshal functions */
void fromwire_secret(const u8 **cursor, size_t *max, struct secret *secret);
void fromwire_privkey(const u8 **cursor, size_t *max, struct privkey *privkey);
void fromwire_mnemonic(const u8 **cursor, size_t *max, struct mnemonic *mnemonic);
void towire_mnemonic(u8 **pptr, const struct mnemonic *mnemonic);
void towire_privkey(u8 **pptr, const struct privkey *privkey);
void towire_secret(u8 **pptr, const struct secret *secret);


#endif /* LIGHTNING_BITCOIN_PRIVKEY_H */
