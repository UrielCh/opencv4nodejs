#include "NativeNodeUtils.h"

#ifndef __FF_CATCHCVEXCEPTIONWORKER_H__
#define __FF_CATCHCVEXCEPTIONWORKER_H__

// TODO remove this one
namespace FF {

class SimpleWorkerBase : public ISyncWorker, public IAsyncWorker {
public:
  virtual bool unwrapRequiredArgs(const Napi::CallbackInfo& info) = 0;
  virtual bool unwrapOptionalArgs(const Napi::CallbackInfo& info) = 0;
  virtual bool unwrapOptionalArgsFromOpts(const Napi::CallbackInfo& info) = 0;
  virtual bool hasOptArgsObject(const Napi::CallbackInfo& info) = 0;

  std::string execute() {
    return "";
  }

  Napi::Value getReturnValue() {
    return Nan::Undefined();
  }

  Napi::Value getReturnValue(const Napi::CallbackInfo& info) {
    return getReturnValue();
  }

  bool applyUnwrappers(const Napi::CallbackInfo& info) {
    return unwrapRequiredArgs(info)
           || (!hasOptArgsObject(info) && unwrapOptionalArgs(info))
           || (hasOptArgsObject(info) && unwrapOptionalArgsFromOpts(info));
  }
};

class SimpleWorker : public SimpleWorkerBase {
  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return false;
  }

  bool hasOptArgsObject(const Napi::CallbackInfo& info) {
    return false;
  }

  bool unwrapOptionalArgsFromOpts(const Napi::CallbackInfo& info) {
    return false;
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return false;
  }
};

} // namespace FF

struct CatchCvExceptionWorker : public FF::SimpleWorker {
public:
  std::string execute() {
    try {
      return executeCatchCvExceptionWorker();
    } catch (std::exception& e) {
      return std::string(e.what());
    }
  }

  virtual std::string executeCatchCvExceptionWorker() = 0;
};

#endif