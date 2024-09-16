#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "descriptorMatchingKnn.h"

Napi::Object DescriptorMatchingKnn(Napi::Env env, Napi::Object exports) {
  exports.Set("matchKnnFlannBased", Napi::Function::New(env, DescriptorMatchingKnn::MatchKnnFlannBased));
  exports.Set("matchKnnBruteForce", Napi::Function::New(env, DescriptorMatchingKnn::MatchKnnBruteForce));
  exports.Set("matchKnnBruteForceL1", Napi::Function::New(env, DescriptorMatchingKnn::MatchKnnBruteForceL1));
  exports.Set("matchKnnBruteForceHamming", Napi::Function::New(env, DescriptorMatchingKnn::MatchKnnBruteForceHamming));
  exports.Set("matchKnnFlannBasedAsync", Napi::Function::New(env, DescriptorMatchingKnn::MatchKnnFlannBasedAsync));
  exports.Set("matchKnnBruteForceAsync", Napi::Function::New(env, DescriptorMatchingKnn::MatchKnnBruteForceAsync));
  exports.Set("matchKnnBruteForceL1Async", Napi::Function::New(env, DescriptorMatchingKnn::MatchKnnBruteForceL1Async));
  exports.Set("matchKnnBruteForceHammingAsync", Napi::Function::New(env, DescriptorMatchingKnn::MatchKnnBruteForceHammingAsync));
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  exports.Set("matchKnnBruteForceHammingLut", Napi::Function::New(env, DescriptorMatchingKnn::MatchKnnBruteForceHammingLut));
  exports.Set("matchKnnBruteForceSL2", Napi::Function::New(env, DescriptorMatchingKnn::MatchKnnBruteForceSL2));
  exports.Set("matchKnnBruteForceHammingLutAsync", Napi::Function::New(env, DescriptorMatchingKnn::MatchKnnBruteForceHammingLutAsync));
  exports.Set("matchKnnBruteForceSL2Async", Napi::Function::New(env, DescriptorMatchingKnn::MatchKnnBruteForceSL2Async));
#endif
};

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)

Napi::Value DescriptorMatchingKnn::MatchKnnFlannBased(const Napi::CallbackInfo& info) {
  return matchKnn(info, cv::DescriptorMatcher::FLANNBASED);
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForce(const Napi::CallbackInfo& info) {
  return matchKnn(info, cv::DescriptorMatcher::BRUTEFORCE);
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForceL1(const Napi::CallbackInfo& info) {
  return matchKnn(info, cv::DescriptorMatcher::BRUTEFORCE_L1);
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForceHamming(const Napi::CallbackInfo& info) {
  return matchKnn(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMING);
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForceHammingLut(const Napi::CallbackInfo& info) {
  return matchKnn(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMINGLUT);
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForceSL2(const Napi::CallbackInfo& info) {
  return matchKnn(info, cv::DescriptorMatcher::BRUTEFORCE_SL2);
}

Napi::Value DescriptorMatchingKnn::MatchKnnFlannBasedAsync(const Napi::CallbackInfo& info) {
  return matchKnnAsync(info, cv::DescriptorMatcher::FLANNBASED);
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForceAsync(const Napi::CallbackInfo& info) {
  return matchKnnAsync(info, cv::DescriptorMatcher::BRUTEFORCE);
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForceL1Async(const Napi::CallbackInfo& info) {
  return matchKnnAsync(info, cv::DescriptorMatcher::BRUTEFORCE_L1);
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForceHammingAsync(const Napi::CallbackInfo& info) {
  return matchKnnAsync(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMING);
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForceHammingLutAsync(const Napi::CallbackInfo& info) {
  return matchKnnAsync(info, cv::DescriptorMatcher::BRUTEFORCE_HAMMINGLUT);
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForceSL2Async(const Napi::CallbackInfo& info) {
  return matchKnnAsync(info, cv::DescriptorMatcher::BRUTEFORCE_SL2);
}

#else

Napi::Value DescriptorMatchingKnn::MatchKnnFlannBased(const Napi::CallbackInfo& info) {
  return matchKnn(info, "FlannBased");
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForce(const Napi::CallbackInfo& info) {
  return matchKnn(info, "BruteForce");
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForceL1(const Napi::CallbackInfo& info) {
  return matchKnn(info, "BruteForce-L1");
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForceHamming(const Napi::CallbackInfo& info) {
  return matchKnn(info, "BruteForce-Hamming");
}

Napi::Value DescriptorMatchingKnn::MatchKnnFlannBasedAsync(const Napi::CallbackInfo& info) {
  return matchKnnAsync(info, "FlannBased");
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForceAsync(const Napi::CallbackInfo& info) {
  return matchKnnAsync(info, "BruteForce");
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForceL1Async(const Napi::CallbackInfo& info) {
  return matchKnnAsync(info, "BruteForce-L1");
}

Napi::Value DescriptorMatchingKnn::MatchKnnBruteForceHammingAsync(const Napi::CallbackInfo& info) {
  return matchKnnAsync(info, "BruteForce-Hamming");
}

#endif

struct DescriptorMatchingKnn::MatchKnnWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::DescriptorMatcher> matcher;

  MatchKnnWorker(cv::Ptr<cv::DescriptorMatcher> _matcher) {
    this->matcher = _matcher;
  }

  virtual ~MatchKnnWorker() {
  }

  cv::Mat descFrom;
  cv::Mat descTo;
  int k;
  std::vector<std::vector<cv::DMatch>> dmatches;

  std::string executeCatchCvExceptionWorker() {
    matcher->knnMatch(descFrom, descTo, dmatches, k);
    return "";
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return Mat::Converter::arg(0, &descFrom, info)
           || Mat::Converter::arg(1, &descTo, info)
           || FF::IntConverter::arg(2, &k, info);
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return DescriptorMatch::ArrayOfArraysConverter::wrap(dmatches);
  }
};

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
Napi::Value DescriptorMatchingKnn::matchKnn(const Napi::CallbackInfo& info, cv::DescriptorMatcher::MatcherType matcherType) {
#elif CV_VERSION_GREATER_EQUAL(3, 2, 0)
Napi::Value DescriptorMatchingKnn::matchKnn(const Napi::CallbackInfo& info, int matcherType) {
#else
Napi::Value DescriptorMatchingKnn::matchKnn(const Napi::CallbackInfo& info, std::string matcherType) {
#endif
  return FF::executeSyncBinding(
      std::make_shared<MatchKnnWorker>(cv::DescriptorMatcher::create(matcherType)),
      "MSERDetector::MatchKnn",
      info);
}

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
Napi::Value DescriptorMatchingKnn::matchKnnAsync(const Napi::CallbackInfo& info, cv::DescriptorMatcher::MatcherType matcherType) {
#elif CV_VERSION_GREATER_EQUAL(3, 2, 0)
Napi::Value DescriptorMatchingKnn::matchKnnAsync(const Napi::CallbackInfo& info, int matcherType) {
#else
Napi::Value DescriptorMatchingKnn::matchKnnAsync(const Napi::CallbackInfo& info, std::string matcherType) {
#endif
  return FF::executeAsyncBinding(
      std::make_shared<MatchKnnWorker>(cv::DescriptorMatcher::create(matcherType)),
      "MSERDetector::MatchKnnAsync",
      info);
}

#endif
