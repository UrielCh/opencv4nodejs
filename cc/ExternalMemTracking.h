#include "CustomMatAllocator.h"
#include "macros.h"

#ifndef __FF_EXTERNALMEMTRACKING_H__
#define __FF_EXTERNALMEMTRACKING_H__

class ExternalMemTracking {
public:
#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
  static CustomMatAllocator* custommatallocator;
#endif

  static inline void onMatAllocated() {
#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING
    if (custommatallocator != NULL) {
      custommatallocator->FixupJSMem();
    }
#endif
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void IsCustomMatAllocatorEnabled(const Napi::CallbackInfo& info);
  static void GetMemMetrics(const Napi::CallbackInfo& info);
  static void DangerousEnableCustomMatAllocator(const Napi::CallbackInfo& info);
  static void DangerousDisableCustomMatAllocator(const Napi::CallbackInfo& info);
};

#endif