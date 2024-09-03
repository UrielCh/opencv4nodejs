#include "HistAxes.h"
#include "Mat.h"
#include "Point.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "Size.h"
#include "TermCriteria.h"
#include "Vec.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_CORE_H__
#define __FF_CORE_H__

class Core : public Napi::ObjectWrap<Core> {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static void GetBuildInformation(const Napi::CallbackInfo& info);
  static void Partition(const Napi::CallbackInfo& info);
  static void Kmeans(const Napi::CallbackInfo& info);
  static void CartToPolar(const Napi::CallbackInfo& info);
  static void CartToPolarAsync(const Napi::CallbackInfo& info);
  static void PolarToCart(const Napi::CallbackInfo& info);
  static void PolarToCartAsync(const Napi::CallbackInfo& info);
  static void GetNumThreads(const Napi::CallbackInfo& info);
  static void SetNumThreads(const Napi::CallbackInfo& info);
  static void GetThreadNum(const Napi::CallbackInfo& info);

  static void AddWeighted(const Napi::CallbackInfo& info);
  static void AddWeightedAsync(const Napi::CallbackInfo& info);
  static void MinMaxLoc(const Napi::CallbackInfo& info);
  static void MinMaxLocAsync(const Napi::CallbackInfo& info);
  static void FindNonZero(const Napi::CallbackInfo& info);
  static void FindNonZeroAsync(const Napi::CallbackInfo& info);
  static void CountNonZero(const Napi::CallbackInfo& info);
  static void CountNonZeroAsync(const Napi::CallbackInfo& info);
  static void Normalize(const Napi::CallbackInfo& info);
  static void NormalizeAsync(const Napi::CallbackInfo& info);
  static void Split(const Napi::CallbackInfo& info);
  static void SplitAsync(const Napi::CallbackInfo& info);
  static void MulSpectrums(const Napi::CallbackInfo& info);
  static void MulSpectrumsAsync(const Napi::CallbackInfo& info);
  static void Transform(const Napi::CallbackInfo& info);
  static void TransformAsync(const Napi::CallbackInfo& info);
  static void PerspectiveTransform(const Napi::CallbackInfo& info);
  static void PerspectiveTransformAsync(const Napi::CallbackInfo& info);
  static void Sum(const Napi::CallbackInfo& info);
  static void SumAsync(const Napi::CallbackInfo& info);
  static void ConvertScaleAbs(const Napi::CallbackInfo& info);
  static void ConvertScaleAbsAsync(const Napi::CallbackInfo& info);
  static void Mean(const Napi::CallbackInfo& info);
  static void MeanAsync(const Napi::CallbackInfo& info);
  static void MeanStdDev(const Napi::CallbackInfo& info);
  static void MeanStdDevAsync(const Napi::CallbackInfo& info);
  static void Reduce(const Napi::CallbackInfo& info);
  static void ReduceAsync(const Napi::CallbackInfo& info);
  static void Min(const Napi::CallbackInfo& info);
  static void MinAsync(const Napi::CallbackInfo& info);
  static void Max(const Napi::CallbackInfo& info);
  static void MaxAsync(const Napi::CallbackInfo& info);
  static void Eigen(const Napi::CallbackInfo& info);
  static void EigenAsync(const Napi::CallbackInfo& info);
  static void Solve(const Napi::CallbackInfo& info);
  static void SolveAsync(const Napi::CallbackInfo& info);
  static void Magnitude(const Napi::CallbackInfo& info);
  static void MagnitudeAsync(const Napi::CallbackInfo& info);

  static void GetTickFrequency(const Napi::CallbackInfo& info);
  static void GetTickCount(const Napi::CallbackInfo& info);
#if CV_VERSION_GREATER_EQUAL(3, 4, 2)
  static void GetVersionMajor(const Napi::CallbackInfo& info);
  static void GetVersionMinor(const Napi::CallbackInfo& info);
  static void GetVersionRevision(const Napi::CallbackInfo& info);
#endif
};

#endif
