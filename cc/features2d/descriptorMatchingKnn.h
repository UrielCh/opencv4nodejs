#include "CatchCvExceptionWorker.h"
#include "DescriptorMatch.h"
#include "KeyPoint.h"
#include "Mat.h"
#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

#ifndef __FF_DESCRIPTORMATCHINGKNN_H__
#define __FF_DESCRIPTORMATCHINGKNN_H__

class DescriptorMatchingKnn : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);

  static NAN_METHOD(MatchKnnFlannBased);
  static NAN_METHOD(MatchKnnBruteForce);
  static NAN_METHOD(MatchKnnBruteForceL1);
  static NAN_METHOD(MatchKnnBruteForceHamming);
  static NAN_METHOD(MatchKnnBruteForceHammingLut);
  static NAN_METHOD(MatchKnnBruteForceSL2);
  static NAN_METHOD(MatchKnnFlannBasedAsync);
  static NAN_METHOD(MatchKnnBruteForceAsync);
  static NAN_METHOD(MatchKnnBruteForceL1Async);
  static NAN_METHOD(MatchKnnBruteForceHammingAsync);
  static NAN_METHOD(MatchKnnBruteForceHammingLutAsync);
  static NAN_METHOD(MatchKnnBruteForceSL2Async);

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  static void matchKnn(const Napi::CallbackInfo& info, cv::DescriptorMatcher::MatcherType matcherType);
  static void matchKnnAsync(const Napi::CallbackInfo& info, cv::DescriptorMatcher::MatcherType matcherType);
#elif CV_VERSION_GREATER_EQUAL(3, 2, 0)
  static void matchKnn(const Napi::CallbackInfo& info, int matcherType);
  static void matchKnnAsync(const Napi::CallbackInfo& info, int matcherType);
#else
  static void matchKnn(const Napi::CallbackInfo& info, std::string matcherType);
  static void matchKnnAsync(const Napi::CallbackInfo& info, std::string matcherType);
#endif

  struct MatchKnnWorker;
};

#endif