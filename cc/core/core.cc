#include "core.h"
#include "coreBindings.h"
#include "coreConstants.h"
#include "matTypes.h"

Napi::Object Core(Napi::Env env, Napi::Object exports) {
  initMatTypes(env, exports);
  CoreConstants::Init(env, exports);
  Mat::Init(env, exports);
  Point::Init(env, exports);
  Vec::Init(env, exports);
  Size::Init(env, exports);
  Rect::Init(env, exports);
  RotatedRect::Init(env, exports);
  TermCriteria::Init(env, exports);
  HistAxes::Init(env, exports);

  exports.Set("getBuildInformation", Napi::Function::New(env, Core::GetBuildInformation));
  exports.Set("partition", Napi::Function::New(env, Core::Partition));
  exports.Set("kmeans", Napi::Function::New(env, Core::Kmeans));
  exports.Set("cartToPolar", Napi::Function::New(env, Core::CartToPolar));
  exports.Set("cartToPolarAsync", Napi::Function::New(env, Core::CartToPolarAsync));
  exports.Set("polarToCart", Napi::Function::New(env, Core::PolarToCart));
  exports.Set("polarToCartAsync", Napi::Function::New(env, Core::PolarToCartAsync));
  exports.Set("getNumThreads", Napi::Function::New(env, Core::GetNumThreads));
  exports.Set("setNumThreads", Napi::Function::New(env, Core::SetNumThreads));
  exports.Set("getThreadNum", Napi::Function::New(env, Core::GetThreadNum));

  exports.Set("addWeighted", Napi::Function::New(env, Core::AddWeighted));
  exports.Set("addWeightedAsync", Napi::Function::New(env, Core::AddWeightedAsync));
  exports.Set("minMaxLoc", Napi::Function::New(env, Core::MinMaxLoc));
  exports.Set("minMaxLocAsync", Napi::Function::New(env, Core::MinMaxLocAsync));
  exports.Set("findNonZero", Napi::Function::New(env, Core::FindNonZero));
  exports.Set("findNonZeroAsync", Napi::Function::New(env, Core::FindNonZeroAsync));
  exports.Set("countNonZero", Napi::Function::New(env, Core::CountNonZero));
  exports.Set("countNonZeroAsync", Napi::Function::New(env, Core::CountNonZeroAsync));
  exports.Set("split", Napi::Function::New(env, Core::Split));
  exports.Set("splitAsync", Napi::Function::New(env, Core::SplitAsync));
  exports.Set("mulSpectrums", Napi::Function::New(env, Core::MulSpectrums));
  exports.Set("mulSpectrumsAsync", Napi::Function::New(env, Core::MulSpectrumsAsync));
  exports.Set("transform", Napi::Function::New(env, Core::Transform));
  exports.Set("transformAsync", Napi::Function::New(env, Core::TransformAsync));
  exports.Set("perspectiveTransform", Napi::Function::New(env, Core::PerspectiveTransform));
  exports.Set("perspectiveTransformAsync", Napi::Function::New(env, Core::PerspectiveTransformAsync));
  exports.Set("convertScaleAbs", Napi::Function::New(env, Core::ConvertScaleAbs));
  exports.Set("convertScaleAbsAsync", Napi::Function::New(env, Core::ConvertScaleAbsAsync));
  exports.Set("sum", Napi::Function::New(env, Core::Sum));
  exports.Set("sumAsync", Napi::Function::New(env, Core::SumAsync));
  exports.Set("mean", Napi::Function::New(env, Core::Mean));
  exports.Set("meanAsync", Napi::Function::New(env, Core::MeanAsync));
  exports.Set("meanStdDev", Napi::Function::New(env, Core::MeanStdDev));
  exports.Set("meanStdDevAsync", Napi::Function::New(env, Core::MeanStdDevAsync));
  exports.Set("reduce", Napi::Function::New(env, Core::Reduce));
  exports.Set("reduceAsync", Napi::Function::New(env, Core::ReduceAsync));

  exports.Set("eigen", Napi::Function::New(env, Core::Eigen));
  exports.Set("eigenAsync", Napi::Function::New(env, Core::EigenAsync));

  exports.Set("min", Napi::Function::New(env, Core::Min));
  exports.Set("minAsync", Napi::Function::New(env, Core::MinAsync));

  exports.Set("max", Napi::Function::New(env, Core::Max));
  exports.Set("maxAsync", Napi::Function::New(env, Core::MaxAsync));

  exports.Set("solve", Napi::Function::New(env, Core::Solve));
  exports.Set("solveAsync", Napi::Function::New(env, Core::SolveAsync));

  exports.Set("magnitude", Napi::Function::New(env, Core::Magnitude));
  exports.Set("magnitudeAsync", Napi::Function::New(env, Core::MagnitudeAsync));

  exports.Set("getTickFrequency", Napi::Function::New(env, Core::GetTickFrequency));
  exports.Set("getTickCount", Napi::Function::New(env, Core::GetTickCount));
#if CV_VERSION_GREATER_EQUAL(3, 4, 2)
  exports.Set("getVersionMajor", Napi::Function::New(env, Core::GetVersionMajor));
  exports.Set("getVersionMinor", Napi::Function::New(env, Core::GetVersionMinor));
  exports.Set("getVersionRevision", Napi::Function::New(env, Core::GetVersionRevision));
#endif
};

/**
 * export function getBuildInformation(): string;
 */
Napi::Value Core::GetBuildInformation(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::String::New(env, cv::getBuildInformation());
}

template <class TClass, class TNativeObject>
static std::function<bool(TNativeObject, TNativeObject)> predicateFactory(Napi::Function cb) {
  return [cb](TNativeObject pt1, TNativeObject pt2) {
    Napi::Value cbArgs[2];
    cbArgs[0] = TClass::Converter::wrap(pt1);
    cbArgs[1] = TClass::Converter::wrap(pt2);
    Nan::AsyncResource resource("opencv4nodejs:Predicate::Constructor");
    return FF::BoolConverter::unwrapUnchecked(resource.runInAsyncScope(Nan::GetCurrentContext()->Global(), cb, 2, cbArgs).ToLocalChecked());
  };
}

/**
 * export function partition<T extends Point2|Point3|Vec2|Vec3|Vec4|Vec6|Mat>(data: Array<T>, predicate: (pt1: T, pt2: T) => boolean): { labels: number[], numLabels: number };
 */
Napi::Value Core::Partition(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Core::Partition");
  if (!info[0].IsArray()) {
    return tryCatch.throwError("expected arg 0 to be an array");
  }
  Napi::Array jsData = info[0].As<Napi::Array>();
  if (!info[1].IsFunction()) {
    return tryCatch.throwError("expected arg 1 to be a function");
  }
  if (jsData.Length() < 2) {
    return tryCatch.throwError("expected data to contain atleast 2 elements");
  }

  Napi::Function cb = Napi::Function::Cast(info[1]);
  Napi::Value data0 = jsData.Get(uint32_t(0));

  int numLabels = 0;
  std::vector<int> labels;

  if (Point2::hasInstance(data0)) {
    std::vector<cv::Point2d> pts;
    if (Point2::ArrayConverter::arg(0, &pts, info)) {
      return tryCatch.reThrow();
    }

    numLabels = cv::partition(pts, labels, predicateFactory<Point2, cv::Point2d>(cb));
  } else if (Point3::hasInstance(data0)) {
    std::vector<cv::Point3d> pts;
    if (Point3::ArrayConverter::arg(0, &pts, info)) {
      return tryCatch.reThrow();
    }
    numLabels = cv::partition(pts, labels, predicateFactory<Point3, cv::Point3d>(cb));
  } else if (Vec2::hasInstance(data0)) {
    std::vector<cv::Vec2d> pts;
    if (Vec2::ArrayConverter::arg(0, &pts, info)) {
      return tryCatch.reThrow();
    }
    numLabels = cv::partition(pts, labels, predicateFactory<Vec2, cv::Vec2d>(cb));
  } else if (Vec3::hasInstance(data0)) {
    std::vector<cv::Vec3d> pts;
    if (Vec3::ArrayConverter::arg(0, &pts, info)) {
      return tryCatch.reThrow();
    }
    numLabels = cv::partition(pts, labels, predicateFactory<Vec3, cv::Vec3d>(cb));
  } else if (Vec4::hasInstance(data0)) {
    std::vector<cv::Vec4d> pts;
    if (Vec4::ArrayConverter::arg(0, &pts, info)) {
      return tryCatch.reThrow();
    }
    numLabels = cv::partition(pts, labels, predicateFactory<Vec4, cv::Vec4d>(cb));
  } else if (Vec6::hasInstance(data0)) {
    std::vector<cv::Vec6d> pts;
    if (Vec6::ArrayConverter::arg(0, &pts, info)) {
      return tryCatch.reThrow();
    }
    numLabels = cv::partition(pts, labels, predicateFactory<Vec6, cv::Vec6d>(cb));
  } else if (Mat::hasInstance(data0)) {
    std::vector<cv::Mat> mats;
    if (Mat::ArrayConverter::arg(0, &mats, info)) {
      return tryCatch.reThrow();
    }
    numLabels = cv::partition(mats, labels, predicateFactory<Mat, cv::Mat>(cb));
  }

  Napi::Object ret = Napi::Object::New(env);
  ret.Set("labels", FF::IntArrayConverter::wrap(labels));
  ret.Set("numLabels", Nan::New(numLabels));
  return ret;
}

/**
 * export function kmeans<T extends Point2|Point3>(data: T[], k: number, termCriteria: TermCriteria, attempts: number, flags: number): { labels: number[], centers: T[] };
 */
Napi::Value Core::Kmeans(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Core::Kmeans");
  if (!info[0].IsArray()) {
    return tryCatch.throwError("expected arg 0 to be an array");
  }
  v8::Local<v8::Array> jsData = v8::Local<v8::Array>::Cast(info[0]);

  if (jsData->Length() < 1) {
    return tryCatch.throwError("expected data to contain at least 1 element");
  }

  Napi::Value data0 = Nan::Get(jsData, 0).ToLocalChecked();
  bool isPoint2 = Point2::hasInstance(data0);

  std::vector<cv::Point2f> pts2d;
  std::vector<cv::Point3f> pts3d;

  cv::TermCriteria termCriteria;
  int k, attempts, flags;
  if ((
          (isPoint2 && Point2::ArrayWithCastConverter<cv::Point2f>::arg(0, &pts2d, info)) || (!isPoint2 && Point3::ArrayWithCastConverter<cv::Point3f>::arg(0, &pts3d, info)))
      || FF::IntConverter::arg(1, &k, info) || TermCriteria::Converter::arg(2, &termCriteria, info) || FF::IntConverter::arg(3, &attempts, info) || FF::IntConverter::arg(4, &flags, info)) {
    return tryCatch.reThrow();
  }

  std::vector<int> labels;
  cv::Mat centersMat;

  if (isPoint2) {
    cv::kmeans(pts2d, k, labels, termCriteria, attempts, flags, centersMat);
  } else {
    cv::kmeans(pts3d, k, labels, termCriteria, attempts, flags, centersMat);
  }

  Napi::Object ret = Napi::Object::New(env);
  Nan::Set(ret, FF::newString(env, "labels"), FF::IntArrayConverter::wrap(labels));

  if (Point2::hasInstance(data0)) {
    std::vector<cv::Point2f> centers;
    for (int i = 0; i < centersMat.rows; i++) {
      centers.push_back(cv::Point2f(centersMat.at<float>(i, 0), centersMat.at<float>(i, 1)));
    }
    Nan::Set(ret, FF::newString(env, "centers"), Point2::ArrayWithCastConverter<cv::Point2f>::wrap(centers));
  } else if (Point3::hasInstance(data0)) {
    std::vector<cv::Point3f> centers;
    for (int i = 0; i < centersMat.rows; i++) {
      centers.push_back(cv::Point3f(centersMat.at<float>(i, 0), centersMat.at<float>(i, 1), centersMat.at<float>(i, 2)));
    }
    Nan::Set(ret, FF::newString(env, "centers"), Point3::ArrayWithCastConverter<cv::Point3f>::wrap(centers));
  }
  return ret;
}

void Core::CartToPolar(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::CartToPolar>("Core", "CartToPolar", info);
}

void Core::CartToPolarAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::CartToPolar>("Core", "CartToPolar", info);
}

void Core::PolarToCart(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::PolarToCart>("Core", "PolarToCart", info);
}

void Core::PolarToCartAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::PolarToCart>("Core", "PolarToCart", info);
}

Napi::Value Core::GetNumThreads(const Napi::CallbackInfo& info) {
  return FF::IntConverter::wrap(cv::getNumThreads());
}

void Core::SetNumThreads(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "Core::SetNumThreads");
  int num;
  if (FF::IntConverter::arg(0, &num, info)) {
    return tryCatch.reThrow();
  }
  cv::setNumThreads(num);
}

Napi::Value Core::GetThreadNum(const Napi::CallbackInfo& info) {
  return FF::IntConverter::wrap(cv::getThreadNum());
}

void Core::AddWeighted(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::AddWeighted>("Core", "AddWeighted", info);
}

void Core::AddWeightedAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::AddWeighted>("Core", "AddWeighted", info);
}

void Core::MinMaxLoc(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::MinMaxLoc>("Core", "MinMaxLoc", info);
}

void Core::MinMaxLocAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::MinMaxLoc>("Core", "MinMaxLoc", info);
}

void Core::FindNonZero(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::FindNonZero>("Core", "FindNonZero", info);
}

void Core::FindNonZeroAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::FindNonZero>("Core", "FindNonZero", info);
}

void Core::CountNonZero(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::CountNonZero>("Core", "CountNonZero", info);
}

void Core::CountNonZeroAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::CountNonZero>("Core", "CountNonZero", info);
}

void Core::Normalize(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::Normalize>("Core", "Normalize", info);
}

void Core::NormalizeAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::Normalize>("Core", "Normalize", info);
}

void Core::Split(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::Split>("Core", "Split", info);
}

void Core::SplitAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::Split>("Core", "Split", info);
}

void Core::MulSpectrums(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::MulSpectrums>("Core", "MulSpectrums", info);
}

void Core::MulSpectrumsAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::MulSpectrums>("Core", "MulSpectrums", info);
}

void Core::Transform(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::Transform>("Core", "Transform", info);
}

void Core::TransformAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::Transform>("Core", "Transform", info);
}

void Core::PerspectiveTransform(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::PerspectiveTransform>("Core", "PerspectiveTransform", info);
}

void Core::PerspectiveTransformAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::PerspectiveTransform>("Core", "PerspectiveTransform", info);
}

void Core::Sum(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::Sum>("Core", "Sum", info);
}

void Core::SumAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::Sum>("Core", "Sum", info);
}

void Core::ConvertScaleAbs(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::ConvertScaleAbs>("Core", "ConvertScaleAbs", info);
}

void Core::ConvertScaleAbsAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::ConvertScaleAbs>("Core", "ConvertScaleAbs", info);
}

void Core::Mean(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::Mean>("Core", "Mean", info);
}

void Core::MeanAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::Mean>("Core", "Mean", info);
}

void Core::MeanStdDev(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::MeanStdDev>("Core", "MeanStdDev", info);
}

void Core::MeanStdDevAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::MeanStdDev>("Core", "MeanStdDev", info);
}

void Core::Reduce(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::Reduce>("Core", "Reduce", info);
}

void Core::ReduceAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::Reduce>("Core", "Reduce", info);
}

void Core::Eigen(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::Eigen>("Core", "Eigen", info);
}

void Core::EigenAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::Eigen>("Core", "Eigen", info);
}

void Core::Min(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::Min>("Core", "Min", info);
}

void Core::MinAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::Min>("Core", "Min", info);
}

void Core::Max(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::Max>("Core", "Max", info);
}

void Core::MaxAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::Max>("Core", "Max", info);
}

void Core::Solve(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::Solve>("Core", "Solve", info);
}

void Core::SolveAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::Solve>("Core", "Solve", info);
}

void Core::Magnitude(const Napi::CallbackInfo& info) {
  FF::syncBinding<CoreBindings::Magnitude>("Core", "Magnitude", info);
}

void Core::MagnitudeAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<CoreBindings::Magnitude>("Core", "Magnitude", info);
}

void Core::GetTickFrequency(const Napi::CallbackInfo& info) {
  info.GetReturnValue().Set(FF::IntConverter::wrap(cv::getTickFrequency()));
}

void Core::GetTickCount(const Napi::CallbackInfo& info) {
  info.GetReturnValue().Set(FF::IntConverter::wrap(cv::getTickCount()));
}

#if CV_VERSION_GREATER_EQUAL(3, 4, 2)
void Core::GetVersionMajor(const Napi::CallbackInfo& info) {
  info.GetReturnValue().Set(FF::IntConverter::wrap(cv::getVersionMajor()));
}

void Core::GetVersionMinor(const Napi::CallbackInfo& info) {
  info.GetReturnValue().Set(FF::IntConverter::wrap(cv::getVersionMinor()));
}

void Core::GetVersionRevision(const Napi::CallbackInfo& info) {
  info.GetReturnValue().Set(FF::IntConverter::wrap(cv::getVersionRevision()));
}
#endif