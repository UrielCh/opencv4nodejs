#include "BFMatcher.h"
#include "DescriptorMatch.h"

#ifndef __FF_BFMATCHERBINDINGS_H_
#define __FF_BFMATCHERBINDINGS_H_

namespace BFMatcherBindings {

struct MatchWorker : public CatchCvExceptionWorker {
public:
  cv::BFMatcher bfmatcher;

  MatchWorker(cv::BFMatcher _bfmatcher) {
    this->bfmatcher = _bfmatcher;
  }

  virtual ~MatchWorker() {
  }

  cv::Mat descFrom;
  cv::Mat descTo;
  std::vector<cv::DMatch> dmatches;

  std::string executeCatchCvExceptionWorker() {
    bfmatcher.match(descFrom, descTo, dmatches);
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

struct MatchKnnWorker : public CatchCvExceptionWorker {
public:
  cv::BFMatcher bfmatcher;

  MatchKnnWorker(cv::BFMatcher _bfmatcher) {
    this->bfmatcher = _bfmatcher;
  }

  virtual ~MatchKnnWorker() {
  }

  cv::Mat descFrom;
  cv::Mat descTo;
  int k;
  std::vector<std::vector<cv::DMatch>> dmatches;

  std::string executeCatchCvExceptionWorker() {
    bfmatcher.knnMatch(descFrom, descTo, dmatches, k);
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
} // namespace BFMatcherBindings

#endif
