#include "imgproc.h"

#ifndef __FF_CONTOURBINDINGS_H_
#define __FF_CONTOURBINDINGS_H_

namespace ContourBindings {

struct ApproxPolyDPWorker : public CatchCvExceptionWorker {
public:
  std::vector<cv::Point2i> self;
  ApproxPolyDPWorker(std::vector<cv::Point2i> self) {
    this->self = self;
  }
  virtual ~ApproxPolyDPWorker() {
  }

  double epsilon;
  bool closed;
  std::vector<cv::Point2i> curve;
  std::string executeCatchCvExceptionWorker() {
    cv::approxPolyDP(self, curve, epsilon, closed);
    return "";
  }

  Napi::Value getReturnValue() {
    return Point2::ArrayWithCastConverter<cv::Point2i>::wrap(curve);
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (
        FF::DoubleConverter::arg(0, &epsilon, info) || FF::BoolConverter::arg(1, &closed, info));
  }
};
} // namespace ContourBindings
#endif
