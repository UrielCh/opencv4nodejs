// #include "macros.h"
#include <napi.h>
#include <opencv2/core.hpp>

#ifndef __FF_CORE_CONSTANTS_H__
#define __FF_CORE_CONSTANTS_H__

class CoreConstants {
public:
  static void Init(Napi::Object exports);
};

#endif