#include <v8.h>
#include <node.h>
#include <node_buffer.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <crypto_box.h>
#include <crypto_sign.h>

using namespace std;
using namespace node;
using namespace v8;

static Handle<Value> node_crypto_box (const Arguments&);
static Handle<Value> node_crypto_box_open (const Arguments&);
static Handle<Value> node_crypto_box_keypair (const Arguments&);

static Handle<Value> node_crypto_sign_keypair (const Arguments&);

extern "C" void init (Handle<Object>);


static string buf_to_str (Handle<Object> b) {
  return string(Buffer::Data(b), Buffer::Length(b));
}

static Buffer* str_to_buf (string s) {
  Buffer* res = Buffer::New(s.length());
  memcpy(Buffer::Data(res), s.c_str(), s.length());
  return res;
}


static Handle<Value> node_crypto_box (const Arguments& args) {
  HandleScope scope;
  string m = buf_to_str(args[0]->ToObject());
  string n = buf_to_str(args[1]->ToObject());
  string pk = buf_to_str(args[2]->ToObject());
  string sk = buf_to_str(args[3]->ToObject());
  try {
    string c = crypto_box(m,n,pk,sk);
    return scope.Close(str_to_buf(c)->handle_);
  } catch(...) {
    return scope.Close(Null());
  }
}

static Handle<Value> node_crypto_box_open (const Arguments& args) {
  HandleScope scope;
  string c = buf_to_str(args[0]->ToObject());
  string n = buf_to_str(args[1]->ToObject());
  string pk = buf_to_str(args[2]->ToObject());
  string sk = buf_to_str(args[3]->ToObject());
  try {
    string m = crypto_box_open(c,n,pk,sk);
    return scope.Close(str_to_buf(m)->handle_);
  } catch(...) {
    return scope.Close(Null());
  }
}

static Handle<Value> node_crypto_box_keypair (const Arguments& args) {
  HandleScope scope;
  string sk;
  Buffer* pk_buf = str_to_buf(crypto_box_keypair(&sk));
  Buffer* sk_buf = str_to_buf(sk);
  Local<Array> res = Array::New(2);
  res->Set(0, pk_buf->handle_);
  res->Set(1, sk_buf->handle_);
  return scope.Close(res);
}


static Handle<Value> node_crypto_sign (const Arguments& args) {
  HandleScope scope;
  string m = buf_to_str(args[0]->ToObject());
  string sk = buf_to_str(args[1]->ToObject());
  try {
    string sm = crypto_sign(m,sk);
    return scope.Close(str_to_buf(sm)->handle_);
  } catch(...) {
    return scope.Close(Null());
  }
}

static Handle<Value> node_crypto_sign_open (const Arguments& args) {
  HandleScope scope;
  string sm = buf_to_str(args[0]->ToObject());
  string pk = buf_to_str(args[1]->ToObject());
  try {
    string m = crypto_sign_open(sm,pk);
    return scope.Close(str_to_buf(m)->handle_);
  } catch(...) {
    return scope.Close(Null());
  }
}

static Handle<Value> node_crypto_sign_keypair (const Arguments& args) {
  HandleScope scope;
  string sk;
  Buffer* pk_buf = str_to_buf(crypto_sign_keypair(&sk));
  Buffer* sk_buf = str_to_buf(sk);
  Local<Array> res = Array::New(2);
  res->Set(0, pk_buf->handle_);
  res->Set(1, sk_buf->handle_);
  return scope.Close(res);
}

extern "C" void init (Handle<Object> target) {
  HandleScope scope;
  NODE_SET_METHOD(target, "box", node_crypto_box);
  NODE_SET_METHOD(target, "box_open", node_crypto_box_open);
  NODE_SET_METHOD(target, "box_keypair", node_crypto_box_keypair);
  
  NODE_SET_METHOD(target, "sign", node_crypto_sign);
  NODE_SET_METHOD(target, "sign_open", node_crypto_sign_open);
  NODE_SET_METHOD(target, "sign_keypair", node_crypto_sign_keypair);
  
  target->Set(v8::String::NewSymbol("box_NONCEBYTES"), Integer::New(crypto_box_NONCEBYTES));
  target->Set(v8::String::NewSymbol("box_PUBLICKEYBYTES"), Integer::New(crypto_box_PUBLICKEYBYTES));
  target->Set(v8::String::NewSymbol("box_SECRETKEYBYTES"), Integer::New(crypto_box_SECRETKEYBYTES));
  
  target->Set(v8::String::NewSymbol("sign_PUBLICKEYBYTES"), Integer::New(crypto_sign_PUBLICKEYBYTES));
  target->Set(v8::String::NewSymbol("sign_SECRETKEYBYTES"), Integer::New(crypto_sign_SECRETKEYBYTES));
}
