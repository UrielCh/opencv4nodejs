#include <iostream>
#include <napi.h>

#ifndef __FF_IWORKER_H__
#define __FF_IWORKER_H__

namespace FF {

class IWorker {
public:
  virtual std::string execute() = 0;
  virtual bool applyUnwrappers(const Napi::CallbackInfo& info) = 0;
};

class ISyncWorker : public IWorker {
public:
  virtual Napi::Value getReturnValue(const Napi::CallbackInfo& info) = 0;
};

class IAsyncWorker : public IWorker {
public:
  virtual Napi::Value getReturnValue() = 0;
};
} // namespace FF

#endif