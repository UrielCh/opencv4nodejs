#include "opencv_modules.h"

#ifdef HAVE_OPENCV_IMGPROC

#include "MatImgproc.h"
#include "MatImgprocBindings.h"
#include "imgprocBindings.h"

void MatImgproc::Init(Napi::FunctionReference ctor) {
  Nan::SetPrototypeMethod(ctor, "rescale", Rescale);
  Nan::SetPrototypeMethod(ctor, "rescaleAsync", RescaleAsync);
  Nan::SetPrototypeMethod(ctor, "resize", Resize);
  Nan::SetPrototypeMethod(ctor, "resizeAsync", ResizeAsync);
  Nan::SetPrototypeMethod(ctor, "resizeToMax", ResizeToMax);
  Nan::SetPrototypeMethod(ctor, "resizeToMaxAsync", ResizeToMaxAsync);
  Nan::SetPrototypeMethod(ctor, "cvtColor", CvtColor);
  Nan::SetPrototypeMethod(ctor, "cvtColorAsync", CvtColorAsync);
  Nan::SetPrototypeMethod(ctor, "bgrToGray", BgrToGray);
  Nan::SetPrototypeMethod(ctor, "bgrToGrayAsync", BgrToGrayAsync);
  Nan::SetPrototypeMethod(ctor, "threshold", Threshold);
  Nan::SetPrototypeMethod(ctor, "thresholdAsync", ThresholdAsync);
  Nan::SetPrototypeMethod(ctor, "adaptiveThreshold", AdaptiveThreshold);
  Nan::SetPrototypeMethod(ctor, "adaptiveThresholdAsync", AdaptiveThresholdAsync);
  Nan::SetPrototypeMethod(ctor, "inRange", InRange);
  Nan::SetPrototypeMethod(ctor, "inRangeAsync", InRangeAsync);
  Nan::SetPrototypeMethod(ctor, "warpAffine", WarpAffine);
  Nan::SetPrototypeMethod(ctor, "warpAffineAsync", WarpAffineAsync);
  Nan::SetPrototypeMethod(ctor, "warpPerspective", WarpPerspective);
  Nan::SetPrototypeMethod(ctor, "warpPerspectiveAsync", WarpPerspectiveAsync);
  Nan::SetPrototypeMethod(ctor, "dilate", Dilate);
  Nan::SetPrototypeMethod(ctor, "dilateAsync", DilateAsync);
  Nan::SetPrototypeMethod(ctor, "erode", Erode);
  Nan::SetPrototypeMethod(ctor, "erodeAsync", ErodeAsync);
  Nan::SetPrototypeMethod(ctor, "morphologyEx", MorphologyEx);
  Nan::SetPrototypeMethod(ctor, "morphologyExAsync", MorphologyExAsync);
  Nan::SetPrototypeMethod(ctor, "distanceTransform", DistanceTransform);
  Nan::SetPrototypeMethod(ctor, "distanceTransformAsync", DistanceTransformAsync);
  Nan::SetPrototypeMethod(ctor, "distanceTransformWithLabels", DistanceTransformWithLabels);
  Nan::SetPrototypeMethod(ctor, "distanceTransformWithLabelsAsync", DistanceTransformWithLabelsAsync);
  Nan::SetPrototypeMethod(ctor, "connectedComponents", ConnectedComponents);
  Nan::SetPrototypeMethod(ctor, "connectedComponentsAsync", ConnectedComponentsAsync);
  Nan::SetPrototypeMethod(ctor, "connectedComponentsWithStats", ConnectedComponentsWithStats);
  Nan::SetPrototypeMethod(ctor, "connectedComponentsWithStatsAsync", ConnectedComponentsWithStatsAsync);
  Nan::SetPrototypeMethod(ctor, "grabCut", GrabCut);
  Nan::SetPrototypeMethod(ctor, "grabCutAsync", GrabCutAsync);
  Nan::SetPrototypeMethod(ctor, "watershed", Watershed);
  Nan::SetPrototypeMethod(ctor, "watershedAsync", WatershedAsync);
  Nan::SetPrototypeMethod(ctor, "moments", _Moments);
  Nan::SetPrototypeMethod(ctor, "momentsAsync", _MomentsAsync);
  Nan::SetPrototypeMethod(ctor, "findContours", FindContours);
  Nan::SetPrototypeMethod(ctor, "findContoursAsync", FindContoursAsync);
  Nan::SetPrototypeMethod(ctor, "drawContours", DrawContours);
  Nan::SetPrototypeMethod(ctor, "drawContoursAsync", DrawContoursAsync);
  Nan::SetPrototypeMethod(ctor, "drawLine", DrawLine);
  Nan::SetPrototypeMethod(ctor, "drawArrowedLine", DrawArrowedLine);
  Nan::SetPrototypeMethod(ctor, "drawCircle", DrawCircle);
  Nan::SetPrototypeMethod(ctor, "drawRectangle", DrawRectangle);
  Nan::SetPrototypeMethod(ctor, "drawEllipse", DrawEllipse);
  Nan::SetPrototypeMethod(ctor, "drawPolylines", DrawPolylines);
  Nan::SetPrototypeMethod(ctor, "drawFillPoly", DrawFillPoly);
  Nan::SetPrototypeMethod(ctor, "drawFillConvexPoly", DrawFillConvexPoly);
  Nan::SetPrototypeMethod(ctor, "putText", PutText);
  Nan::SetPrototypeMethod(ctor, "putTextAsync", PutTextAsync);
  Nan::SetPrototypeMethod(ctor, "matchTemplate", MatchTemplate);
  Nan::SetPrototypeMethod(ctor, "matchTemplateAsync", MatchTemplateAsync);
  Nan::SetPrototypeMethod(ctor, "canny", Canny);
  Nan::SetPrototypeMethod(ctor, "cannyAsync", CannyAsync);
  Nan::SetPrototypeMethod(ctor, "sobel", Sobel);
  Nan::SetPrototypeMethod(ctor, "sobelAsync", SobelAsync);
  Nan::SetPrototypeMethod(ctor, "scharr", Scharr);
  Nan::SetPrototypeMethod(ctor, "scharrAsync", ScharrAsync);
  Nan::SetPrototypeMethod(ctor, "laplacian", Laplacian);
  Nan::SetPrototypeMethod(ctor, "laplacianAsync", LaplacianAsync);
  Nan::SetPrototypeMethod(ctor, "pyrDown", PyrDown);
  Nan::SetPrototypeMethod(ctor, "pyrDownAsync", PyrDownAsync);
  Nan::SetPrototypeMethod(ctor, "pyrUp", PyrUp);
  Nan::SetPrototypeMethod(ctor, "pyrUpAsync", PyrUpAsync);
  Nan::SetPrototypeMethod(ctor, "buildPyramid", BuildPyramid);
  Nan::SetPrototypeMethod(ctor, "buildPyramidAsync", BuildPyramidAsync);
  Nan::SetPrototypeMethod(ctor, "houghLines", HoughLines);
  Nan::SetPrototypeMethod(ctor, "houghLinesAsync", HoughLinesAsync);
  Nan::SetPrototypeMethod(ctor, "houghLinesP", HoughLinesP);
  Nan::SetPrototypeMethod(ctor, "houghLinesPAsync", HoughLinesPAsync);
  Nan::SetPrototypeMethod(ctor, "houghCircles", HoughCircles);
  Nan::SetPrototypeMethod(ctor, "houghCirclesAsync", HoughCirclesAsync);
  Nan::SetPrototypeMethod(ctor, "equalizeHist", EqualizeHist);
  Nan::SetPrototypeMethod(ctor, "equalizeHistAsync", EqualizeHistAsync);
  Nan::SetPrototypeMethod(ctor, "compareHist", CompareHist);
  Nan::SetPrototypeMethod(ctor, "compareHistAsync", CompareHistAsync);
  Nan::SetPrototypeMethod(ctor, "floodFill", FloodFill);
  Nan::SetPrototypeMethod(ctor, "floodFillAsync", FloodFillAsync);
  Nan::SetPrototypeMethod(ctor, "bilateralFilter", BilateralFilter);
  Nan::SetPrototypeMethod(ctor, "bilateralFilterAsync", BilateralFilterAsync);
  Nan::SetPrototypeMethod(ctor, "boxFilter", BoxFilter);
  Nan::SetPrototypeMethod(ctor, "boxFilterAsync", BoxFilterAsync);
  Nan::SetPrototypeMethod(ctor, "sqrBoxFilter", SqrBoxFilter);
  Nan::SetPrototypeMethod(ctor, "sqrBoxFilterAsync", SqrBoxFilterAsync);
  Nan::SetPrototypeMethod(ctor, "filter2D", Filter2D);
  Nan::SetPrototypeMethod(ctor, "filter2DAsync", Filter2DAsync);
  Nan::SetPrototypeMethod(ctor, "sepFilter2D", SepFilter2D);
  Nan::SetPrototypeMethod(ctor, "sepFilter2DAsync", SepFilter2DAsync);
  Nan::SetPrototypeMethod(ctor, "cornerHarris", CornerHarris);
  Nan::SetPrototypeMethod(ctor, "cornerHarrisAsync", CornerHarrisAsync);
  Nan::SetPrototypeMethod(ctor, "cornerSubPix", CornerSubPix);
  Nan::SetPrototypeMethod(ctor, "cornerSubPixAsync", CornerSubPixAsync);
  Nan::SetPrototypeMethod(ctor, "cornerMinEigenVal", CornerMinEigenVal);
  Nan::SetPrototypeMethod(ctor, "cornerMinEigenValAsync", CornerMinEigenValAsync);
  Nan::SetPrototypeMethod(ctor, "cornerEigenValsAndVecs", CornerEigenValsAndVecs);
  Nan::SetPrototypeMethod(ctor, "cornerEigenValsAndVecsAsync", CornerEigenValsAndVecsAsync);
  Nan::SetPrototypeMethod(ctor, "integral", Integral);
  Nan::SetPrototypeMethod(ctor, "integralAsync", IntegralAsync);
#if CV_VERSION_LOWER_THAN(4, 0, 0)
  Nan::SetPrototypeMethod(ctor, "undistort", Undistort);
  Nan::SetPrototypeMethod(ctor, "undistortAsync", UndistortAsync);
#endif
  Nan::SetPrototypeMethod(ctor, "goodFeaturesToTrack", GoodFeaturesToTrack);
  Nan::SetPrototypeMethod(ctor, "goodFeaturesToTrackAsync", GoodFeaturesToTrackAsync);
  Nan::SetPrototypeMethod(ctor, "blur", Blur);
  Nan::SetPrototypeMethod(ctor, "blurAsync", BlurAsync);
  Nan::SetPrototypeMethod(ctor, "gaussianBlur", GaussianBlur);
  Nan::SetPrototypeMethod(ctor, "gaussianBlurAsync", GaussianBlurAsync);
  Nan::SetPrototypeMethod(ctor, "medianBlur", MedianBlur);
  Nan::SetPrototypeMethod(ctor, "medianBlurAsync", MedianBlurAsync);
};

void MatImgproc::DrawContours(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::DrawContoursWorker>(Mat::unwrapSelf(info)),
      "Mat::DrawContours",
      info);
}

void MatImgproc::DrawContoursAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::DrawContoursWorker>(Mat::unwrapSelf(info)),
      "Mat::DrawContoursAsync",
      info);
}

void MatImgproc::Rescale(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::RescaleWorker>(Mat::unwrapSelf(info)),
      "Mat::Rescale",
      info);
}

void MatImgproc::RescaleAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::RescaleWorker>(Mat::unwrapSelf(info)),
      "Mat::RescaleAsync",
      info);
}

void MatImgproc::Resize(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::ResizeWorker>(Mat::unwrapSelf(info)),
      "Mat::Resize",
      info);
}

void MatImgproc::ResizeAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::ResizeWorker>(Mat::unwrapSelf(info)),
      "Mat::ResizeAsync",
      info);
}

void MatImgproc::ResizeToMax(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::ResizeToMaxWorker>(Mat::unwrapSelf(info)),
      "Mat::ResizeToMax",
      info);
}

void MatImgproc::ResizeToMaxAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::ResizeToMaxWorker>(Mat::unwrapSelf(info)),
      "Mat::ResizeToMaxAsync",
      info);
}

void MatImgproc::Threshold(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::ThresholdWorker>(Mat::unwrapSelf(info)),
      "Mat::Threshold",
      info);
}

void MatImgproc::ThresholdAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::ThresholdWorker>(Mat::unwrapSelf(info)),
      "Mat::ThresholdAsync",
      info);
}

void MatImgproc::AdaptiveThreshold(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::AdaptiveThresholdWorker>(Mat::unwrapSelf(info)),
      "Mat::AdaptiveThreshold",
      info);
}

void MatImgproc::AdaptiveThresholdAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::AdaptiveThresholdWorker>(Mat::unwrapSelf(info)),
      "Mat::AdaptiveThresholdAsync",
      info);
}

void MatImgproc::InRange(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::InRangeWorker>(Mat::unwrapSelf(info)),
      "Mat::InRange",
      info);
}

void MatImgproc::InRangeAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::InRangeWorker>(Mat::unwrapSelf(info)),
      "Mat::InRangeAsync",
      info);
}

void MatImgproc::CvtColor(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::CvtColorWorker>(Mat::unwrapSelf(info)),
      "Mat::CvtColor",
      info);
}

void MatImgproc::CvtColorAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::CvtColorWorker>(Mat::unwrapSelf(info)),
      "Mat::CvtColorAsync",
      info);
}

void MatImgproc::BgrToGray(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::BgrToGrayWorker>(Mat::unwrapSelf(info)),
      "Mat::BgrToGray",
      info);
}

void MatImgproc::BgrToGrayAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::BgrToGrayWorker>(Mat::unwrapSelf(info)),
      "Mat::BgrToGrayAsync",
      info);
}

void MatImgproc::WarpAffine(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::WarpAffineWorker>(Mat::unwrapSelf(info)),
      "Mat::WarpAffine",
      info);
}

void MatImgproc::WarpAffineAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::WarpAffineWorker>(Mat::unwrapSelf(info)),
      "Mat::WarpAffineAsync",
      info);
}

void MatImgproc::WarpPerspective(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::WarpPerspectiveWorker>(Mat::unwrapSelf(info)),
      "Mat::WarpPerspective",
      info);
}

void MatImgproc::WarpPerspectiveAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::WarpPerspectiveWorker>(Mat::unwrapSelf(info)),
      "Mat::WarpPerspectiveAsync",
      info);
}

void MatImgproc::Erode(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::ErodeWorker>(Mat::unwrapSelf(info)),
      "Mat::Erode",
      info);
}

void MatImgproc::ErodeAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::ErodeWorker>(Mat::unwrapSelf(info)),
      "Mat::ErodeAsync",
      info);
}

void MatImgproc::Dilate(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::DilateWorker>(Mat::unwrapSelf(info)),
      "Mat::Dilate",
      info);
}

void MatImgproc::DilateAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::DilateWorker>(Mat::unwrapSelf(info)),
      "Mat::DilateAsync",
      info);
}

void MatImgproc::MorphologyEx(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::MorphologyExWorker>(Mat::unwrapSelf(info)),
      "Mat::MorphologyEx",
      info);
}

void MatImgproc::MorphologyExAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::MorphologyExWorker>(Mat::unwrapSelf(info)),
      "Mat::MorphologyExAsync",
      info);
}

void MatImgproc::DistanceTransform(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::DistanceTransformWorker>(Mat::unwrapSelf(info)),
      "Mat::DistanceTransform",
      info);
}

void MatImgproc::DistanceTransformAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::DistanceTransformWorker>(Mat::unwrapSelf(info)),
      "Mat::DistanceTransformAsync",
      info);
}

void MatImgproc::DistanceTransformWithLabels(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::DistanceTransformWithLabelsWorker>(Mat::unwrapSelf(info)),
      "Mat::DistanceTransformWithLabels",
      info);
}

void MatImgproc::DistanceTransformWithLabelsAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::DistanceTransformWithLabelsWorker>(Mat::unwrapSelf(info)),
      "Mat::DistanceTransformWithLabelsAsync",
      info);
}

void MatImgproc::ConnectedComponents(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::ConnectedComponentsWorker>(Mat::unwrapSelf(info)),
      "Mat::ConnectedComponents",
      info);
}

void MatImgproc::ConnectedComponentsAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::ConnectedComponentsWorker>(Mat::unwrapSelf(info)),
      "Mat::ConnectedComponentsAsync",
      info);
}

void MatImgproc::ConnectedComponentsWithStats(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::ConnectedComponentsWithStatsWorker>(Mat::unwrapSelf(info)),
      "Mat::ConnectedComponentsWithStats",
      info);
}

void MatImgproc::ConnectedComponentsWithStatsAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::ConnectedComponentsWithStatsWorker>(Mat::unwrapSelf(info)),
      "Mat::ConnectedComponentsWithStatsAsync",
      info);
}

void MatImgproc::GrabCut(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::GrabCutWorker>(Mat::unwrapSelf(info)),
      "Mat::GrabCut",
      info);
}

void MatImgproc::GrabCutAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::GrabCutWorker>(Mat::unwrapSelf(info)),
      "Mat::GrabCutAsync",
      info);
}

void MatImgproc::Watershed(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::WatershedWorker>(Mat::unwrapSelf(info)),
      "Mat::Watershed",
      info);
}

void MatImgproc::WatershedAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::WatershedWorker>(Mat::unwrapSelf(info)),
      "Mat::WatershedAsync",
      info);
}

NAN_METHOD(MatImgproc::_Moments) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::MomentsWorker>(Mat::unwrapSelf(info)),
      "Mat::Moments",
      info);
}

NAN_METHOD(MatImgproc::_MomentsAsync) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::MomentsWorker>(Mat::unwrapSelf(info)),
      "Mat::MomentsAsync",
      info);
}

void MatImgproc::FindContours(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::FindContoursWorker>(Mat::unwrapSelf(info)),
      "Mat::FindContours",
      info);
}

void MatImgproc::FindContoursAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::FindContoursWorker>(Mat::unwrapSelf(info)),
      "Mat::FindContoursAsync",
      info);
}

void MatImgproc::DrawLine(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::DrawLineWorker>(Mat::unwrapSelf(info)),
      "Mat::DrawLine",
      info);
}

void MatImgproc::DrawArrowedLine(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::DrawArrowedLineWorker>(Mat::unwrapSelf(info)),
      "Mat::DrawArrowedLine",
      info);
}

void MatImgproc::DrawRectangle(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::DrawRectangleWorker>(Mat::unwrapSelf(info)),
      "Mat::DrawRectangle",
      info);
}

void MatImgproc::DrawCircle(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::DrawCircleWorker>(Mat::unwrapSelf(info)),
      "Mat::DrawCircle",
      info);
}

void MatImgproc::DrawEllipse(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::DrawEllipseWorker>(Mat::unwrapSelf(info)),
      "Mat::DrawEllipse",
      info);
}

void MatImgproc::DrawPolylines(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::DrawPolylinesWorker>(Mat::unwrapSelf(info)),
      "Mat::DrawPolylines",
      info);
}

void MatImgproc::DrawFillPoly(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::DrawFillPolyWorker>(Mat::unwrapSelf(info)),
      "Mat::DrawFillPoly",
      info);
}

void MatImgproc::DrawFillConvexPoly(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::DrawFillConvexPolyWorker>(Mat::unwrapSelf(info)),
      "Mat::DrawFillConvexPoly",
      info);
}

void MatImgproc::PutText(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::PutTextWorker>(Mat::unwrapSelf(info)),
      "Mat::PutText",
      info);
}

void MatImgproc::PutTextAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::PutTextWorker>(Mat::unwrapSelf(info)),
      "Mat::PutTextAsync",
      info);
}

void MatImgproc::MatchTemplate(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::MatchTemplateWorker>(Mat::unwrapSelf(info)),
      "Mat::MatchTemplate",
      info);
}

void MatImgproc::MatchTemplateAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::MatchTemplateWorker>(Mat::unwrapSelf(info)),
      "Mat::MatchTemplateAsync",
      info);
}

void MatImgproc::Canny(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::CannyWorker>(Mat::unwrapSelf(info)),
      "Mat::Canny",
      info);
}

void MatImgproc::CannyAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::CannyWorker>(Mat::unwrapSelf(info)),
      "Mat::CannyAsync",
      info);
}

void MatImgproc::Sobel(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::SobelWorker>(Mat::unwrapSelf(info), true),
      "Mat::Sobel",
      info);
}

void MatImgproc::SobelAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::SobelWorker>(Mat::unwrapSelf(info), true),
      "Mat::SobelAsync",
      info);
}

void MatImgproc::Scharr(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::ScharrWorker>(Mat::unwrapSelf(info), false),
      "Mat::Scharr",
      info);
}

void MatImgproc::ScharrAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::ScharrWorker>(Mat::unwrapSelf(info), false),
      "Mat::ScharrAsync",
      info);
}

void MatImgproc::Laplacian(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::LaplacianWorker>(Mat::unwrapSelf(info)),
      "Mat::Laplacian",
      info);
}

void MatImgproc::LaplacianAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::LaplacianWorker>(Mat::unwrapSelf(info)),
      "Mat::LaplacianAsync",
      info);
}

void MatImgproc::PyrDown(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::PyrWorker>(Mat::unwrapSelf(info)),
      "Mat::PyrDown",
      info);
}

void MatImgproc::PyrDownAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::PyrWorker>(Mat::unwrapSelf(info)),
      "Mat::PyrDownAsync",
      info);
}

void MatImgproc::PyrUp(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::PyrWorker>(Mat::unwrapSelf(info), true),
      "Mat::PyrUp",
      info);
}

void MatImgproc::PyrUpAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::PyrWorker>(Mat::unwrapSelf(info), true),
      "Mat::PyrUpAsync",
      info);
}

void MatImgproc::BuildPyramid(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::BuildPyramidWorker>(Mat::unwrapSelf(info)),
      "Mat::BuildPyramid",
      info);
}

void MatImgproc::BuildPyramidAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::BuildPyramidWorker>(Mat::unwrapSelf(info)),
      "Mat::BuildPyramidAsync",
      info);
}

void MatImgproc::HoughLines(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::HoughLinesWorker>(Mat::unwrapSelf(info)),
      "Mat::HoughLines",
      info);
}

void MatImgproc::HoughLinesAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::HoughLinesWorker>(Mat::unwrapSelf(info)),
      "Mat::HoughLinesAsync",
      info);
}

void MatImgproc::HoughLinesP(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::HoughLinesPWorker>(Mat::unwrapSelf(info)),
      "Mat::HoughLinesP",
      info);
}

void MatImgproc::HoughLinesPAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::HoughLinesPWorker>(Mat::unwrapSelf(info)),
      "Mat::HoughLinesPAsync",
      info);
}

void MatImgproc::HoughCircles(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::HoughCirclesWorker>(Mat::unwrapSelf(info)),
      "Mat::HoughCircles",
      info);
}

void MatImgproc::HoughCirclesAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::HoughCirclesWorker>(Mat::unwrapSelf(info)),
      "Mat::HoughCirclesAsync",
      info);
}

void MatImgproc::EqualizeHist(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::EqualizeHistWorker>(Mat::unwrapSelf(info)),
      "Mat::EqualizeHist",
      info);
}

void MatImgproc::EqualizeHistAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::EqualizeHistWorker>(Mat::unwrapSelf(info)),
      "Mat::EqualizeHistAsync",
      info);
}

void MatImgproc::CompareHist(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::CompareHistWorker>(Mat::unwrapSelf(info)),
      "Mat::CompareHist",
      info);
}

void MatImgproc::CompareHistAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::CompareHistWorker>(Mat::unwrapSelf(info)),
      "Mat::CompareHistAsync",
      info);
}

void MatImgproc::FloodFill(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::FloodFillWorker>(Mat::unwrapSelf(info)),
      "Mat::FloodFill",
      info);
}

void MatImgproc::FloodFillAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::FloodFillWorker>(Mat::unwrapSelf(info)),
      "Mat::FloodFillAsync",
      info);
}

void MatImgproc::BilateralFilter(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::BilateralFilterWorker>(Mat::unwrapSelf(info)),
      "Mat::BilateralFilter",
      info);
}

void MatImgproc::BilateralFilterAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::BilateralFilterWorker>(Mat::unwrapSelf(info)),
      "Mat::BilateralFilterAsync",
      info);
}

void MatImgproc::BoxFilter(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::BoxFilterWorker>(Mat::unwrapSelf(info)),
      "Mat::BoxFilter",
      info);
}

void MatImgproc::BoxFilterAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::BoxFilterWorker>(Mat::unwrapSelf(info)),
      "Mat::BoxFilterAsync",
      info);
}

void MatImgproc::SqrBoxFilter(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::SqrBoxFilterWorker>(Mat::unwrapSelf(info)),
      "Mat::SqrBoxFilter",
      info);
}

void MatImgproc::SqrBoxFilterAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::SqrBoxFilterWorker>(Mat::unwrapSelf(info)),
      "Mat::SqrBoxFilterAsync",
      info);
}

void MatImgproc::Filter2D(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::Filter2DWorker>(Mat::unwrapSelf(info)),
      "Mat::Filter2D",
      info);
}

void MatImgproc::Filter2DAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::Filter2DWorker>(Mat::unwrapSelf(info)),
      "Mat::Filter2DAsync",
      info);
}

void MatImgproc::SepFilter2D(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::SepFilter2DWorker>(Mat::unwrapSelf(info)),
      "Mat::SepFilter2D",
      info);
}

void MatImgproc::SepFilter2DAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::SepFilter2DWorker>(Mat::unwrapSelf(info)),
      "Mat::SepFilter2DAsync",
      info);
}

void MatImgproc::CornerHarris(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::CornerHarrisWorker>(Mat::unwrapSelf(info)),
      "Mat::CornerHarris",
      info);
}

void MatImgproc::CornerHarrisAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::CornerHarrisWorker>(Mat::unwrapSelf(info)),
      "Mat::CornerHarrisAsync",
      info);
}

void MatImgproc::CornerSubPix(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::CornerSubPixWorker>(Mat::unwrapSelf(info)),
      "Mat::CornerSubPix",
      info);
}

void MatImgproc::CornerSubPixAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::CornerSubPixWorker>(Mat::unwrapSelf(info)),
      "Mat::CornerSubPixAsync",
      info);
}

void MatImgproc::CornerMinEigenVal(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::CornerMinEigenValWorker>(Mat::unwrapSelf(info)),
      "Mat::CornerMinEigenVal",
      info);
}

void MatImgproc::CornerMinEigenValAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::CornerMinEigenValWorker>(Mat::unwrapSelf(info)),
      "Mat::CornerMinEigenValAsync",
      info);
}

void MatImgproc::CornerEigenValsAndVecs(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::CornerEigenValsAndVecsWorker>(Mat::unwrapSelf(info)),
      "Mat::CornerEigenValsAndVecs",
      info);
}

void MatImgproc::CornerEigenValsAndVecsAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::CornerEigenValsAndVecsWorker>(Mat::unwrapSelf(info)),
      "Mat::CornerEigenValsAndVecsAsync",
      info);
}

void MatImgproc::Integral(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::IntegralWorker>(Mat::unwrapSelf(info)),
      "Mat::Integral",
      info);
}

void MatImgproc::IntegralAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatImgprocBindings::IntegralWorker>(Mat::unwrapSelf(info)),
      "Mat::IntegralAsync",
      info);
}

#if CV_VERSION_LOWER_THAN(4, 0, 0)
void MatImgproc::Undistort(const Napi::CallbackInfo& info) {
  Mat::syncBinding<MatImgprocBindings::Undistort>("Undistort", info);
}

void MatImgproc::UndistortAsync(const Napi::CallbackInfo& info) {
  Mat::asyncBinding<MatImgprocBindings::Undistort>("Undistort", info);
}
#endif

void MatImgproc::GoodFeaturesToTrack(const Napi::CallbackInfo& info) {
  Mat::syncBinding<ImgprocBindings::GoodFeaturesToTrack>("GoodFeaturesToTrack", info);
}

void MatImgproc::GoodFeaturesToTrackAsync(const Napi::CallbackInfo& info) {
  Mat::asyncBinding<ImgprocBindings::GoodFeaturesToTrack>("GoodFeaturesToTrack", info);
}

void MatImgproc::Blur(const Napi::CallbackInfo& info) {
  Mat::syncBinding<ImgprocBindings::Blur>("Blur", info);
}

void MatImgproc::BlurAsync(const Napi::CallbackInfo& info) {
  Mat::asyncBinding<ImgprocBindings::Blur>("Blur", info);
}

void MatImgproc::GaussianBlur(const Napi::CallbackInfo& info) {
  Mat::syncBinding<ImgprocBindings::GaussianBlur>("GaussianBlur", info);
}

void MatImgproc::GaussianBlurAsync(const Napi::CallbackInfo& info) {
  Mat::asyncBinding<ImgprocBindings::GaussianBlur>("GaussianBlur", info);
}

void MatImgproc::MedianBlur(const Napi::CallbackInfo& info) {
  Mat::syncBinding<ImgprocBindings::MedianBlur>("MedianBlur", info);
}

void MatImgproc::MedianBlurAsync(const Napi::CallbackInfo& info) {
  Mat::asyncBinding<ImgprocBindings::MedianBlur>("MedianBlur", info);
}

#endif