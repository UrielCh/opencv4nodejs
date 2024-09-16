#include "CatchCvExceptionWorker.h"
#include "DescriptorMatch.h"
#include "KeyPoint.h"
#include "Mat.h"
#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

#ifndef __FF_DESCRIPTORMATCHING_H__
#define __FF_DESCRIPTORMATCHING_H__

class DescriptorMatching : public Napi::ObjectWrap<DescriptorMatching> {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static Napi::Value MatchFlannBased(const Napi::CallbackInfo& info);
  static Napi::Value MatchBruteForce(const Napi::CallbackInfo& info);
  static Napi::Value MatchBruteForceL1(const Napi::CallbackInfo& info);
  static Napi::Value MatchBruteForceHamming(const Napi::CallbackInfo& info);
  static Napi::Value MatchBruteForceHammingLut(const Napi::CallbackInfo& info);
  static Napi::Value MatchBruteForceSL2(const Napi::CallbackInfo& info);
  static Napi::Value MatchFlannBasedAsync(const Napi::CallbackInfo& info);
  static Napi::Value MatchBruteForceAsync(const Napi::CallbackInfo& info);
  static Napi::Value MatchBruteForceL1Async(const Napi::CallbackInfo& info);
  static Napi::Value MatchBruteForceHammingAsync(const Napi::CallbackInfo& info);
  static Napi::Value MatchBruteForceHammingLutAsync(const Napi::CallbackInfo& info);
  static Napi::Value MatchBruteForceSL2Async(const Napi::CallbackInfo& info);

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  static Napi::Value match(const Napi::CallbackInfo& info, cv::DescriptorMatcher::MatcherType matcherType);
  static Napi::Value matchAsync(const Napi::CallbackInfo& info, cv::DescriptorMatcher::MatcherType matcherType);
#elif CV_VERSION_GREATER_EQUAL(3, 2, 0)
  static Napi::Value match(const Napi::CallbackInfo& info, int matcherType);
  static Napi::Value matchAsync(const Napi::CallbackInfo& info, int matcherType);
#else
  static Napi::Value match(const Napi::CallbackInfo& info, std::string matcherType);
  static Napi::Value matchAsync(const Napi::CallbackInfo& info, std::string matcherType);
#endif

  struct MatchWorker;
};

#endif