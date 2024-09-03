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

  void OnOK() override {
    Napi::Env env = Env(); // get env from AsyncWorker::Env()
    Napi::HandleScope scope(env);
    Napi::Value argv[] = {env.Null(), worker->getReturnValue()};
    Callback().Call({argv[0], argv[1]});
  }

  void OnError(const Napi::Error& e) override {
    Napi::Env env = Env(); // get env from AsyncWorker::Env()
    Napi::HandleScope scope(env);
    Napi::Value argv[] = {e.Value(), env.Null()};
    Callback().Call({argv[0], argv[1]});
  }
};

} // namespace FF

#endif
