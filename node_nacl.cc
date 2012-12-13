#include <v8.h>
#include <node.h>
#include <node_buffer.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <crypto_box.h>
#include <crypto_sign.h>
#include <crypto_secretbox.h>
#include <crypto_onetimeauth.h>

using namespace std;
using namespace node;
using namespace v8;

static Handle<Value> node_crypto_box (const Arguments&);
static Handle<Value> node_crypto_box_open (const Arguments&);
static Handle<Value> node_crypto_box_keypair (const Arguments&);

static Handle<Value> node_crypto_sign (const Arguments&);
static Handle<Value> node_crypto_sign_open (const Arguments&);
static Handle<Value> node_crypto_sign_keypair (const Arguments&);

static Handle<Value> node_crypto_secretbox (const Arguments&);
static Handle<Value> node_crypto_secretbox_open (const Arguments&);

static Handle<Value> node_crypto_onetimeauth (const Arguments&);
static Handle<Value> node_crypto_onetimeauth_verify (const Arguments&);


static string buf_to_str (Handle<Object> b) {
  return string(Buffer::Data(b), Buffer::Length(b));
}

static Buffer* str_to_buf (string s) {
  Buffer* res = Buffer::New(s.length());
  memcpy(Buffer::Data(res), s.c_str(), s.length());
  return res;
}

#define THROW_ERROR(msg) \
  ThrowException(Exception::Error(String::New(msg)))

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
    return THROW_ERROR("box error");
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
    return THROW_ERROR("box_open error");
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
    return THROW_ERROR("sign error");
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
    return THROW_ERROR("sign_open error");
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

static Handle<Value> node_crypto_secretbox (const Arguments& args) {
  HandleScope scope;
  string m = buf_to_str(args[0]->ToObject());
  string n = buf_to_str(args[1]->ToObject());
  string k = buf_to_str(args[2]->ToObject());
  try {
    string c = crypto_secretbox(m,n,k);
    return scope.Close(str_to_buf(c)->handle_);
  } catch(...) {
    return THROW_ERROR("secretbox error");
  }
}

static Handle<Value> node_crypto_secretbox_open (const Arguments& args) {
  HandleScope scope;
  string c = buf_to_str(args[0]->ToObject());
  string n = buf_to_str(args[1]->ToObject());
  string k = buf_to_str(args[2]->ToObject());
  try {
    string m = crypto_secretbox_open(c,n,k);
    return scope.Close(str_to_buf(m)->handle_);
  } catch(...) {
    return THROW_ERROR("secretbox_open error");
  }
}

static Handle<Value> node_crypto_onetimeauth (const Arguments& args) {
  HandleScope scope;
  string m = buf_to_str(args[0]->ToObject());
  string k = buf_to_str(args[1]->ToObject());
  try {
    string c = crypto_onetimeauth(m,k);
    return scope.Close(str_to_buf(c)->handle_);
  } catch(...) {
    return THROW_ERROR("onetimeauth error");
  }
}

static Handle<Value> node_crypto_onetimeauth_verify (const Arguments& args) {
  HandleScope scope;
  string a = buf_to_str(args[0]->ToObject());
  string m = buf_to_str(args[1]->ToObject());
  string k = buf_to_str(args[2]->ToObject());
  try {
    crypto_onetimeauth_verify(a,m,k);
    return scope.Close(Null());
  } catch(...) {
    return THROW_ERROR("onetimeauth_verify error");
  }
}


extern "C" {
  void init (Handle<Object> target) {
    HandleScope scope;
    
    NODE_SET_METHOD(target, "box", node_crypto_box);
    NODE_SET_METHOD(target, "box_open", node_crypto_box_open);
    NODE_SET_METHOD(target, "box_keypair", node_crypto_box_keypair);
  
    NODE_SET_METHOD(target, "sign", node_crypto_sign);
    NODE_SET_METHOD(target, "sign_open", node_crypto_sign_open);
    NODE_SET_METHOD(target, "sign_keypair", node_crypto_sign_keypair);

    NODE_SET_METHOD(target, "secretbox", node_crypto_secretbox);
    NODE_SET_METHOD(target, "secretbox_open", node_crypto_secretbox_open);

    NODE_SET_METHOD(target, "onetimeauth", node_crypto_onetimeauth);
    NODE_SET_METHOD(target, "onetimeauth_verify", node_crypto_onetimeauth_verify);
  
    target->Set(String::NewSymbol("box_NONCEBYTES"), Integer::New(crypto_box_NONCEBYTES));
    target->Set(String::NewSymbol("box_PUBLICKEYBYTES"), Integer::New(crypto_box_PUBLICKEYBYTES));
    target->Set(String::NewSymbol("box_SECRETKEYBYTES"), Integer::New(crypto_box_SECRETKEYBYTES));
  
    target->Set(String::NewSymbol("sign_PUBLICKEYBYTES"), Integer::New(crypto_sign_PUBLICKEYBYTES));
    target->Set(String::NewSymbol("sign_SECRETKEYBYTES"), Integer::New(crypto_sign_SECRETKEYBYTES));
  }
  NODE_MODULE(node_nacl, init)
}
