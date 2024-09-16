#include "opencv_modules.h"

#ifdef HAVE_OPENCV_ML

#include "machinelearningConstants.h"

using namespace cv;

void MachineLearningConstants::Init(Napi::Env env, Napi::Object exports) {
  Napi::Object svmConstants = Napi::Object::New(env);

  FF_SET_JS_PROP(svmConstants, CUSTOM, Napi::Number::New(env, ml::SVM::KernelTypes::CUSTOM));
  FF_SET_JS_PROP(svmConstants, LINEAR, Napi::Number::New(env, ml::SVM::KernelTypes::LINEAR));
  FF_SET_JS_PROP(svmConstants, POLY, Napi::Number::New(env, ml::SVM::KernelTypes::POLY));
  FF_SET_JS_PROP(svmConstants, RBF, Napi::Number::New(env, ml::SVM::KernelTypes::RBF));
  FF_SET_JS_PROP(svmConstants, SIGMOID, Napi::Number::New(env, ml::SVM::KernelTypes::SIGMOID));
  FF_SET_JS_PROP(svmConstants, CHI2, Napi::Number::New(env, ml::SVM::KernelTypes::CHI2));
  FF_SET_JS_PROP(svmConstants, INTER, Napi::Number::New(env, ml::SVM::KernelTypes::INTER));

  FF_SET_JS_PROP(svmConstants, C, Napi::Number::New(env, ml::SVM::ParamTypes::C));
  FF_SET_JS_PROP(svmConstants, COEF, Napi::Number::New(env, ml::SVM::ParamTypes::COEF));
  FF_SET_JS_PROP(svmConstants, DEGREE, Napi::Number::New(env, ml::SVM::ParamTypes::DEGREE));
  FF_SET_JS_PROP(svmConstants, GAMMA, Napi::Number::New(env, ml::SVM::ParamTypes::GAMMA));
  FF_SET_JS_PROP(svmConstants, NU, Napi::Number::New(env, ml::SVM::ParamTypes::NU));
  FF_SET_JS_PROP(svmConstants, P, Napi::Number::New(env, ml::SVM::ParamTypes::P));

  Napi::Object mlConstants = Napi::Object::New(env);
  FF_SET_JS_PROP(mlConstants, COL_SAMPLE, Napi::Number::New(env, ml::SampleTypes::COL_SAMPLE));
  FF_SET_JS_PROP(mlConstants, ROW_SAMPLE, Napi::Number::New(env, ml::SampleTypes::ROW_SAMPLE));

  FF_SET_JS_PROP(mlConstants, VAR_CATEGORICAL, Napi::Number::New(env, ml::VariableTypes::VAR_CATEGORICAL));
  FF_SET_JS_PROP(mlConstants, VAR_NUMERICAL, Napi::Number::New(env, ml::VariableTypes::VAR_NUMERICAL));
  FF_SET_JS_PROP(mlConstants, VAR_ORDERED, Napi::Number::New(env, ml::VariableTypes::VAR_ORDERED));
  mlConstants.Set("SVM", svmConstants);
  exports.Set("ml", mlConstants);

  Napi::Object statModelCostants = Napi::Object::New(env);
  FF_SET_JS_PROP(statModelCostants, COMPRESSED_INPUT, Napi::Number::New(env, ml::StatModel::Flags::COMPRESSED_INPUT));
  FF_SET_JS_PROP(statModelCostants, PREPROCESSED_INPUT, Napi::Number::New(env, ml::StatModel::Flags::PREPROCESSED_INPUT));
  FF_SET_JS_PROP(statModelCostants, RAW_OUTPUT, Napi::Number::New(env, ml::StatModel::Flags::RAW_OUTPUT));
  FF_SET_JS_PROP(statModelCostants, UPDATE_MODEL, Napi::Number::New(env, ml::StatModel::Flags::UPDATE_MODEL));
  exports.Set("statModel", statModelCostants);
}

#endif
