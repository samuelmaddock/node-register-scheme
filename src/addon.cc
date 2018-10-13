#include <nan.h>
#include "register.h"

#define THROW_BAD_ARGS(msg)    \
    do {                       \
       Nan::ThrowTypeError(msg); \
       return;                   \
    } while (0);

NAN_METHOD(RPH) {
  Nan::HandleScope scope;
  if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsString()) {
    THROW_BAD_ARGS("Bad arguments");
  }

  std::string scheme_str(*(v8::String::Utf8Value(info[0])));
  std::string command_str(*(v8::String::Utf8Value(info[1])));

  const char* scheme = scheme_str.c_str();
  const char* command = command_str.c_str();

  bool success = Register(scheme, command);
  info.GetReturnValue().Set(Nan::New(success));
}

NAN_MODULE_INIT(Init) {
  Nan::Set(target,
           Nan::New("registerProtocolHandler").ToLocalChecked(),
           Nan::New<v8::FunctionTemplate>(RPH)->GetFunction());
}

NODE_MODULE(rph, Init)
