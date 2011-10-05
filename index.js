var binding = require('./build/Release/node_nacl')

// produces an authenticated ciphertext. might return null.
exports.box = function(message, nonce, pubkey, privkey) {
  if (typeof message === 'string') message = new Buffer(message)
  return binding.box(message, nonce, pubkey, privkey)
}

// opens a cryptobox. might return null.
exports.unbox = binding.box_open

// make a private and its corresponding public key
exports.boxKeypair = function() {
  var result = binding.box_keypair()
  return {private: result[0], public: result[1]}
}


exports.sign = function(message, privkey) {
  if (typeof message === 'string') message = new Buffer(message)
  return binding.sign(message, privkey)
}

exports.unsign = binding.sign_open

exports.signKeypair = function() {
  var result = binding.sign_keypair()
  return {private: result[0], public: result[1]}
}


exports.lengths =
{ box:
  { nonce: binding.box_NONCEBYTES
  , pubkey: binding.box_PUBLICKEYBYTES
  , privkey: binding.box_SECRETKEYBYTES
  }
, sign:
  { pubkey: binding.sign_PUBLICKEYBYTES
  , privkey: binding.sign_SECRETKEYBYTES
  }
}
