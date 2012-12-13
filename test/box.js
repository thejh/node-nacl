
var test = require("tap").test;

var n = require("../index").nacl;

test("box", function(t) {

    // test case from naclcrypto-20090310.pdf, page 35

    var key = Buffer("1b27556473e985d462cd51197a9a46c7"+
                     "6009549eac6474f206c4ee0844f68389", "hex");
    var nonce = Buffer("69696ee955b62b73cd62bda875fc73d68219e0036b7a0b37", "hex");
    var msg = Buffer("be075fc53c81f2d5cf141316ebeb0c7b"+
                     "5228c52a4c62cbd44b66849b64244ffc"+
                     "e5ecbaaf33bd751a1ac728d45e6c6129"+
                     "6cdc3c01233561f41db66cce314adb31"+
                     "0e3be8250c46f06dceea3a7fa1348057"+
                     "e2f6556ad6b1318a024a838f21af1fde"+
                     "048977eb48f59ffd4924ca1c60902e52"+
                     "f0a089bc76897040e082f93776384864"+
                     "5e0705", "hex"); // 131 bytes long
    var boxed = Buffer("f3ffc7703f9400e52a7dfb4b3d3305d9"+
                       "8e993b9f48681273c29650ba32fc76ce"+
                       "48332ea7164d96a4476fb8c531a1186a"+
                       "c0dfc17c98dce87b4da7f011ec48c972"+
                       "71d2c20f9b928fe2270d6fb863d51738"+
                       "b48eeee314a7cc8ab932164548e526ae"+
                       "90224368517acfeabd6bb3732bc0e9da"+
                       "99832b61ca01b6de56244a9e88d5f9b3"+
                       "7973f622a43d14a6599b1f654cb45a74"+
                       "e355a5", "hex"); // 147-byte boxed packet

    var alice_sk = Buffer("77076d0a7318a57d3c16c17251b26645"+
                          "df4c2f87ebc0992ab177fba51db92c2a", "hex");
    var alice_pk = Buffer("8520f0098930a754748b7ddcb43ef75a"+
                          "0dbf3a0d26381af4eba4a98eaa9b4e6a", "hex");

    var bob_sk = Buffer("5dab087e624a8a4b79e17f8b83800ee6"+
                        "6f3bb1292618b6fd1c2f8b27ff88e0eb", "hex");
    var bob_pk = Buffer("de9edb7d7b7dc1b4d35b61c2ece43537"+
                        "3f8343c85b78674dadfc7e146f882b4f", "hex");

    // alice sends to bob
    t.equivalent(n.box(msg, nonce, bob_pk, alice_sk), boxed);
    t.equivalent(n.box_open(boxed, nonce, alice_pk, bob_sk), msg);

    // bob sends to alice
    t.equivalent(n.box(msg, nonce, alice_pk, bob_sk), boxed);
    t.equivalent(n.box_open(boxed, nonce, bob_pk, alice_sk), msg);


    // and keypair creation
    var alice = n.box_keypair(); // [0] is public key, [1] is private key
    var bob = n.box_keypair();
    var newboxed = n.box(msg, nonce, alice[0], bob[1]);
    t.equivalent(n.box_open(newboxed, nonce, bob[0], alice[1]), msg);

    // now the beforenm/afternm functions
    return t.end(); // not yet implemented

    var pre1 = n.box_beforenm(bob_pk, alice_sk);
    t.equivalent(n.box_afternm(msg, nonce, pre1), boxed);
    var pre2 = n.box_beforenm(alice_pk, bob_sk);
    t.equivalent(n.box_open_afternm(boxed, nonce, pre2), msg);

    t.end();
});
