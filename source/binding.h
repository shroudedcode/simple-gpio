#include <napi.h>
#include <wiringPi.h>

class SimpleGPIO : public Napi::ObjectWrap<SimpleGPIO>
{

public:
  static void Init(Napi::Env env, Napi::Object exports);
  SimpleGPIO(const Napi::CallbackInfo &info);
  ~SimpleGPIO();

private:
  static Napi::FunctionReference constructor;

  void setupInput(const Napi::CallbackInfo &info);
  void setupOutput(const Napi::CallbackInfo &info);
  Napi::Value read(const Napi::CallbackInfo &info);
  void write(const Napi::CallbackInfo &info);

};
