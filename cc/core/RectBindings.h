#include "Rect.h"

#ifndef __FF_RECTBINDINGS_H__
#define __FF_RECTBINDINGS_H__

namespace RectBindings {

struct LogicOpWorker : public CatchCvExceptionWorker {
public:
  cv::Rect2d rect;
  cv::Rect2d rect2;
  cv::Rect2d outRect;

  LogicOpWorker(cv::Rect2d rect) {
    this->rect = rect;
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (
        Rect::Converter::arg(0, &rect2, info));
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return Rect::Converter::wrap(outRect);
  }
};

struct AndWorker : public LogicOpWorker {
public:
  AndWorker(cv::Rect2d rect)
      : LogicOpWorker(rect) {
  }

  std::string executeCatchCvExceptionWorker() {
    outRect = rect & rect2;
    return "";
  }

  virtual ~AndWorker() {
  }
};

struct OrWorker : public LogicOpWorker {
public:
  OrWorker(cv::Rect2d rect)
      : LogicOpWorker(rect) {
  }

  std::string executeCatchCvExceptionWorker() {
    outRect = rect | rect2;
    return "";
  }

  virtual ~OrWorker() {
  }
};

struct ToSquareWorker : CatchCvExceptionWorker {
public:
  cv::Rect2d rect;
  cv::Rect2d outRect;

  ToSquareWorker(cv::Rect2d rect) {
    this->rect = rect;
  }

  std::string executeCatchCvExceptionWorker() {
    double diff = rect.width - rect.height;
    if (diff < 0) {
      outRect = cv::Rect(rect.x + (diff / 2), rect.y, rect.width - diff, rect.height);
    } else {
      outRect = cv::Rect(rect.x, rect.y - (diff / 2), rect.width, rect.height + diff);
    }
    return "";
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return Rect::Converter::wrap(outRect);
  }

  virtual ~ToSquareWorker() {
  }
};

struct PadWorker : CatchCvExceptionWorker {
public:
  cv::Rect2d rect;
  cv::Size2d newSize = cv::Size2d();
  cv::Rect2d outRect;

  PadWorker(cv::Rect2d rect) {
    this->rect = rect;
  }

  std::string executeCatchCvExceptionWorker() {
    double offX = (rect.width - newSize.width) / 2;
    double offY = (rect.height - newSize.height) / 2;
    outRect = cv::Rect(rect.x + offX, rect.y + offY, newSize.width, newSize.height);
    return "";
  }

  /**
   * args[0] can be a cv::Size2d or a number
   */
  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    bool isSizeArg = Size::hasInstance(info[0]);
    double f = 1;
    bool didThrow =
        (!isSizeArg && FF::DoubleConverter::arg(0, &f, info))
        || (isSizeArg && Size::Converter::arg(0, &newSize, info));

    if (!isSizeArg) {
      newSize = cv::Size2d(rect.width * f, rect.height * f);
    }
    return didThrow;
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return Rect::Converter::wrap(outRect);
  }

  virtual ~PadWorker() {
  }
};

struct RescaleWorker : CatchCvExceptionWorker {
public:
  cv::Rect2d rect;
  double f;
  cv::Rect2d outRect;

  RescaleWorker(cv::Rect2d rect) {
    this->rect = rect;
  }

  std::string executeCatchCvExceptionWorker() {
    outRect = cv::Rect(f * rect.x, f * rect.y, f * rect.width, f * rect.height);
    return "";
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (
        FF::DoubleConverter::arg(0, &f, info));
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return Rect::Converter::wrap(outRect);
  }

  virtual ~RescaleWorker() {
  }
};

} // namespace RectBindings

#endif