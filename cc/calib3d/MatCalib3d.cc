#include "opencv_modules.h"

#ifdef HAVE_OPENCV_CALIB3D

#include "MatCalib3d.h"
#include "MatCalib3dBindings.h"

void MatCalib3d::Init(Napi::FunctionReference ctor) {
  Nan::SetPrototypeMethod(ctor, "rodrigues", Rodrigues);
  Nan::SetPrototypeMethod(ctor, "rodriguesAsync", RodriguesAsync);
  Nan::SetPrototypeMethod(ctor, "rqDecomp3x3", RQDecomp3x3);
  Nan::SetPrototypeMethod(ctor, "rqDecomp3x3Async", RQDecomp3x3Async);
  Nan::SetPrototypeMethod(ctor, "decomposeProjectionMatrix", DecomposeProjectionMatrix);
  Nan::SetPrototypeMethod(ctor, "decomposeProjectionMatrixAsync", DecomposeProjectionMatrixAsync);
  Nan::SetPrototypeMethod(ctor, "matMulDeriv", MatMulDeriv);
  Nan::SetPrototypeMethod(ctor, "matMulDerivAsync", MatMulDerivAsync);
  Nan::SetPrototypeMethod(ctor, "findChessboardCorners", FindChessboardCorners);
  Nan::SetPrototypeMethod(ctor, "findChessboardCornersAsync", FindChessboardCornersAsync);
  Nan::SetPrototypeMethod(ctor, "drawChessboardCorners", DrawChessboardCorners);
  Nan::SetPrototypeMethod(ctor, "drawChessboardCornersAsync", DrawChessboardCornersAsync);
  Nan::SetPrototypeMethod(ctor, "find4QuadCornerSubpix", Find4QuadCornerSubpix);
  Nan::SetPrototypeMethod(ctor, "find4QuadCornerSubpixAsync", Find4QuadCornerSubpixAsync);
  Nan::SetPrototypeMethod(ctor, "calibrationMatrixValues", CalibrationMatrixValues);
  Nan::SetPrototypeMethod(ctor, "calibrationMatrixValuesAsync", CalibrationMatrixValuesAsync);
  Nan::SetPrototypeMethod(ctor, "stereoRectify", StereoRectify);
  Nan::SetPrototypeMethod(ctor, "stereoRectifyAsync", StereoRectifyAsync);
  Nan::SetPrototypeMethod(ctor, "rectify3Collinear", Rectify3Collinear);
  Nan::SetPrototypeMethod(ctor, "rectify3CollinearAsync", Rectify3CollinearAsync);
  Nan::SetPrototypeMethod(ctor, "getOptimalNewCameraMatrix", GetOptimalNewCameraMatrix);
  Nan::SetPrototypeMethod(ctor, "getOptimalNewCameraMatrixAsync", GetOptimalNewCameraMatrixAsync);
  Nan::SetPrototypeMethod(ctor, "decomposeEssentialMat", DecomposeEssentialMat);
  Nan::SetPrototypeMethod(ctor, "decomposeEssentialMatAsync", DecomposeEssentialMatAsync);
  Nan::SetPrototypeMethod(ctor, "triangulatePoints", TriangulatePoints);
  Nan::SetPrototypeMethod(ctor, "triangulatePointsAsync", TriangulatePointsAsync);
  Nan::SetPrototypeMethod(ctor, "correctMatches", CorrectMatches);
  Nan::SetPrototypeMethod(ctor, "correctMatchesAsync", CorrectMatchesAsync);
  Nan::SetPrototypeMethod(ctor, "filterSpeckles", FilterSpeckles);
  Nan::SetPrototypeMethod(ctor, "filterSpecklesAsync", FilterSpecklesAsync);
  Nan::SetPrototypeMethod(ctor, "validateDisparity", ValidateDisparity);
  Nan::SetPrototypeMethod(ctor, "validateDisparityAsync", ValidateDisparityAsync);
  Nan::SetPrototypeMethod(ctor, "reprojectImageTo3D", ReprojectImageTo3D);
  Nan::SetPrototypeMethod(ctor, "reprojectImageTo3DAsync", ReprojectImageTo3DAsync);
  Nan::SetPrototypeMethod(ctor, "decomposeHomographyMat", DecomposeHomographyMat);
  Nan::SetPrototypeMethod(ctor, "decomposeHomographyMatAsync", DecomposeHomographyMatAsync);
#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
  Nan::SetPrototypeMethod(ctor, "findEssentialMat", FindEssentialMat);
  Nan::SetPrototypeMethod(ctor, "findEssentialMatAsync", FindEssentialMatAsync);
  Nan::SetPrototypeMethod(ctor, "recoverPose", RecoverPose);
  Nan::SetPrototypeMethod(ctor, "recoverPoseAsync", RecoverPoseAsync);
#endif
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  Nan::SetPrototypeMethod(ctor, "undistort", Undistort);
  Nan::SetPrototypeMethod(ctor, "undistortAsync", UndistortAsync);
#endif
};

void MatCalib3d::Rodrigues(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::RodriguesWorker>(Mat::unwrapSelf(info)),
      "Mat::Rodrigues",
      info);
}

void MatCalib3d::RodriguesAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::RodriguesWorker>(Mat::unwrapSelf(info)),
      "Mat::RodriguesAsync",
      info);
}

void MatCalib3d::RQDecomp3x3(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::RQDecomp3x3Worker>(Mat::unwrapSelf(info)),
      "Mat::RQDecomp3x3",
      info);
}

void MatCalib3d::RQDecomp3x3Async(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::RQDecomp3x3Worker>(Mat::unwrapSelf(info)),
      "Mat::RQDecomp3x3Async",
      info);
}

void MatCalib3d::DecomposeProjectionMatrix(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::DecomposeProjectionMatrixWorker>(Mat::unwrapSelf(info)),
      "Mat::DecomposeProjectionMatrix",
      info);
}

void MatCalib3d::DecomposeProjectionMatrixAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::DecomposeProjectionMatrixWorker>(Mat::unwrapSelf(info)),
      "Mat::DecomposeProjectionMatrixAsync",
      info);
}

void MatCalib3d::MatMulDeriv(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::MatMulDerivWorker>(Mat::unwrapSelf(info)),
      "Mat::MatMulDeriv",
      info);
}

void MatCalib3d::MatMulDerivAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::MatMulDerivWorker>(Mat::unwrapSelf(info)),
      "Mat::MatMulDerivAsync",
      info);
}

void MatCalib3d::FindChessboardCorners(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::FindChessboardCornersWorker>(Mat::unwrapSelf(info)),
      "Mat::FindChessboardCorners",
      info);
}

void MatCalib3d::FindChessboardCornersAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::FindChessboardCornersWorker>(Mat::unwrapSelf(info)),
      "Mat::FindChessboardCornersAsync",
      info);
}

void MatCalib3d::DrawChessboardCorners(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::DrawChessboardCornersWorker>(Mat::unwrapSelf(info)),
      "Mat::DrawChessboardCorners",
      info);
}

void MatCalib3d::DrawChessboardCornersAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::DrawChessboardCornersWorker>(Mat::unwrapSelf(info)),
      "Mat::DrawChessboardCornersAsync",
      info);
}

void MatCalib3d::Find4QuadCornerSubpix(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::Find4QuadCornerSubpixWorker>(Mat::unwrapSelf(info)),
      "Mat::Find4QuadCornerSubpix",
      info);
}

void MatCalib3d::Find4QuadCornerSubpixAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::Find4QuadCornerSubpixWorker>(Mat::unwrapSelf(info)),
      "Mat::Find4QuadCornerSubpixAsync",
      info);
}

void MatCalib3d::CalibrationMatrixValues(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::CalibrationMatrixValuesWorker>(Mat::unwrapSelf(info)),
      "Mat::CalibrationMatrixValues",
      info);
}

void MatCalib3d::CalibrationMatrixValuesAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::CalibrationMatrixValuesWorker>(Mat::unwrapSelf(info)),
      "Mat::CalibrationMatrixValuesAsync",
      info);
}

void MatCalib3d::StereoRectify(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::StereoRectifyWorker>(Mat::unwrapSelf(info)),
      "Mat::StereoRectify",
      info);
}

void MatCalib3d::StereoRectifyAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::StereoRectifyWorker>(Mat::unwrapSelf(info)),
      "Mat::StereoRectifyAsync",
      info);
}

void MatCalib3d::Rectify3Collinear(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::Rectify3CollinearWorker>(Mat::unwrapSelf(info)),
      "Mat::Rectify3Collinear",
      info);
}

void MatCalib3d::Rectify3CollinearAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::Rectify3CollinearWorker>(Mat::unwrapSelf(info)),
      "Mat::Rectify3CollinearAsync",
      info);
}

void MatCalib3d::GetOptimalNewCameraMatrix(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::GetOptimalNewCameraMatrixWorker>(Mat::unwrapSelf(info)),
      "Mat::GetOptimalNewCameraMatrix",
      info);
}

void MatCalib3d::GetOptimalNewCameraMatrixAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::GetOptimalNewCameraMatrixWorker>(Mat::unwrapSelf(info)),
      "Mat::GetOptimalNewCameraMatrixAsync",
      info);
}

void MatCalib3d::DecomposeEssentialMat(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::DecomposeEssentialMatWorker>(Mat::unwrapSelf(info)),
      "Mat::DecomposeEssentialMat",
      info);
}

void MatCalib3d::DecomposeEssentialMatAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::DecomposeEssentialMatWorker>(Mat::unwrapSelf(info)),
      "Mat::DecomposeEssentialMatAsync",
      info);
}

void MatCalib3d::TriangulatePoints(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::TriangulatePointsWorker>(Mat::unwrapSelf(info)),
      "Mat::TriangulatePoints",
      info);
}

void MatCalib3d::TriangulatePointsAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::TriangulatePointsWorker>(Mat::unwrapSelf(info)),
      "Mat::TriangulatePointsAsync",
      info);
}

void MatCalib3d::CorrectMatches(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::CorrectMatchesWorker>(Mat::unwrapSelf(info)),
      "Mat::CorrectMatches",
      info);
}

void MatCalib3d::CorrectMatchesAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::CorrectMatchesWorker>(Mat::unwrapSelf(info)),
      "Mat::CorrectMatchesAsync",
      info);
}

void MatCalib3d::FilterSpeckles(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::FilterSpecklesWorker>(Mat::unwrapSelf(info)),
      "Mat::FilterSpeckles",
      info);
}

void MatCalib3d::FilterSpecklesAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::FilterSpecklesWorker>(Mat::unwrapSelf(info)),
      "Mat::FilterSpecklesAsync",
      info);
}

void MatCalib3d::ValidateDisparity(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::ValidateDisparityWorker>(Mat::unwrapSelf(info)),
      "Mat::ValidateDisparity",
      info);
}

void MatCalib3d::ValidateDisparityAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::ValidateDisparityWorker>(Mat::unwrapSelf(info)),
      "Mat::ValidateDisparityAsync",
      info);
}

void MatCalib3d::ReprojectImageTo3D(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::ReprojectImageTo3DWorker>(Mat::unwrapSelf(info)),
      "Mat::ReprojectImageTo3D",
      info);
}

void MatCalib3d::ReprojectImageTo3DAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::ReprojectImageTo3DWorker>(Mat::unwrapSelf(info)),
      "Mat::ReprojectImageTo3DAsync",
      info);
}

void MatCalib3d::DecomposeHomographyMat(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::DecomposeHomographyMatWorker>(Mat::unwrapSelf(info)),
      "Mat::DecomposeHomographyMat",
      info);
}

void MatCalib3d::DecomposeHomographyMatAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::DecomposeHomographyMatWorker>(Mat::unwrapSelf(info)),
      "Mat::DecomposeHomographyMatAsync",
      info);
}

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

void MatCalib3d::FindEssentialMat(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::FindEssentialMatWorker>(Mat::unwrapSelf(info)),
      "Mat::FindEssentialMat",
      info);
}

void MatCalib3d::FindEssentialMatAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::FindEssentialMatWorker>(Mat::unwrapSelf(info)),
      "Mat::FindEssentialMatAsync",
      info);
}

void MatCalib3d::RecoverPose(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<MatCalib3dBindings::RecoverPoseWorker>(Mat::unwrapSelf(info)),
      "Mat::RecoverPose",
      info);
}

void MatCalib3d::RecoverPoseAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<MatCalib3dBindings::RecoverPoseWorker>(Mat::unwrapSelf(info)),
      "Mat::RecoverPoseAsync",
      info);
}

#endif

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
void MatCalib3d::Undistort(const Napi::CallbackInfo& info) {
  Mat::syncBinding<MatCalib3dBindings::Undistort>("Undistort", info);
}

void MatCalib3d::UndistortAsync(const Napi::CallbackInfo& info) {
  Mat::asyncBinding<MatCalib3dBindings::Undistort>("Undistort", info);
}
#endif

#endif