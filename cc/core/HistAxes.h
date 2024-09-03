//
// Created by stefan on 11/4/19.
//
#include "macros.h"

#ifndef __FF_HISTAXES_H__
#define __FF_HISTAXES_H__

namespace internal {
class HistAxes {
public:
  std::vector<double> range = {};
  int channel = 0;
  int bins = 0;
};
} // namespace internal

class HistAxes : public FF::ObjectWrap<HistAxes, internal::HistAxes> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "HistAxes";
  }

  static void New(const Napi::CallbackInfo& info);

  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  FF_GETTER_CUSTOM(bins, FF::IntConverter, self.bins);
  FF_GETTER_CUSTOM(channel, FF::IntConverter, self.channel);
  FF_GETTER_CUSTOM(ranges, FF::DoubleArrayConverter, self.range);
};

#endif //__FF_HISTAXES_H__
