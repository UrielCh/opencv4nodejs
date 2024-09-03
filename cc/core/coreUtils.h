#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_COREUTILS_H__
#define __FF_COREUTILS_H__

#define FF_ASSERT_INDEX_RANGE(idx, max, what)                                                                     \
  if (idx < 0 || max < idx) {                                                                                     \
    return tryCatch.throwError("Index out of bounds: " + std::string(what) + " at index " + std::to_string(idx)); \
  }

#define FF_APPLY_FUNC(func, arg0, arg1, ret) func(arg0, arg1, ret);
#define FF_APPLY_CLASS_FUNC(func, arg0, arg1, ret) ret = ((arg0).*(func))(arg1);
#define FF_APPLY_OPERATOR(op, arg0, arg1, ret) ret = arg0 op arg1;

/* TODO fix non scalar matrix multiplication, division */

#define FF_SELF_OPERATOR(func)                                       \
  Napi::Object jsObj = FF::newInstance(Napi::New(env, constructor)); \
  func(unwrapSelf(info), unwrapClassPtrUnchecked(jsObj)->self);      \
  return return jsObj;

#define FF_SCALAR_OPERATOR(func, applyFunc, clazz, methodName)       \
  FF::TryCatch tryCatch(methodName);                                 \
  if (!info[0].IsNumber()) {                                         \
    return tryCatch.throwError("expected arg to be a Scalar");       \
  }                                                                  \
  Napi::Object jsObj = FF::newInstance(Napi::New(env, constructor)); \
  applyFunc(                                                         \
      func,                                                          \
      unwrapSelf(info),                                              \
      info[0].ToNumber(Napi::GetCurrentContext())->Value(),          \
      unwrapClassPtrUnchecked(jsObj)->self);                         \
  return return jsObj;

#define FF_OPERATOR(func, applyFunc, clazz, methodName)                                     \
  FF::TryCatch tryCatch(methodName);                                                        \
  if (!Napi::New(env, constructor)->HasInstance(info[0])) {                                 \
    return tryCatch.throwError("expected arg to be an instance of " + std::string(#clazz)); \
  }                                                                                         \
  Napi::Object jsObj = FF::newInstance(Napi::New(env, constructor));                        \
  applyFunc(                                                                                \
      func,                                                                                 \
      unwrapSelf(info),                                                                     \
      unwrapClassPtrUnchecked(info[0].ToObject(Napi::GetCurrentContext()))->self,           \
      unwrapClassPtrUnchecked(jsObj)->self);                                                \
  return return jsObj;

#define FF_OPERATOR_RET_SCALAR(func, applyFunc, clazz, methodName)                          \
  FF::TryCatch tryCatch(methodName);                                                        \
  if (!Napi::New(env, constructor)->HasInstance(info[0])) {                                 \
    return tryCatch.throwError("expected arg to be an instance of " + std::string(#clazz)); \
  }                                                                                         \
  double ret;                                                                               \
  applyFunc(                                                                                \
      func,                                                                                 \
      unwrapSelf(info),                                                                     \
      unwrapClassPtrUnchecked(info[0].ToObject(Napi::GetCurrentContext()))->self,           \
      ret);                                                                                 \
  return return ret;

#define FF_PROTO_SET_ARITHMETIC_OPERATIONS(ctor) \
  InstanceMethod("add", &Add),                   \
      InstanceMethod("sub", &Sub),               \
      InstanceMethod("mul", &Mul),               \
      InstanceMethod("div", &Div),

#define FF_PROTO_SET_MATRIX_OPERATIONS(ctor) \
  FF_PROTO_SET_ARITHMETIC_OPERATIONS(ctor)   \
  InstanceMethod("hMul", &HMul),             \
      InstanceMethod("hDiv", &HDiv),         \
      InstanceMethod("absdiff", &Absdiff),   \
      InstanceMethod("exp", &Exp),           \
      InstanceMethod("log", &Log),           \
      InstanceMethod("sqrt", &Sqrt),         \
      InstanceMethod("dot", &Dot),

#define FF_PROTO_SET_MAT_OPERATIONS(ctor)          \
  FF_PROTO_SET_MATRIX_OPERATIONS(ctor)             \
  InstanceMethod("and", &And),                     \
      InstanceMethod("or", &Or),                   \
      InstanceMethod("bitwiseAnd", &BitwiseAnd),   \
      InstanceMethod("bitwiseNot", &BitwiseNot),   \
      InstanceMethod("bitwiseOr", &BitwiseOr),     \
      InstanceMethod("bitwiseXor", &BitwiseXor),   \
      InstanceMethod("abs", &Abs),                 \
      InstanceMethod("transpose", &Transpose),     \
      InstanceMethod("inv", &Inv),                 \
      InstanceMethod("determinant", &Determinant), \
      InstanceMethod("matMul", &MatMul),

#define FF_INIT_ARITHMETIC_OPERATIONS(clazz)                \
  static Napi::Value Add(const Napi::CallbackInfo& info) {  \
    FF_OPERATOR(+, FF_APPLY_OPERATOR, clazz, "Add");        \
  }                                                         \
  static Napi::Value Sub(const Napi::CallbackInfo& info) {  \
    FF_OPERATOR(-, FF_APPLY_OPERATOR, clazz, "Sub");        \
  }                                                         \
  static Napi::Value Mul(const Napi::CallbackInfo& info) {  \
    FF_SCALAR_OPERATOR(*, FF_APPLY_OPERATOR, clazz, "Mul"); \
  }                                                         \
  static Napi::Value Div(const Napi::CallbackInfo& info) {  \
    FF_SCALAR_OPERATOR(/, FF_APPLY_OPERATOR, clazz, "Div"); \
  }

#define FF_INIT_MATRIX_OPERATIONS(clazz)                       \
  FF_INIT_ARITHMETIC_OPERATIONS(clazz)                         \
  static Napi::Value HMul(const Napi::CallbackInfo& info) {    \
    FF_OPERATOR(cv::multiply, FF_APPLY_FUNC, clazz, "HMul");   \
  }                                                            \
  static Napi::Value HDiv(const Napi::CallbackInfo& info) {    \
    FF_OPERATOR(cv::divide, FF_APPLY_FUNC, clazz, "HDiv");     \
  }                                                            \
  static Napi::Value Absdiff(const Napi::CallbackInfo& info) { \
    FF_OPERATOR(cv::absdiff, FF_APPLY_FUNC, clazz, "Absdiff"); \
  }                                                            \
  static Napi::Value Exp(const Napi::CallbackInfo& info) {     \
    FF_SELF_OPERATOR(cv::exp);                                 \
  }                                                            \
  static Napi::Value Log(const Napi::CallbackInfo& info) {     \
    FF_SELF_OPERATOR(cv::log);                                 \
  }                                                            \
  static Napi::Value Sqrt(const Napi::CallbackInfo& info) {    \
    FF_SELF_OPERATOR(cv::sqrt);                                \
  }

#define FF_INIT_MAT_OPERATIONS()                                    \
  FF_INIT_MATRIX_OPERATIONS(Mat);                                   \
  static Napi::Value And(const Napi::CallbackInfo& info) {          \
    FF_OPERATOR(&, FF_APPLY_OPERATOR, Mat, "And");                  \
  }                                                                 \
  static Napi::Value Or(const Napi::CallbackInfo& info) {           \
    FF_OPERATOR(|, FF_APPLY_OPERATOR, Mat, "Or");                   \
  }                                                                 \
  static Napi::Value BitwiseAnd(const Napi::CallbackInfo& info) {   \
    FF_OPERATOR(cv::bitwise_and, FF_APPLY_FUNC, Mat, "BitwiseAnd"); \
  }                                                                 \
  static Napi::Value BitwiseNot(const Napi::CallbackInfo& info) {   \
    FF_SELF_OPERATOR(cv::bitwise_not);                              \
  }                                                                 \
  static Napi::Value BitwiseOr(const Napi::CallbackInfo& info) {    \
    FF_OPERATOR(cv::bitwise_or, FF_APPLY_FUNC, Mat, "BitwiseOr");   \
  }                                                                 \
  static Napi::Value BitwiseXor(const Napi::CallbackInfo& info) {   \
    FF_OPERATOR(cv::bitwise_xor, FF_APPLY_FUNC, Mat, "BitwiseXor"); \
  }                                                                 \
  static Napi::Value Abs(const Napi::CallbackInfo& info) {          \
    return return Converter::wrap(cv::abs(unwrapSelf(info)));       \
  }                                                                 \
  static Napi::Value Determinant(const Napi::CallbackInfo& info) {  \
    return return cv::determinant(Mat::unwrapSelf(info));           \
  }                                                                 \
  static Napi::Value Transpose(const Napi::CallbackInfo& info) {    \
    FF_SELF_OPERATOR(cv::transpose);                                \
  }                                                                 \
  static Napi::Value Inv(const Napi::CallbackInfo& info) {          \
    FF_SELF_OPERATOR(cv::invert);                                   \
  }                                                                 \
  static Napi::Value MatMul(const Napi::CallbackInfo& info) {       \
    FF_OPERATOR(*, FF_APPLY_OPERATOR, Mat, "MatMul");               \
  }

#define FF_INIT_VEC2_OPERATIONS() FF_INIT_MATRIX_OPERATIONS(Vec2);
#define FF_INIT_VEC3_OPERATIONS() FF_INIT_MATRIX_OPERATIONS(Vec3);
#define FF_INIT_VEC4_OPERATIONS() FF_INIT_MATRIX_OPERATIONS(Vec4);
#define FF_INIT_VEC6_OPERATIONS() FF_INIT_MATRIX_OPERATIONS(Vec6);

namespace FF {
template <int cn>
static Napi::Array vecToJsArr(cv::Vec<double, cn> vec) {
  Napi::Array jsVec = Napi::Array::New(env, cn);
  for (int i = 0; i < cn; i++)
    (jsVec).Set(i, Napi::New(env, vec[i]));
  return jsVec;
}
} // namespace FF

#endif