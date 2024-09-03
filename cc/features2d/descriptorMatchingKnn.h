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

  static void MatchKnnFlannBased(const Napi::CallbackInfo& info);
  static void MatchKnnBruteForce(const Napi::CallbackInfo& info);
  static void MatchKnnBruteForceL1(const Napi::CallbackInfo& info);
  static void MatchKnnBruteForceHamming(const Napi::CallbackInfo& info);
  static void MatchKnnBruteForceHammingLut(const Napi::CallbackInfo& info);
  static void MatchKnnBruteForceSL2(const Napi::CallbackInfo& info);
  static void MatchKnnFlannBasedAsync(const Napi::CallbackInfo& info);
  static void MatchKnnBruteForceAsync(const Napi::CallbackInfo& info);
  static void MatchKnnBruteForceL1Async(const Napi::CallbackInfo& info);
  static void MatchKnnBruteForceHammingAsync(const Napi::CallbackInfo& info);
  static void MatchKnnBruteForceHammingLutAsync(const Napi::CallbackInfo& info);
  static void MatchKnnBruteForceSL2Async(const Napi::CallbackInfo& info);

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