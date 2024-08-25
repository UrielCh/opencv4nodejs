#include "CatchCvExceptionWorker.h"
#include "DescriptorMatch.h"
#include "KeyPoint.h"
#include "Mat.h"
#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

#ifndef __FF_DESCRIPTORMATCHING_H__
#define __FF_DESCRIPTORMATCHING_H__

class DescriptorMatching : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);

  static NAN_METHOD(MatchFlannBased);
  static NAN_METHOD(MatchBruteForce);
  static NAN_METHOD(MatchBruteForceL1);
  static NAN_METHOD(MatchBruteForceHamming);
  static NAN_METHOD(MatchBruteForceHammingLut);
  static NAN_METHOD(MatchBruteForceSL2);
  static NAN_METHOD(MatchFlannBasedAsync);
  static NAN_METHOD(MatchBruteForceAsync);
  static NAN_METHOD(MatchBruteForceL1Async);
  static NAN_METHOD(MatchBruteForceHammingAsync);
  static NAN_METHOD(MatchBruteForceHammingLutAsync);
  static NAN_METHOD(MatchBruteForceSL2Async);

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  static void match(const Napi::CallbackInfo& info, cv::DescriptorMatcher::MatcherType matcherType);
  static void matchAsync(const Napi::CallbackInfo& info, cv::DescriptorMatcher::MatcherType matcherType);
#elif CV_VERSION_GREATER_EQUAL(3, 2, 0)
  static void match(const Napi::CallbackInfo& info, int matcherType);
  static void matchAsync(const Napi::CallbackInfo& info, int matcherType);
#else
  static void match(const Napi::CallbackInfo& info, std::string matcherType);
  static void matchAsync(const Napi::CallbackInfo& info, std::string matcherType);
#endif

  struct MatchWorker;
};

#endif