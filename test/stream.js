
var test = require("tap").test;
var crypto = require("crypto");
var n = require("../index").nacl;

test("stream", function(t) {
    // test vectors adapted from naclcrypto-20090310.pdf, chapter 8

    var nonceprefix = Buffer("69696ee955b62b73"+ "cd62bda875fc73d6", "hex");
    var noncesuffix = Buffer("8219e0036b7a0b37", "hex");
    var nonce = Buffer.concat([nonceprefix, noncesuffix]);
    var k1 = Buffer("1b27556473e985d4"+"62cd51197a9a46c7"+
                    "6009549eac6474f2"+"06c4ee0844f68389", "hex");
    var keystream = n.stream(4194304, nonce, k1);
    t.equal(keystream.length, 4194304);
    var h2 = crypto.createHash("sha256");
    h2.update(keystream, "binary");
    t.equal(h2.digest("hex"),
            "662b9d0e3463029156069b12f918691a98f7dfb2ca0393c96bbfc6b1fbd630a2");
    t.end();
});
