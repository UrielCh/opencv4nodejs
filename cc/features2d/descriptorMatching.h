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

  static void MatchFlannBased(const Napi::CallbackInfo& info);
  static void MatchBruteForce(const Napi::CallbackInfo& info);
  static void MatchBruteForceL1(const Napi::CallbackInfo& info);
  static void MatchBruteForceHamming(const Napi::CallbackInfo& info);
  static void MatchBruteForceHammingLut(const Napi::CallbackInfo& info);
  static void MatchBruteForceSL2(const Napi::CallbackInfo& info);
  static void MatchFlannBasedAsync(const Napi::CallbackInfo& info);
  static void MatchBruteForceAsync(const Napi::CallbackInfo& info);
  static void MatchBruteForceL1Async(const Napi::CallbackInfo& info);
  static void MatchBruteForceHammingAsync(const Napi::CallbackInfo& info);
  static void MatchBruteForceHammingLutAsync(const Napi::CallbackInfo& info);
  static void MatchBruteForceSL2Async(const Napi::CallbackInfo& info);

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