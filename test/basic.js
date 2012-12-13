
var test = require("tap").test;

var n = require("../index").nacl;
console.log("loaded");

test("constants", function(t) {
         t.equal(n.box_NONCEBYTES, 24, "box_NONCEBYTES");
         t.equal(n.box_PUBLICKEYBYTES, 32, "box_PUBLICKEYBYTES");
         t.equal(n.box_SECRETKEYBYTES, 32, "box_SECRETKEYBYTES");
         t.end();
     });

test("box", function(t) {
         var keys = n.box_keypair();
         t.equal(keys.length, 2);
         //console.log(keys[0].toString("hex"));
         //console.log(keys[1].toString("hex"));
         var alice_pub = keys[0];
         var alice_priv = keys[1];
         keys = n.box_keypair();
         var bob_pub = keys[0];
         var bob_priv = keys[1];
         var nonce = Buffer(24);
         nonce.fill(0);
         var boxed = n.box(Buffer("message"), nonce, alice_pub, bob_priv);
         //console.log(boxed.toString("hex"));
         var unboxed = n.box_open(boxed, nonce, bob_pub, alice_priv);
         //console.log(unboxed.toString("hex"));
         t.equal("message", unboxed.toString("binary"), "unboxed==msg");

         unboxed = n.box_open(boxed, nonce, alice_pub, bob_priv);
         t.equal("message", unboxed.toString("binary"), "both keypairs work");

         t.throws(function(){n.box_open(boxed, nonce, alice_pub, bob_pub);},
                  "bad keys");
         t.throws(function(){n.box_open(Buffer.concat([boxed, Buffer([0])]),
                                        nonce, alice_pub, bob_pub);},
                  "bad message");
         var nonce1 = Buffer(nonce);
         nonce1.fill(1);
         t.throws(function(){n.box_open(Buffer.concat([boxed, Buffer([0])]),
                                        nonce1, alice_pub, bob_pub);},
                  "wrong nonce");
         
         t.end();
     });
