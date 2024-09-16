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

class DescriptorMatchingKnn : public Napi::ObjectWrap<DescriptorMatchingKnn> {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static Napi::Value MatchKnnFlannBased(const Napi::CallbackInfo& info);
  static Napi::Value MatchKnnBruteForce(const Napi::CallbackInfo& info);
  static Napi::Value MatchKnnBruteForceL1(const Napi::CallbackInfo& info);
  static Napi::Value MatchKnnBruteForceHamming(const Napi::CallbackInfo& info);
  static Napi::Value MatchKnnBruteForceHammingLut(const Napi::CallbackInfo& info);
  static Napi::Value MatchKnnBruteForceSL2(const Napi::CallbackInfo& info);
  static Napi::Value MatchKnnFlannBasedAsync(const Napi::CallbackInfo& info);
  static Napi::Value MatchKnnBruteForceAsync(const Napi::CallbackInfo& info);
  static Napi::Value MatchKnnBruteForceL1Async(const Napi::CallbackInfo& info);
  static Napi::Value MatchKnnBruteForceHammingAsync(const Napi::CallbackInfo& info);
  static Napi::Value MatchKnnBruteForceHammingLutAsync(const Napi::CallbackInfo& info);
  static Napi::Value MatchKnnBruteForceSL2Async(const Napi::CallbackInfo& info);

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  static Napi::Value matchKnn(const Napi::CallbackInfo& info, cv::DescriptorMatcher::MatcherType matcherType);
  static Napi::Value matchKnnAsync(const Napi::CallbackInfo& info, cv::DescriptorMatcher::MatcherType matcherType);
#elif CV_VERSION_GREATER_EQUAL(3, 2, 0)
  static Napi::Value matchKnn(const Napi::CallbackInfo& info, int matcherType);
  static Napi::Value matchKnnAsync(const Napi::CallbackInfo& info, int matcherType);
#else
  static Napi::Value matchKnn(const Napi::CallbackInfo& info, std::string matcherType);
  static Napi::Value matchKnnAsync(const Napi::CallbackInfo& info, std::string matcherType);
#endif

  struct MatchKnnWorker;
};

#endif