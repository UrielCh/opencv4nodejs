#include "IWorker.h"
#include "TryCatch.h"
#include "utils.h"

#ifndef __FF_BINDING_H__
#define __FF_BINDING_H__

namespace FF {
static inline Napi::Value executeSyncBinding(std::shared_ptr<ISyncWorker> worker, std::string methodName, const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  // Remove the redundant Napi::HandleScope

  try {
    if (worker->applyUnwrappers(info)) {
      Napi::Error::New(env, "Error in applyUnwrappers").ThrowAsJavaScriptException();
      return env.Null();
    }

    std::string err = worker->execute();
    if (!err.empty()) {
      Napi::Error::New(env, err).ThrowAsJavaScriptException();
      return env.Null();
    }

    return worker->getReturnValue(info);
  } catch (const std::exception& e) {
    Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
    return env.Null();
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

  class AsyncWorker : public Napi::AsyncWorker {
  public:
    AsyncWorker(Napi::Function& callback, std::shared_ptr<IAsyncWorker> worker)
        : Napi::AsyncWorker(callback), worker(worker) {
    }

    void Execute() override {
      std::string err = worker->execute();
      if (!err.empty()) {
        SetError(err);
      }
    }

    void OnOK() override {
      Napi::HandleScope scope(Env());
      Callback().Call({Env().Null(), worker->getReturnValue(Env())});
    }

    void OnError(const Napi::Error& e) override {
      Napi::HandleScope scope(Env());
      Callback().Call({e.Value(), Env().Null()});
    }

  private:
    std::shared_ptr<IAsyncWorker> worker;
  };

  auto asyncWorker = new AsyncWorker(callback, worker);
  asyncWorker->Queue();
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
