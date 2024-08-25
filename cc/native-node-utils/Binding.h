#include "IWorker.h"
#include "TryCatch.h"
#include "utils.h"

#ifndef __FF_BINDING_H__
#define __FF_BINDING_H__

namespace FF {
static inline void executeSyncBinding(std::shared_ptr<ISyncWorker> worker, std::string methodName, const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  try {
    // if (worker && worker->applyUnwrappers(info)) {
    if (worker->applyUnwrappers(info)) {
      Napi::Error::New(env, "Error in applyUnwrappers").ThrowAsJavaScriptException();
      return;
    }

    std::string err = worker->execute();
    if (!err.empty()) {
      Napi::Error::New(env, err).ThrowAsJavaScriptException();
      return;
    }

    info.GetReturnValue().Set(worker->getReturnValue(info));
    // info.ReturnValue().Set(worker->getReturnValue(info));
  } catch (const std::exception& e) {
    Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
  }
}

static inline void executeAsyncBinding(std::shared_ptr<IAsyncWorker> worker, std::string methodName, const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (!info[info.Length() - 1].IsFunction()) {
    Napi::TypeError::New(env, "callback function required").ThrowAsJavaScriptException();
    return;
  }

  Napi::Function callback = info[info.Length() - 1].As<Napi::Function>();

  if (worker->applyUnwrappers(info)) {
    Napi::Error error = Napi::Error::New(env, "Error in applyUnwrappers");
    Napi::Value argv[] = {error.Value(), env.Null()};
    callback.Call(env.Global(), argv);
    return;
  }

  auto asyncWorker = new FF::AsyncWorker(callback, worker);
  Napi::AsyncWorker::Queue(asyncWorker);
}

template <class WorkerImpl>
static void syncBinding(std::string methodNamespace, std::string methodName, const Napi::CallbackInfo& info) {
  auto worker = std::make_shared<WorkerImpl>();
  worker->setup();
  executeSyncBinding(
      worker,
      methodNamespace + "::" + methodName,
      info);
}

template <class WorkerImpl>
static void asyncBinding(std::string methodNamespace, std::string methodName, const Napi::CallbackInfo& info) {
  auto worker = std::make_shared<WorkerImpl>();
  worker->setup();
  executeAsyncBinding(
      worker,
      methodNamespace + "::" + methodName + "Async",
      info);
}
} // namespace FF

#endif
