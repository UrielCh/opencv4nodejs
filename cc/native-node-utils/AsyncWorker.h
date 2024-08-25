#include <IWorker.h>
#include <memory>
#include <napi.h>

#ifndef __FF_ASYNC_WORKER_H__
#define __FF_ASYNC_WORKER_H__

namespace FF {

class AsyncWorker : public Napi::AsyncWorker {
public:
  std::shared_ptr<IAsyncWorker> worker;

  AsyncWorker(
      Napi::Function& callback,
      std::shared_ptr<IAsyncWorker> worker)
      : Napi::AsyncWorker(callback), worker(worker) {
  }

  ~AsyncWorker() {
  }

  void Execute() override {
    std::string err = worker->execute();
    if (!err.empty()) {
      this->SetError(err);
    }
  }

  void HandleOKCallback() {
    Napi::HandleScope scope(Env());
    Napi::Env env = Env();
    Napi::Value argv[] = {env.Null(), worker->getReturnValue()};
    Callback().Call({argv[0], argv[1]});
  }

  void HandleErrorCallback() {
    Napi::HandleScope scope(Env());
    Napi::Env env = Env();
    Napi::Value argv[] = {Napi::String::New(env, this->ErrorMessage()), env.Null()};
    Callback().Call({argv[0], argv[1]});
  }
};

} // namespace FF

#endif
