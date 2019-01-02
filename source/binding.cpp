#include <napi.h>
#include "binding.h"

Napi::FunctionReference SimpleGPIO::constructor;

void SimpleGPIO::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(env, "SimpleGPIO", {
    InstanceMethod("setupInput", &SimpleGPIO::setupInput),
    InstanceMethod("setupOutput", &SimpleGPIO::setupOutput),
    InstanceMethod("write", &SimpleGPIO::write),
    InstanceMethod("read", &SimpleGPIO::read)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("SimpleGPIO", func);
}

SimpleGPIO::SimpleGPIO(const Napi::CallbackInfo &info) : Napi::ObjectWrap<SimpleGPIO>(info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  wiringPiSetupPhys();
}

SimpleGPIO::~SimpleGPIO() {}

void SimpleGPIO::setupInput(const Napi::CallbackInfo &info)
{
  int pin = info[0].ToNumber();
  pinMode(pin, INPUT);
}

void SimpleGPIO::setupOutput(const Napi::CallbackInfo &info)
{
  int pin = info[0].ToNumber();
  pinMode(pin, OUTPUT);
}

Napi::Value SimpleGPIO::read(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  int pin = info[0].ToNumber();

  int value = digitalRead(pin);
  return Napi::Boolean::New(env, value);
}

void SimpleGPIO::write(const Napi::CallbackInfo &info)
{
  int pin = info[0].ToNumber();
  int value = info[1].ToNumber();

  digitalWrite(pin, value);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  SimpleGPIO::Init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
