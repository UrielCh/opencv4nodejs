#include "opencv_modules.h"

#ifdef HAVE_OPENCV_IMGPROC

#include "imgproc.h"
#include "imgprocBindings.h"
#include "imgprocConstants.h"

Napi::Object Imgproc(Napi::Env env, Napi::Object exports) {
  ImgprocConstants::Init(env, exports);
  exports.Set("getStructuringElement", Napi::Function::New(env, Imgproc::GetStructuringElement));
  exports.Set("getRotationMatrix2D", Napi::Function::New(env, Imgproc::GetRotationMatrix2D));
  exports.Set("plot1DHist", Napi::Function::New(env, Imgproc::Plot1DHist));
  exports.Set("fitLine", Napi::Function::New(env, Imgproc::FitLine));
  exports.Set("getAffineTransform", Napi::Function::New(env, Imgproc::GetAffineTransform));
  exports.Set("getPerspectiveTransform", Napi::Function::New(env, Imgproc::GetPerspectiveTransform));
  exports.Set("getTextSize", Napi::Function::New(env, Imgproc::GetTextSize));
  exports.Set("getTextSizeAsync", Napi::Function::New(env, Imgproc::GetTextSizeAsync));
  exports.Set("applyColorMap", Napi::Function::New(env, Imgproc::ApplyColorMap));
  exports.Set("applyColorMapAsync", Napi::Function::New(env, Imgproc::ApplyColorMapAsync));
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  exports.Set("canny", Napi::Function::New(env, Imgproc::Canny));
  exports.Set("cannyAsync", Napi::Function::New(env, Imgproc::CannyAsync));
#endif
#if CV_VERSION_LOWER_THAN(4, 0, 0)
  exports.Set("undistortPoints", Napi::Function::New(env, Imgproc::UndistortPoints));
  exports.Set("undistortPointsAsync", Napi::Function::New(env, Imgproc::UndistortPointsAsync));
#endif
  exports.Set("goodFeaturesToTrack", Napi::Function::New(env, Imgproc::GoodFeaturesToTrack));
  exports.Set("goodFeaturesToTrackAsync", Napi::Function::New(env, Imgproc::GoodFeaturesToTrackAsync));
  exports.Set("blur", Napi::Function::New(env, Imgproc::Blur));
  exports.Set("blurAsync", Napi::Function::New(env, Imgproc::BlurAsync));
  exports.Set("gaussianBlur", Napi::Function::New(env, Imgproc::GaussianBlur));
  exports.Set("gaussianBlurAsync", Napi::Function::New(env, Imgproc::GaussianBlurAsync));
  exports.Set("medianBlur", Napi::Function::New(env, Imgproc::MedianBlur));
  exports.Set("medianBlurAsync", Napi::Function::New(env, Imgproc::MedianBlurAsync));
  exports.Set("accumulate", Napi::Function::New(env, Imgproc::Accumulate));
  exports.Set("accumulateAsync", Napi::Function::New(env, Imgproc::AccumulateAsync));
  exports.Set("accumulateProduct", Napi::Function::New(env, Imgproc::AccumulateProduct));
  exports.Set("accumulateProductAsync", Napi::Function::New(env, Imgproc::AccumulateProductAsync));
  exports.Set("accumulateSquare", Napi::Function::New(env, Imgproc::AccumulateSquare));
  exports.Set("accumulateSquareAsync", Napi::Function::New(env, Imgproc::AccumulateSquareAsync));
  exports.Set("accumulateWeighted", Napi::Function::New(env, Imgproc::AccumulateWeighted));
  exports.Set("accumulateWeightedAsync", Napi::Function::New(env, Imgproc::AccumulateWeightedAsync));
  exports.Set("calcHist", Napi::Function::New(env, Imgproc::CalcHist));
  exports.Set("calcHistAsync", Napi::Function::New(env, Imgproc::CalcHistAsync));

  Moments::Init(env, exports);
  Contour::Init(env, exports);
};

void Imgproc::GetStructuringElement(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Imgproc::GetStructuringElement");

  uint shape;
  cv::Size2d size;
  cv::Point2d anchor = cv::Point2d(-1, -1);

  if (
      FF::UintConverter::arg(0, &shape, info) || Size::Converter::arg(1, &size, info) || Point2::Converter::optArg(2, &anchor, info)) {
    return tryCatch.reThrow();
  }

  info.GetReturnValue().Set(Mat::Converter::wrap(cv::getStructuringElement(shape, size, anchor)));
}

void Imgproc::GetRotationMatrix2D(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Imgproc::GetRotationMatrix2D");

  cv::Point2d center;
  double angle, scale = 1.0;
  if (
      Point2::Converter::arg(0, &center, info) || FF::DoubleConverter::arg(1, &angle, info) || FF::DoubleConverter::optArg(2, &scale, info)) {
    return tryCatch.reThrow();
  }

  info.GetReturnValue().Set(Mat::Converter::wrap(cv::getRotationMatrix2D(center, angle, scale)));
}

void Imgproc::GetAffineTransform(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Imgproc::GetAffineTransform");

  std::vector<cv::Point2f> srcPoints, dstPoints;
  if (
      Point2::ArrayWithCastConverter<cv::Point2f>::arg(0, &srcPoints, info) || Point2::ArrayWithCastConverter<cv::Point2f>::arg(1, &dstPoints, info)) {
    return tryCatch.reThrow();
  }

  info.GetReturnValue().Set(Mat::Converter::wrap(cv::getAffineTransform(srcPoints, dstPoints)));
}

void Imgproc::GetPerspectiveTransform(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Imgproc::GetPerspectiveTransform");

  std::vector<cv::Point2f> srcPoints, dstPoints;
  if (Point2::ArrayWithCastConverter<cv::Point2f>::arg(0, &srcPoints, info)
      || Point2::ArrayWithCastConverter<cv::Point2f>::arg(1, &dstPoints, info)) {
    return tryCatch.reThrow();
  }

  info.GetReturnValue().Set(Mat::Converter::wrap(cv::getPerspectiveTransform(srcPoints, dstPoints)));
}

void Imgproc::Plot1DHist(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Imgproc::Plot1DHist");

  cv::Mat hist, plot;
  cv::Vec3d color;
  int lineType = cv::LINE_8;
  int thickness = 2;
  int shift = 0;

  Napi::Object opts = FF::isArgObject(info, 3) ? info[3]->ToObject(Nan::GetCurrentContext()).ToLocalChecked() : Napi::Object::New(env);

  if (Mat::Converter::arg(0, &hist, info) || Mat::Converter::arg(1, &plot, info) || Vec3::Converter::arg(2, &color, info) || ((FF::isArgObject(info, 3) && (FF::IntConverter::optProp(&lineType, "lineType", opts) || FF::IntConverter::optProp(&thickness, "thickness", opts) || FF::IntConverter::optProp(&shift, "shift", opts))) || (FF::IntConverter::optArg(3, &lineType, info) || FF::IntConverter::optArg(4, &thickness, info) || FF::IntConverter::optArg(5, &shift, info)))) {
    return tryCatch.reThrow();
  }

  if (1 != hist.cols) {
    return tryCatch.throwError("hist rows mismatch, expected "
                               + std::to_string(1) + ", have " + std::to_string(hist.cols));
  }
  if (hist.channels() != 1) {
    return tryCatch.throwError("expected hist to be single channeled");
  }

  double binWidth = ((double)plot.cols / (double)hist.rows);
  int plotHeight = (cv::max)(256, plot.rows - 20);
  cv::Mat normHist = hist;
  if (hist.type() != CV_64F) {
    hist.convertTo(normHist, CV_64F);
  }
  cv::normalize(normHist, normHist, 0, 256, cv::NORM_MINMAX);

  for (int i = 1; i < hist.rows; i++) {
    cv::line(
        plot,
        cv::Point(binWidth * (i - 1), plotHeight - normHist.at<double>(i - 1)),
        cv::Point(binWidth * i, plotHeight - normHist.at<double>(i)),
        color,
        thickness,
        lineType,
        shift);
  }

  info.GetReturnValue().Set(Mat::Converter::wrap(plot));
}

void Imgproc::FitLine(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Imgproc::FitLine");

  if (!info[0]->IsArray()) {
    return tryCatch.throwError("expected arg 0 to be an array");
  }
  v8::Local<v8::Array> jsPoints = v8::Local<v8::Array>::Cast(info[0]);

  if (jsPoints->Length() < 2) {
    return tryCatch.throwError("expected arg0 to be an Array with atleast 2 Points");
  }
  Napi::Value jsPt1 = Nan::Get(jsPoints, 0).ToLocalChecked();
  bool isPoint2 = Point2::hasInstance(jsPt1);
  bool isPoint3 = Point3::hasInstance(jsPt1);
  if (!isPoint2 && !isPoint3) {
    return tryCatch.throwError("expected arg0 to be an Array containing instances of Point2 or Point3");
  }

  std::vector<cv::Point2d> pts2d;
  std::vector<cv::Point3d> pts3d;
  uint distType;
  double param, reps, aeps;
  if ((
          (isPoint2 && Point2::ArrayConverter::arg(0, &pts2d, info)) || (!isPoint2 && Point3::ArrayConverter::arg(0, &pts3d, info)))
      || FF::UintConverter::arg(1, &distType, info) || FF::DoubleConverter::arg(2, &param, info) || FF::DoubleConverter::arg(3, &reps, info) || FF::DoubleConverter::arg(4, &aeps, info)) {
    return tryCatch.reThrow();
  }

  if (isPoint2) {
    cv::Vec4f lineParams;
    cv::fitLine(pts2d, lineParams, (int)distType, param, reps, aeps);
    info.GetReturnValue().Set(Vec4::Converter::wrap(lineParams));
  } else {
    cv::Vec6f lineParams;
    cv::fitLine(pts3d, lineParams, (int)distType, param, reps, aeps);
    v8::Local<v8::Array> jsLineParams = Nan::New<v8::Array>(6);
    for (int i = 0; i < 6; i++) {
      Nan::Set(jsLineParams, i, Nan::New(lineParams[i]));
    }
    info.GetReturnValue().Set(jsLineParams);
  }
}

void Imgproc::GetTextSize(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<ImgprocBindings::GetTextSizeWorker>(),
      "Imgproc::GetTextSize",
      info);
}

void Imgproc::GetTextSizeAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<ImgprocBindings::GetTextSizeWorker>(),
      "Imgproc::GetTextSizeAsync",
      info);
}

void Imgproc::ApplyColorMap(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(std::make_shared<ImgprocBindings::ApplyColorMapWorker>(),
                         "Imgproc::ApplyColorMap", info);
}

void Imgproc::ApplyColorMapAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(std::make_shared<ImgprocBindings::ApplyColorMapWorker>(),
                          "Imgproc::ApplyColorMapAsync", info);
}

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)

void Imgproc::Canny(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(std::make_shared<ImgprocBindings::CannyWorker>(),
                         "Imgproc::Canny", info);
}

void Imgproc::CannyAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(std::make_shared<ImgprocBindings::CannyWorker>(),
                          "Imgproc::CannyAsync", info);
}

#endif

#if CV_VERSION_LOWER_THAN(4, 0, 0)
void Imgproc::UndistortPoints(const Napi::CallbackInfo& info) {
  FF::syncBinding<ImgprocBindings::UndistortPoints>("Imgproc", "UndistortPoints", info);
}

void Imgproc::UndistortPointsAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<ImgprocBindings::UndistortPoints>("Imgproc", "UndistortPoints", info);
}
#endif

void Imgproc::GoodFeaturesToTrack(const Napi::CallbackInfo& info) {
  FF::syncBinding<ImgprocBindings::GoodFeaturesToTrack>("Imgproc", "GoodFeaturesToTrack", info);
}

void Imgproc::GoodFeaturesToTrackAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<ImgprocBindings::GoodFeaturesToTrack>("Imgproc", "GoodFeaturesToTrack", info);
}

void Imgproc::Blur(const Napi::CallbackInfo& info) {
  FF::syncBinding<ImgprocBindings::Blur>("Imgproc", "Blur", info);
}

void Imgproc::BlurAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<ImgprocBindings::Blur>("Imgproc", "Blur", info);
}

void Imgproc::GaussianBlur(const Napi::CallbackInfo& info) {
  FF::syncBinding<ImgprocBindings::GaussianBlur>("Imgproc", "GaussianBlur", info);
}

void Imgproc::GaussianBlurAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<ImgprocBindings::GaussianBlur>("Imgproc", "GaussianBlur", info);
}

void Imgproc::MedianBlur(const Napi::CallbackInfo& info) {
  FF::syncBinding<ImgprocBindings::MedianBlur>("Imgproc", "MedianBlur", info);
}

void Imgproc::MedianBlurAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<ImgprocBindings::MedianBlur>("Imgproc", "MedianBlur", info);
}

void Imgproc::Accumulate(const Napi::CallbackInfo& info) {
  FF::syncBinding<ImgprocBindings::Accumulate>("Imgproc", "Accumulate", info);
}

void Imgproc::AccumulateAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<ImgprocBindings::Accumulate>("Imgproc", "Accumulate", info);
}

void Imgproc::AccumulateProduct(const Napi::CallbackInfo& info) {
  FF::syncBinding<ImgprocBindings::AccumulateProduct>("Imgproc", "AccumulateProduct", info);
}

void Imgproc::AccumulateProductAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<ImgprocBindings::AccumulateProduct>("Imgproc", "AccumulateProduct", info);
}

void Imgproc::AccumulateSquare(const Napi::CallbackInfo& info) {
  FF::syncBinding<ImgprocBindings::AccumulateSquare>("Imgproc", "AccumulateSquare", info);
}

void Imgproc::AccumulateSquareAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<ImgprocBindings::AccumulateSquare>("Imgproc", "AccumulateSquare", info);
}

void Imgproc::AccumulateWeighted(const Napi::CallbackInfo& info) {
  FF::syncBinding<ImgprocBindings::AccumulateWeighted>("Imgproc", "AccumulateWeighted", info);
}

void Imgproc::AccumulateWeightedAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<ImgprocBindings::AccumulateWeighted>("Imgproc", "AccumulateWeighted", info);
}

void Imgproc::CalcHist(const Napi::CallbackInfo& info) {
  FF::syncBinding<ImgprocBindings::CalcHist>("Imgproc", "CalcHist", info);
}

void Imgproc::CalcHistAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<ImgprocBindings::CalcHist>("Imgproc", "CalcHist", info);
}

#endif