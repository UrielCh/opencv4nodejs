#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "descriptorMatching.h"

Napi::Object DescriptorMatching(Napi::Env env, Napi::Object exports) {
  exports.Set("matchFlannBased", Napi::Function::New(env, DescriptorMatching::MatchFlannBased));
  exports.Set("matchBruteForce", Napi::Function::New(env, DescriptorMatching::MatchBruteForce));
  exports.Set("matchBruteForceL1", Napi::Function::New(env, DescriptorMatching::MatchBruteForceL1));
  exports.Set("matchBruteForceHamming", Napi::Function::New(env, DescriptorMatching::MatchBruteForceHamming));
  exports.Set("matchFlannBasedAsync", Napi::Function::New(env, DescriptorMatching::MatchFlannBasedAsync));
  exports.Set("matchBruteForceAsync", Napi::Function::New(env, DescriptorMatching::MatchBruteForceAsync));
  exports.Set("matchBruteForceL1Async", Napi::Function::New(env, DescriptorMatching::MatchBruteForceL1Async));
  exports.Set("matchBruteForceHammingAsync", Napi::Function::New(env, DescriptorMatching::MatchBruteForceHammingAsync));
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  exports.Set("matchBruteForceHammingLut", Napi::Function::New(env, DescriptorMatching::MatchBruteForceHammingLut));
  exports.Set("matchBruteForceSL2", Napi::Function::New(env, DescriptorMatching::MatchBruteForceSL2));
  exports.Set("matchBruteForceHammingLutAsync", Napi::Function::New(env, DescriptorMatching::MatchBruteForceHammingLutAsync));
  exports.Set("matchBruteForceSL2Async", Napi::Function::New(env, DescriptorMatching::MatchBruteForceSL2Async));
#endif
};

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)

Napi::Value DescriptorMatching::MatchFlannBased(const Napi::CallbackInfo& info) {
  return match(info, cv::DescriptorMatcher::FLANNBASED);
}

Napi::Value DescriptorMatching::MatchBruteForce(const Napi::CallbackInfo& info) {
  return match(info, cv::DescriptorMatcher::BRUTEFORCE);
}

Napi::Value DescriptorMatching::MatchBruteForceL1(const Napi::CallbackInfo& info) {
  return match(info, cv::DescriptorMatcher::BRUTEFORCE_L1);
}

Napi::Value DescriptorMatching::MatchBruteForceHamming(const Napi::CallbackInfo& info) {
  return match(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMING);
}

Napi::Value DescriptorMatching::MatchBruteForceHammingLut(const Napi::CallbackInfo& info) {
  return match(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMINGLUT);
}

Napi::Value DescriptorMatching::MatchBruteForceSL2(const Napi::CallbackInfo& info) {
  return match(info, cv::DescriptorMatcher::BRUTEFORCE_SL2);
}

Napi::Value DescriptorMatching::MatchFlannBasedAsync(const Napi::CallbackInfo& info) {
  return matchAsync(info, cv::DescriptorMatcher::FLANNBASED);
}

Napi::Value DescriptorMatching::MatchBruteForceAsync(const Napi::CallbackInfo& info) {
  return matchAsync(info, cv::DescriptorMatcher::BRUTEFORCE);
}

Napi::Value DescriptorMatching::MatchBruteForceL1Async(const Napi::CallbackInfo& info) {
  return matchAsync(info, cv::DescriptorMatcher::BRUTEFORCE_L1);
}

Napi::Value DescriptorMatching::MatchBruteForceHammingAsync(const Napi::CallbackInfo& info) {
  return matchAsync(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMING);
}

Napi::Value DescriptorMatching::MatchBruteForceHammingLutAsync(const Napi::CallbackInfo& info) {
  return matchAsync(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMINGLUT);
}

Napi::Value DescriptorMatching::MatchBruteForceSL2Async(const Napi::CallbackInfo& info) {
  return matchAsync(info, cv::DescriptorMatcher::BRUTEFORCE_SL2);
}

#else

Napi::Value DescriptorMatching::MatchFlannBased(const Napi::CallbackInfo& info) {
  return match(info, "FlannBased");
}

Napi::Value DescriptorMatching::MatchBruteForce(const Napi::CallbackInfo& info) {
  return match(info, "BruteForce");
}

Napi::Value DescriptorMatching::MatchBruteForceL1(const Napi::CallbackInfo& info) {
  return match(info, "BruteForce-L1");
}

Napi::Value DescriptorMatching::MatchBruteForceHamming(const Napi::CallbackInfo& info) {
  return match(info, "BruteForce-Hamming");
}

Napi::Value DescriptorMatching::MatchFlannBasedAsync(const Napi::CallbackInfo& info) {
  return matchAsync(info, "FlannBased");
}

Napi::Value DescriptorMatching::MatchBruteForceAsync(const Napi::CallbackInfo& info) {
  return matchAsync(info, "BruteForce");
}

Napi::Value DescriptorMatching::MatchBruteForceL1Async(const Napi::CallbackInfo& info) {
  return matchAsync(info, "BruteForce-L1");
}

Napi::Value DescriptorMatching::MatchBruteForceHammingAsync(const Napi::CallbackInfo& info) {
  return matchAsync(info, "BruteForce-Hamming");
}

#endif

struct DescriptorMatching::MatchWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::DescriptorMatcher> matcher;

  MatchWorker(cv::Ptr<cv::DescriptorMatcher> _matcher) {
    this->matcher = _matcher;
  }

  virtual ~MatchWorker() {
  }

  cv::Mat descFrom;
  cv::Mat descTo;
  std::vector<cv::DMatch> dmatches;

  std::string executeCatchCvExceptionWorker() {
    matcher->match(descFrom, descTo, dmatches);
    return "";
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return Mat::Converter::arg(0, &descFrom, info)
           || Mat::Converter::arg(1, &descTo, info);
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return DescriptorMatch::ArrayConverter::wrap(dmatches);
  }
};

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
Napi::Value DescriptorMatching::match(const Napi::CallbackInfo& info, cv::DescriptorMatcher::MatcherType matcherType) {
#elif CV_VERSION_GREATER_EQUAL(3, 2, 0)
Napi::Value DescriptorMatching::match(const Napi::CallbackInfo& info, int matcherType) {
#else
Napi::Value DescriptorMatching::match(const Napi::CallbackInfo& info, std::string matcherType) {
#endif
  return FF::executeSyncBinding(
      std::make_shared<MatchWorker>(cv::DescriptorMatcher::create(matcherType)),
      "Match",
      info);
}

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
Napi::Value DescriptorMatching::matchAsync(const Napi::CallbackInfo& info, cv::DescriptorMatcher::MatcherType matcherType) {
#elif CV_VERSION_GREATER_EQUAL(3, 2, 0)
Napi::Value DescriptorMatching::matchAsync(const Napi::CallbackInfo& info, int matcherType) {
#else
Napi::Value DescriptorMatching::matchAsync(const Napi::CallbackInfo& info, std::string matcherType) {
#endif
  return FF::executeAsyncBinding(
      std::make_shared<MatchWorker>(cv::DescriptorMatcher::create(matcherType)),
      "MatchAsync",
      info);
}

#endif