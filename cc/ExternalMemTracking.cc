#include "ExternalMemTracking.h"
#include <iostream>

#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
CustomMatAllocator* ExternalMemTracking::custommatallocator = NULL;
#endif

Napi::Object ExternalMemTracking(Napi::Env env, Napi::Object exports) {
#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
  try {
    char* env = std::getenv("OPENCV4NODEJS_DISABLE_EXTERNAL_MEM_TRACKING");
    if (env == NULL && custommatallocator == NULL) {
      custommatallocator = new CustomMatAllocator();
      cv::Mat::setDefaultAllocator(custommatallocator);
    }
  } catch (...) {
    printf("ExternalMemTracking::Init - fatal exception while trying to read env: OPENCV4NODEJS_DISABLE_EXTERNAL_MEM_TRACKING");
  }
#endif
    exports.Set("isCustomMatAllocatorEnabled", Napi::Function::New(env, ExternalMemTracking::IsCustomMatAllocatorEnabled));
    exports.Set("dangerousEnableCustomMatAllocator", Napi::Function::New(env, ExternalMemTracking::DangerousEnableCustomMatAllocator));
    exports.Set("dangerousDisableCustomMatAllocator", Napi::Function::New(env, ExternalMemTracking::DangerousDisableCustomMatAllocator));
    exports.Set("getMemMetrics", Napi::Function::New(env, ExternalMemTracking::GetMemMetrics));
};

void ExternalMemTracking::GetMemMetrics(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int64_t TotalAlloc = -1;
  int64_t TotalKnownByJS = -1;
  int64_t NumAllocations = -1;
  int64_t NumDeAllocations = -1;

#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
  if (ExternalMemTracking::custommatallocator != NULL) {
    TotalAlloc = ExternalMemTracking::custommatallocator->readtotalmem();
    TotalKnownByJS = ExternalMemTracking::custommatallocator->readmeminformed();
    NumAllocations = ExternalMemTracking::custommatallocator->readnumallocated();
    NumDeAllocations = ExternalMemTracking::custommatallocator->readnumdeallocated();
  }
#endif

  Napi::Object result = Napi::Object::New(env);
  result.Set("TotalAlloc", Napi::Number::New(env, static_cast<double>(TotalAlloc)));
  result.Set("TotalKnownByJS", Napi::Number::New(env, static_cast<double>(TotalKnownByJS)));
  result.Set("NumAllocations", Napi::Number::New(env, static_cast<double>(NumAllocations)));
  result.Set("NumDeAllocations", Napi::Number::New(env, static_cast<double>(NumDeAllocations)));

  info.GetReturnValue().Set(result);
  return;
}

void ExternalMemTracking::IsCustomMatAllocatorEnabled(const Napi::CallbackInfo& info) {
  bool allocatorOn = false;
#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
  if (ExternalMemTracking::custommatallocator != NULL) {
    allocatorOn = true;
  }
#endif
  info.GetReturnValue().Set(allocatorOn);
}

void ExternalMemTracking::DangerousEnableCustomMatAllocator(const Napi::CallbackInfo& info) {
  bool success = false;
#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
  if (ExternalMemTracking::custommatallocator == NULL) {
    ExternalMemTracking::custommatallocator = new CustomMatAllocator();
    cv::Mat::setDefaultAllocator(ExternalMemTracking::custommatallocator);
  }
  success = ExternalMemTracking::custommatallocator != NULL;
#endif
  info.GetReturnValue().Set(success);
}

void ExternalMemTracking::DangerousDisableCustomMatAllocator(const Napi::CallbackInfo& info) {
  bool success = false;
#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
  if (ExternalMemTracking::custommatallocator != NULL) {
    CustomMatAllocator* allocator = ExternalMemTracking::custommatallocator;

    // return default allocator
    if (allocator->variables) {
      allocator->variables->MemTotalChangeMutex.lock();
    }
    cv::Mat::setDefaultAllocator(NULL);
    ExternalMemTracking::custommatallocator = NULL;
    if (allocator->variables) {
      allocator->variables->MemTotalChangeMutex.unlock();
    }

    // sorry, can't delete it, since it may be references by a number of outstanding Mats -> memory leak, but it's small
    // and should not happen often, or ever!.
    // delete allocator;
  }
  success = ExternalMemTracking::custommatallocator == NULL;
#endif
  info.GetReturnValue().Set(success);
}
