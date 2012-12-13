
var test = require("tap").test;

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
