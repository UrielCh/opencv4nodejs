#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_MATUTILS_H__
#define __FF_MATUTILS_H__

namespace FF {
/**
 * 2,3-Dimmentions Macro seters for a single Value
 */
template <typename type>
static inline void matPutVal(cv::Mat mat, Napi::Value value, int r, int c) {
  mat.at<type>(r, c) = (type)value->ToNumber(Napi::GetCurrentContext())->Value();
}

template <typename type>
static inline void matPutVal(cv::Mat mat, Napi::Value value, int r, int c, int z) {
  mat.at<type>(r, c, z) = (type)value->ToNumber(Napi::GetCurrentContext())->Value();
}

/**
 * 2,3-Dimmentions Macro seters for a Vec<2> Value
 */
template <typename type>
static inline void matPutVec2(cv::Mat mat, Napi::Value vector, int r, int c) {
  Napi::Array vec = vector.As<Napi::Array>();
  mat.at<cv::Vec<type, 2>>(r, c) = cv::Vec<type, 2>(
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(0)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(1)));
}

template <typename type>
static inline void matPutVec2(cv::Mat mat, Napi::Value vector, int r, int c, int z) {
  Napi::Array vec = vector.As<Napi::Array>();
  mat.at<cv::Vec<type, 2>>(r, c, z) = cv::Vec<type, 2>(
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(0)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(1)));
}

/**
 * 2,3-Dimmentions Macro seters for a Vec<3> Value
 */
template <typename type>
static inline void matPutVec3(cv::Mat mat, Napi::Value vector, int r, int c) {
  Napi::Array vec = vector.As<Napi::Array>();
  mat.at<cv::Vec<type, 3>>(r, c) = cv::Vec<type, 3>(
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(0)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(1)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(2)));
}

template <typename type>
static inline void matPutVec3(cv::Mat mat, Napi::Value vector, int r, int c, int z) {
  Napi::Array vec = vector.As<Napi::Array>();
  mat.at<cv::Vec<type, 3>>(r, c, z) = cv::Vec<type, 3>(
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(0)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(1)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(2)));
}

/**
 * 2,3-Dimmentions Macro seters for a Vec<4> Value
 */
template <typename type>
static inline void matPutVec4(cv::Mat mat, Napi::Value vector, int r, int c) {
  Napi::Array vec = vector.As<Napi::Array>();
  mat.at<cv::Vec<type, 4>>(r, c) = cv::Vec<type, 4>(
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(0)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(1)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(2)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(3)));
}

template <typename type>
static inline void matPutVec4(cv::Mat mat, Napi::Value vector, int r, int c, int z) {
  Napi::Array vec = vector.As<Napi::Array>();
  mat.at<cv::Vec<type, 4>>(r, c, z) = cv::Vec<type, 4>(
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(0)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(1)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(2)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(3)));
}

/**
 * 2,3,n-Dimmentions Macro getters for single Value
 */
template <typename type>
static inline Napi::Value matGetVal(cv::Mat mat, int r, int c) {
  return Napi::New(env, mat.at<type>(r, c));
}

template <typename type>
static inline Napi::Value matGetVal(cv::Mat mat, int r, int c, int z) {
  return Napi::New(env, mat.at<type>(r, c, z));
}

template <typename type>
static inline Napi::Value matGetVal(cv::Mat mat, const int* idx) {
  return Napi::New(env, mat.at<type>(idx));
}

/**
 * 2,3,n-Dimmentions Macro getters for Vec<2> Value
 */
template <typename type>
static inline Napi::Value matGetVec2(cv::Mat mat, int r, int c) {
  Napi::Array vec = Napi::Array::New(env, 2);
  (vec).Set(0, Napi::New(env, mat.at<cv::Vec<type, 2>>(r, c)[0]));
  (vec).Set(1, Napi::New(env, mat.at<cv::Vec<type, 2>>(r, c)[1]));
  return vec;
}

template <typename type>
static inline Napi::Value matGetVec2(cv::Mat mat, int r, int c, int z) {
  Napi::Array vec = Napi::Array::New(env, 2);
  (vec).Set(0, Napi::New(env, mat.at<cv::Vec<type, 2>>(r, c, z)[0]));
  (vec).Set(1, Napi::New(env, mat.at<cv::Vec<type, 2>>(r, c, z)[1]));
  return vec;
}

template <typename type>
static inline Napi::Value matGetVec2(cv::Mat mat, const int* idx) {
  Napi::Array vec = Napi::Array::New(env, 2);
  (vec).Set(0, Napi::New(env, mat.at<cv::Vec<type, 2>>(idx)[0]));
  (vec).Set(1, Napi::New(env, mat.at<cv::Vec<type, 2>>(idx)[1]));
  return vec;
}

/**
 * 2,3,n-Dimmentions Macro getters for Vec<3> Value
 */
template <typename type>
static inline Napi::Value matGetVec3(cv::Mat mat, int r, int c) {
  Napi::Array vec = Napi::Array::New(env, 3);
  (vec).Set(0, Napi::New(env, mat.at<cv::Vec<type, 3>>(r, c)[0]));
  (vec).Set(1, Napi::New(env, mat.at<cv::Vec<type, 3>>(r, c)[1]));
  (vec).Set(2, Napi::New(env, mat.at<cv::Vec<type, 3>>(r, c)[2]));
  return vec;
}

template <typename type>
static inline Napi::Value matGetVec3(cv::Mat mat, int r, int c, int z) {
  Napi::Array vec = Napi::Array::New(env, 3);
  (vec).Set(0, Napi::New(env, mat.at<cv::Vec<type, 3>>(r, c, z)[0]));
  (vec).Set(1, Napi::New(env, mat.at<cv::Vec<type, 3>>(r, c, z)[1]));
  (vec).Set(2, Napi::New(env, mat.at<cv::Vec<type, 3>>(r, c, z)[2]));
  return vec;
}

template <typename type>
static inline Napi::Value matGetVec3(cv::Mat mat, const int* idx) {
  Napi::Array vec = Napi::Array::New(env, 3);
  (vec).Set(0, Napi::New(env, mat.at<cv::Vec<type, 3>>(idx)[0]));
  (vec).Set(1, Napi::New(env, mat.at<cv::Vec<type, 3>>(idx)[1]));
  (vec).Set(2, Napi::New(env, mat.at<cv::Vec<type, 3>>(idx)[2]));
  return vec;
}

/**
 * 2,3,n-Dimmentions Macro getters for Vec<4> Value
 */
template <typename type>
static inline Napi::Value matGetVec4(cv::Mat mat, int r, int c) {
  Napi::Array vec = Napi::Array::New(env, 4);
  (vec).Set(0, Napi::New(env, mat.at<cv::Vec<type, 4>>(r, c)[0]));
  (vec).Set(1, Napi::New(env, mat.at<cv::Vec<type, 4>>(r, c)[1]));
  (vec).Set(2, Napi::New(env, mat.at<cv::Vec<type, 4>>(r, c)[2]));
  (vec).Set(3, Napi::New(env, mat.at<cv::Vec<type, 4>>(r, c)[3]));
  return vec;
}

template <typename type>
static inline Napi::Value matGetVec4(cv::Mat mat, int r, int c, int z) {
  Napi::Array vec = Napi::Array::New(env, 4);
  (vec).Set(0, Napi::New(env, mat.at<cv::Vec<type, 4>>(r, c, z)[0]));
  (vec).Set(1, Napi::New(env, mat.at<cv::Vec<type, 4>>(r, c, z)[1]));
  (vec).Set(2, Napi::New(env, mat.at<cv::Vec<type, 4>>(r, c, z)[2]));
  (vec).Set(3, Napi::New(env, mat.at<cv::Vec<type, 4>>(r, c, z)[3]));
  return vec;
}

template <typename type>
static inline Napi::Value matGetVec4(cv::Mat mat, const int* idx) {
  Napi::Array vec = Napi::Array::New(env, 4);
  (vec).Set(0, Napi::New(env, mat.at<cv::Vec<type, 4>>(idx)[0]));
  (vec).Set(1, Napi::New(env, mat.at<cv::Vec<type, 4>>(idx)[1]));
  (vec).Set(2, Napi::New(env, mat.at<cv::Vec<type, 4>>(idx)[2]));
  (vec).Set(3, Napi::New(env, mat.at<cv::Vec<type, 4>>(idx)[3]));
  return vec;
}
} // namespace FF

#endif
