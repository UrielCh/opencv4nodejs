#include "opencv_modules.h"

#ifdef HAVE_OPENCV_ML

#include "ParamGrid.h"
#include "SVM.h"
#include "StatModel.h"
#include "TrainData.h"
#include "machinelearning.h"
#include "machinelearningConstants.h"

Napi::Object MachineLearning::Init(Napi::Env env, Napi::Object exports) {
  MachineLearningConstants::Init(env, exports);
  TrainData::Init(env, exports);
  ParamGrid::Init(env, exports);
  StatModel::Init(env, exports);
  SVM::Init(env, exports);
  return exports;
}

NODE_API_MODULE(machinelearning, MachineLearning::Init)

#endif