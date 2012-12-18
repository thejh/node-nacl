
var test = require("tap").test;
var crypto = require("crypto");

var n = require("../index").nacl;

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
var join = Buffer.concat;
var buf0 = Buffer([0x00]);

test("secretbox", function(t) {
    t.equivalent(n.secretbox(msg, nonce, key), boxed);
    t.equivalent(n.secretbox_open(boxed, nonce, key), msg);
    t.throws(function() { n.secretbox_open(join([boxed, buf0]),
                                           nonce, key); });
    t.throws(function() { n.secretbox_open(join([boxed.slice(0,-1), buf0]),
                                           nonce, key); });
    t.throws(function() { n.secretbox_open(join([buf0, boxed.slice(1)]),
                                           nonce, key); });
    t.throws(function() { n.secretbox_open(boxed,
                                           join([nonce.slice(0,-1), buf0]),
                                           key); });
    t.throws(function() { n.secretbox_open(boxed, nonce,
                                           join([key.slice(0,-1), buf0])); });
    t.end();
});

test("secretbox-nacl", function(t) {
    var sb1_firstkey = Buffer([0x1b,0x27,0x55,0x64,0x73,0xe9,0x85,0xd4
                               ,0x62,0xcd,0x51,0x19,0x7a,0x9a,0x46,0xc7
                               ,0x60,0x09,0x54,0x9e,0xac,0x64,0x74,0xf2
                               ,0x06,0xc4,0xee,0x08,0x44,0xf6,0x83,0x89]);
    var sb1_nonce = Buffer([0x69,0x69,0x6e,0xe9,0x55,0xb6,0x2b,0x73
                            ,0xcd,0x62,0xbd,0xa8,0x75,0xfc,0x73,0xd6
                            ,0x82,0x19,0xe0,0x03,0x6b,0x7a,0x0b,0x37]);
    var sb1_m = Buffer([0xbe,0x07,0x5f,0xc5,0x3c,0x81,0xf2,0xd5
                        ,0xcf,0x14,0x13,0x16,0xeb,0xeb,0x0c,0x7b
                        ,0x52,0x28,0xc5,0x2a,0x4c,0x62,0xcb,0xd4
                        ,0x4b,0x66,0x84,0x9b,0x64,0x24,0x4f,0xfc
                        ,0xe5,0xec,0xba,0xaf,0x33,0xbd,0x75,0x1a
                        ,0x1a,0xc7,0x28,0xd4,0x5e,0x6c,0x61,0x29
                        ,0x6c,0xdc,0x3c,0x01,0x23,0x35,0x61,0xf4
                        ,0x1d,0xb6,0x6c,0xce,0x31,0x4a,0xdb,0x31
                        ,0x0e,0x3b,0xe8,0x25,0x0c,0x46,0xf0,0x6d
                        ,0xce,0xea,0x3a,0x7f,0xa1,0x34,0x80,0x57
                        ,0xe2,0xf6,0x55,0x6a,0xd6,0xb1,0x31,0x8a
                        ,0x02,0x4a,0x83,0x8f,0x21,0xaf,0x1f,0xde
                        ,0x04,0x89,0x77,0xeb,0x48,0xf5,0x9f,0xfd
                        ,0x49,0x24,0xca,0x1c,0x60,0x90,0x2e,0x52
                        ,0xf0,0xa0,0x89,0xbc,0x76,0x89,0x70,0x40
                        ,0xe0,0x82,0xf9,0x37,0x76,0x38,0x48,0x64
                        ,0x5e,0x07,0x05]);
    var sb1_c = n.secretbox(sb1_m, sb1_nonce, sb1_firstkey);
    t.equivalent(sb1_c, Buffer([0xf3,0xff,0xc7,0x70,0x3f,0x94,0x00,0xe5
                                ,0x2a,0x7d,0xfb,0x4b,0x3d,0x33,0x05,0xd9
                                ,0x8e,0x99,0x3b,0x9f,0x48,0x68,0x12,0x73
                                ,0xc2,0x96,0x50,0xba,0x32,0xfc,0x76,0xce
                                ,0x48,0x33,0x2e,0xa7,0x16,0x4d,0x96,0xa4
                                ,0x47,0x6f,0xb8,0xc5,0x31,0xa1,0x18,0x6a
                                ,0xc0,0xdf,0xc1,0x7c,0x98,0xdc,0xe8,0x7b
                                ,0x4d,0xa7,0xf0,0x11,0xec,0x48,0xc9,0x72
                                ,0x71,0xd2,0xc2,0x0f,0x9b,0x92,0x8f,0xe2
                                ,0x27,0x0d,0x6f,0xb8,0x63,0xd5,0x17,0x38
                                ,0xb4,0x8e,0xee,0xe3,0x14,0xa7,0xcc,0x8a
                                ,0xb9,0x32,0x16,0x45,0x48,0xe5,0x26,0xae
                                ,0x90,0x22,0x43,0x68,0x51,0x7a,0xcf,0xea
                                ,0xbd,0x6b,0xb3,0x73,0x2b,0xc0,0xe9,0xda
                                ,0x99,0x83,0x2b,0x61,0xca,0x01,0xb6,0xde
                                ,0x56,0x24,0x4a,0x9e,0x88,0xd5,0xf9,0xb3
                                ,0x79,0x73,0xf6,0x22,0xa4,0x3d,0x14,0xa6
                                ,0x59,0x9b,0x1f,0x65,0x4c,0xb4,0x5a,0x74
                                ,0xe3,0x55,0xa5]));

    var sb2_firstkey = Buffer([0x1b,0x27,0x55,0x64,0x73,0xe9,0x85,0xd4
                               ,0x62,0xcd,0x51,0x19,0x7a,0x9a,0x46,0xc7
                               ,0x60,0x09,0x54,0x9e,0xac,0x64,0x74,0xf2
                               ,0x06,0xc4,0xee,0x08,0x44,0xf6,0x83,0x89]);
    var sb2_nonce = Buffer([0x69,0x69,0x6e,0xe9,0x55,0xb6,0x2b,0x73
                            ,0xcd,0x62,0xbd,0xa8,0x75,0xfc,0x73,0xd6
                            ,0x82,0x19,0xe0,0x03,0x6b,0x7a,0x0b,0x37]);
    var sb2_c = Buffer([0xf3,0xff,0xc7,0x70,0x3f,0x94,0x00,0xe5
                        ,0x2a,0x7d,0xfb,0x4b,0x3d,0x33,0x05,0xd9
                        ,0x8e,0x99,0x3b,0x9f,0x48,0x68,0x12,0x73
                        ,0xc2,0x96,0x50,0xba,0x32,0xfc,0x76,0xce
                        ,0x48,0x33,0x2e,0xa7,0x16,0x4d,0x96,0xa4
                        ,0x47,0x6f,0xb8,0xc5,0x31,0xa1,0x18,0x6a
                        ,0xc0,0xdf,0xc1,0x7c,0x98,0xdc,0xe8,0x7b
                        ,0x4d,0xa7,0xf0,0x11,0xec,0x48,0xc9,0x72
                        ,0x71,0xd2,0xc2,0x0f,0x9b,0x92,0x8f,0xe2
                        ,0x27,0x0d,0x6f,0xb8,0x63,0xd5,0x17,0x38
                        ,0xb4,0x8e,0xee,0xe3,0x14,0xa7,0xcc,0x8a
                        ,0xb9,0x32,0x16,0x45,0x48,0xe5,0x26,0xae
                        ,0x90,0x22,0x43,0x68,0x51,0x7a,0xcf,0xea
                        ,0xbd,0x6b,0xb3,0x73,0x2b,0xc0,0xe9,0xda
                        ,0x99,0x83,0x2b,0x61,0xca,0x01,0xb6,0xde
                        ,0x56,0x24,0x4a,0x9e,0x88,0xd5,0xf9,0xb3
                        ,0x79,0x73,0xf6,0x22,0xa4,0x3d,0x14,0xa6
                        ,0x59,0x9b,0x1f,0x65,0x4c,0xb4,0x5a,0x74
                        ,0xe3,0x55,0xa5]);
    var sb2_m = n.secretbox_open(sb2_c, sb2_nonce, sb2_firstkey);
    t.equivalent(sb2_m, Buffer([0xbe,0x07,0x5f,0xc5,0x3c,0x81,0xf2,0xd5
                                ,0xcf,0x14,0x13,0x16,0xeb,0xeb,0x0c,0x7b
                                ,0x52,0x28,0xc5,0x2a,0x4c,0x62,0xcb,0xd4
                                ,0x4b,0x66,0x84,0x9b,0x64,0x24,0x4f,0xfc
                                ,0xe5,0xec,0xba,0xaf,0x33,0xbd,0x75,0x1a
                                ,0x1a,0xc7,0x28,0xd4,0x5e,0x6c,0x61,0x29
                                ,0x6c,0xdc,0x3c,0x01,0x23,0x35,0x61,0xf4
                                ,0x1d,0xb6,0x6c,0xce,0x31,0x4a,0xdb,0x31
                                ,0x0e,0x3b,0xe8,0x25,0x0c,0x46,0xf0,0x6d
                                ,0xce,0xea,0x3a,0x7f,0xa1,0x34,0x80,0x57
                                ,0xe2,0xf6,0x55,0x6a,0xd6,0xb1,0x31,0x8a
                                ,0x02,0x4a,0x83,0x8f,0x21,0xaf,0x1f,0xde
                                ,0x04,0x89,0x77,0xeb,0x48,0xf5,0x9f,0xfd
                                ,0x49,0x24,0xca,0x1c,0x60,0x90,0x2e,0x52
                                ,0xf0,0xa0,0x89,0xbc,0x76,0x89,0x70,0x40
                                ,0xe0,0x82,0xf9,0x37,0x76,0x38,0x48,0x64
                                ,0x5e,0x07,0x05]));


    // secretbox3 is just a C++ variant of secretbox[1]
    // secretbox4 is just a C++ variant of secretbox2


    for(var sb5_mlen=0; sb5_mlen < 1000; sb5_mlen++) {
        //console.log(sb5_mlen);
        var sb5_key = Buffer(crypto.randomBytes(32), "binary");
        var sb5_nonce = Buffer(crypto.randomBytes(24), "binary");
        var sb5_msg = Buffer(crypto.randomBytes(sb5_mlen), "binary");
        var sb5_c = n.secretbox(sb5_msg, sb5_nonce, sb5_key);
        var sb5_m2 = n.secretbox_open(sb5_c, sb5_nonce, sb5_key);
        t.equivalent(sb5_msg, sb5_m2);
    }

    for(var sb6_mlen=0; sb6_mlen < 1000; sb6_mlen++) {
        //console.log(sb6_mlen);
        var sb6_key = Buffer(crypto.randomBytes(32), "binary");
        var sb6_nonce = Buffer(crypto.randomBytes(24), "binary");
        var sb6_msg = Buffer(crypto.randomBytes(sb6_mlen), "binary");
        var sb6_c = n.secretbox(sb6_msg, sb6_nonce, sb6_key);
        for (var sb6_caught=0; sb6_caught < 10; sb6_caught++) {
            // N.B. cumulative, that's how secretbox6.cpp was written
            sb6_c[Math.floor(Math.random()*sb6_mlen)] = Math.floor(Math.random()*256);
            try {
                var sb6_m2 = n.secretbox_open(sb6_c, sb6_nonce, sb6_key);
                if (sb6_msg.toString("hex") != sb6_m2.toString("hex")) {
                    t.fail("forgery"); // scary+unhelpful
                    break;
                }
                // else we randomly fixed the message, ok
            } catch (e) {
                t.equal(e.message, "ciphertext fails verification");
            }
        }
    }

    // secretbox7 is just a C variant of secretbox5
    // secretbox8 is just a C variant of secretbox6

    t.end();
});


