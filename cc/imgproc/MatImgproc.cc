#include "opencv_modules.h"

#ifdef HAVE_OPENCV_IMGPROC

#include "MatImgproc.h"
#include "MatImgprocBindings.h"
#include "imgprocBindings.h"

void MatImgproc::Init(Napi::Object exports) {
  Napi::Env env = exports.Env();
  InstanceMethod("rescale", &Rescale),
  InstanceMethod("rescaleAsync", &RescaleAsync),
  InstanceMethod("resize", &Resize),
  InstanceMethod("resizeAsync", &ResizeAsync),
  InstanceMethod("resizeToMax", &ResizeToMax),
  InstanceMethod("resizeToMaxAsync", &ResizeToMaxAsync),
  InstanceMethod("cvtColor", &CvtColor),
  InstanceMethod("cvtColorAsync", &CvtColorAsync),
  InstanceMethod("bgrToGray", &BgrToGray),
  InstanceMethod("bgrToGrayAsync", &BgrToGrayAsync),
  InstanceMethod("threshold", &Threshold),
  InstanceMethod("thresholdAsync", &ThresholdAsync),
  InstanceMethod("adaptiveThreshold", &AdaptiveThreshold),
  InstanceMethod("adaptiveThresholdAsync", &AdaptiveThresholdAsync),
  InstanceMethod("inRange", &InRange),
  InstanceMethod("inRangeAsync", &InRangeAsync),
  InstanceMethod("warpAffine", &WarpAffine),
  InstanceMethod("warpAffineAsync", &WarpAffineAsync),
  InstanceMethod("warpPerspective", &WarpPerspective),
  InstanceMethod("warpPerspectiveAsync", &WarpPerspectiveAsync),
  InstanceMethod("dilate", &Dilate),
  InstanceMethod("dilateAsync", &DilateAsync),
  InstanceMethod("erode", &Erode),
  InstanceMethod("erodeAsync", &ErodeAsync),
  InstanceMethod("morphologyEx", &MorphologyEx),
  InstanceMethod("morphologyExAsync", &MorphologyExAsync),
  InstanceMethod("distanceTransform", &DistanceTransform),
  InstanceMethod("distanceTransformAsync", &DistanceTransformAsync),
  InstanceMethod("distanceTransformWithLabels", &DistanceTransformWithLabels),
  InstanceMethod("distanceTransformWithLabelsAsync", &DistanceTransformWithLabelsAsync),
  InstanceMethod("connectedComponents", &ConnectedComponents),
  InstanceMethod("connectedComponentsAsync", &ConnectedComponentsAsync),
  InstanceMethod("connectedComponentsWithStats", &ConnectedComponentsWithStats),
  InstanceMethod("connectedComponentsWithStatsAsync", &ConnectedComponentsWithStatsAsync),
  InstanceMethod("grabCut", &GrabCut),
  InstanceMethod("grabCutAsync", &GrabCutAsync),
  InstanceMethod("watershed", &Watershed),
  InstanceMethod("watershedAsync", &WatershedAsync),
  InstanceMethod("moments", &_Moments),
  InstanceMethod("momentsAsync", &_MomentsAsync),
  InstanceMethod("findContours", &FindContours),
  InstanceMethod("findContoursAsync", &FindContoursAsync),
  InstanceMethod("drawContours", &DrawContours),
  InstanceMethod("drawContoursAsync", &DrawContoursAsync),
  InstanceMethod("drawLine", &DrawLine),
  InstanceMethod("drawArrowedLine", &DrawArrowedLine),
  InstanceMethod("drawCircle", &DrawCircle),
  InstanceMethod("drawRectangle", &DrawRectangle),
  InstanceMethod("drawEllipse", &DrawEllipse),
  InstanceMethod("drawPolylines", &DrawPolylines),
  InstanceMethod("drawFillPoly", &DrawFillPoly),
  InstanceMethod("drawFillConvexPoly", &DrawFillConvexPoly),
  InstanceMethod("putText", &PutText),
  InstanceMethod("putTextAsync", &PutTextAsync),
  InstanceMethod("matchTemplate", &MatchTemplate),
  InstanceMethod("matchTemplateAsync", &MatchTemplateAsync),
  InstanceMethod("canny", &Canny),
  InstanceMethod("cannyAsync", &CannyAsync),
  InstanceMethod("sobel", &Sobel),
  InstanceMethod("sobelAsync", &SobelAsync),
  InstanceMethod("scharr", &Scharr),
  InstanceMethod("scharrAsync", &ScharrAsync),
  InstanceMethod("laplacian", &Laplacian),
  InstanceMethod("laplacianAsync", &LaplacianAsync),
  InstanceMethod("pyrDown", &PyrDown),
  InstanceMethod("pyrDownAsync", &PyrDownAsync),
  InstanceMethod("pyrUp", &PyrUp),
  InstanceMethod("pyrUpAsync", &PyrUpAsync),
  InstanceMethod("buildPyramid", &BuildPyramid),
  InstanceMethod("buildPyramidAsync", &BuildPyramidAsync),
  InstanceMethod("houghLines", &HoughLines),
  InstanceMethod("houghLinesAsync", &HoughLinesAsync),
  InstanceMethod("houghLinesP", &HoughLinesP),
  InstanceMethod("houghLinesPAsync", &HoughLinesPAsync),
  InstanceMethod("houghCircles", &HoughCircles),
  InstanceMethod("houghCirclesAsync", &HoughCirclesAsync),
  InstanceMethod("equalizeHist", &EqualizeHist),
  InstanceMethod("equalizeHistAsync", &EqualizeHistAsync),
  InstanceMethod("compareHist", &CompareHist),
  InstanceMethod("compareHistAsync", &CompareHistAsync),
  InstanceMethod("floodFill", &FloodFill),
  InstanceMethod("floodFillAsync", &FloodFillAsync),
  InstanceMethod("bilateralFilter", &BilateralFilter),
  InstanceMethod("bilateralFilterAsync", &BilateralFilterAsync),
  InstanceMethod("boxFilter", &BoxFilter),
  InstanceMethod("boxFilterAsync", &BoxFilterAsync),
  InstanceMethod("sqrBoxFilter", &SqrBoxFilter),
  InstanceMethod("sqrBoxFilterAsync", &SqrBoxFilterAsync),
  InstanceMethod("filter2D", &Filter2D),
  InstanceMethod("filter2DAsync", &Filter2DAsync),
  InstanceMethod("sepFilter2D", &SepFilter2D),
  InstanceMethod("sepFilter2DAsync", &SepFilter2DAsync),
  InstanceMethod("cornerHarris", &CornerHarris),
  InstanceMethod("cornerHarrisAsync", &CornerHarrisAsync),
  InstanceMethod("cornerSubPix", &CornerSubPix),
  InstanceMethod("cornerSubPixAsync", &CornerSubPixAsync),
  InstanceMethod("cornerMinEigenVal", &CornerMinEigenVal),
  InstanceMethod("cornerMinEigenValAsync", &CornerMinEigenValAsync),
  InstanceMethod("cornerEigenValsAndVecs", &CornerEigenValsAndVecs),
  InstanceMethod("cornerEigenValsAndVecsAsync", &CornerEigenValsAndVecsAsync),
  InstanceMethod("integral", &Integral),
  InstanceMethod("integralAsync", &IntegralAsync),
#if CV_VERSION_LOWER_THAN(4, 0, 0)
  InstanceMethod("undistort", &Undistort),
  InstanceMethod("undistortAsync", &UndistortAsync),
#endif
  InstanceMethod("goodFeaturesToTrack", &GoodFeaturesToTrack),
  InstanceMethod("goodFeaturesToTrackAsync", &GoodFeaturesToTrackAsync),
  InstanceMethod("blur", &Blur),
  InstanceMethod("blurAsync", &BlurAsync),
  InstanceMethod("gaussianBlur", &GaussianBlur),
  InstanceMethod("gaussianBlurAsync", &GaussianBlurAsync),
  InstanceMethod("medianBlur", &MedianBlur),
  InstanceMethod("medianBlurAsync", &MedianBlurAsync),
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

Napi::Value MatImgproc::_Moments(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatImgprocBindings::MomentsWorker>(Mat::unwrapSelf(info)),
      "Mat::Moments",
      info);
}

Napi::Value MatImgproc::_MomentsAsync(const Napi::CallbackInfo& info) {
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