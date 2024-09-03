#include "macros.h"
#include <opencv2/ml.hpp>

#ifndef __FF_MACHINE_LEARNING_CONSTANTS_H__
#define __FF_MACHINE_LEARNING_CONSTANTS_H__

class MachineLearningConstants {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
};

#endif