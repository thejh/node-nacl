WARNING: This library DOES NOT WORK on 64-bit systems, and there's nothing I can do about
it before the next version of NaCl is available.
=========================

Bindings for the [Networking and Cryptography library (NaCl)](http://nacl.cr.yp.to/).
This gives you a fast and easy-to-use crypto box: Put stuff inside, turn the key
and it's automagically signed and encrypted. Reverse direction works, too.
There's also signing functionality.
For details about how to use that stuff, go to the NaCl homepage.

Methods and Properties
======================
`box`, `unbox`, `sign` and `unsign` return `null` if one of the parameters is
incorrect or a signature is invalid. The methods never throw.

Crypto-Box
----------

    // encrypt and sign (message may be string or Buffer, all others must be Buffers, returns a Buffer)
    box(message, nonce, pubkey, privkey)
    // decrypt and validate (all parameters buffers, returns a Buffer or null)
    unbox(box, nonce, pubkey, privkey)
    // generates a new keypair, returns {private: <buffer>, public: <buffer>}
    boxKeypair()
    // lengths of nonces and public and private keys in bytes
    // { nonce: x, pubkey: x, privkey: x }
    lengths.box

Signatures
----------

    // sign, returns the signed message as Buffer (message is a Buffer or a string, privkey is a Buffer)
    sign(message, privkey)
    // verify signature and remove it (parameters are Buffers, returns a Buffer or null)
    unsign(message, pubkey)
    // generates a new keypair, returns {private: <buffer>, public: <buffer>}
    signKeypair()
    // lengths of public and private keys in bytes
    // { pubkey: x, privkey: x }
    lengths.sign

Installation
============
This takes some time because there's a long benchmark that takes place after the
actual C++ library got compiled. Didn't measure the time, but it's more than a
few minutes.

    npm install nacl
