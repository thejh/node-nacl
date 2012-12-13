
var test = require("tap").test;

var n = require("../index").nacl;
    
var rs = Buffer("eea6a7251c1e72916d11c2cb214d3c25"+
                "2539121d8e234e652d651fa4c8cff880", "hex");
var c = Buffer("8e993b9f48681273c29650ba32fc76ce"+
               "48332ea7164d96a4476fb8c531a1186a"+
               "c0dfc17c98dce87b4da7f011ec48c972"+
               "71d2c20f9b928fe2270d6fb863d51738"+
               "b48eeee314a7cc8ab932164548e526ae"+
               "90224368517acfeabd6bb3732bc0e9da"+
               "99832b61ca01b6de56244a9e88d5f9b3"+
               "7973f622a43d14a6599b1f654cb45a74"+
               "e355a5", "hex"); // 131 bytes long

test("onetimeauth", function(t) {
    t.equivalent(n.onetimeauth(c, rs),
                 Buffer("f3ffc7703f9400e52a7dfb4b3d3305d9", "hex"));
    t.end();
});
