#include "opencv_modules.h"

#ifdef HAVE_OPENCV_CALIB3D

#include "calib3d.h"
#include "calib3dConstants.h"

Napi::Object Calib3d(Napi::Env env, Napi::Object exports) {
  Calib3dConstants::Init(env, exports);
  exports.Set("findHomography", Napi::Function::New(env, Calib3d::FindHomography));
  exports.Set("findHomographyAsync", Napi::Function::New(env, Calib3d::FindHomographyAsync));
  exports.Set("composeRT", Napi::Function::New(env, Calib3d::ComposeRT));
  exports.Set("composeRTAsync", Napi::Function::New(env, Calib3d::ComposeRTAsync));
  exports.Set("solvePnP", Napi::Function::New(env, Calib3d::SolvePnP));
  exports.Set("solvePnPAsync", Napi::Function::New(env, Calib3d::SolvePnPAsync));
  exports.Set("solvePnPRansac", Napi::Function::New(env, Calib3d::SolvePnPRansac));
  exports.Set("solvePnPRansacAsync", Napi::Function::New(env, Calib3d::SolvePnPRansacAsync));
  exports.Set("projectPoints", Napi::Function::New(env, Calib3d::ProjectPoints));
  exports.Set("projectPointsAsync", Napi::Function::New(env, Calib3d::ProjectPointsAsync));
  exports.Set("initCameraMatrix2D", Napi::Function::New(env, Calib3d::InitCameraMatrix2D));
  exports.Set("initCameraMatrix2DAsync", Napi::Function::New(env, Calib3d::InitCameraMatrix2DAsync));
  exports.Set("stereoCalibrate", Napi::Function::New(env, Calib3d::StereoCalibrate));
  exports.Set("stereoCalibrateAsync", Napi::Function::New(env, Calib3d::StereoCalibrateAsync));
  exports.Set("stereoRectifyUncalibrated", Napi::Function::New(env, Calib3d::StereoRectifyUncalibrated));
  exports.Set("stereoRectifyUncalibratedAsync", Napi::Function::New(env, Calib3d::StereoRectifyUncalibratedAsync));
  exports.Set("findFundamentalMat", Napi::Function::New(env, Calib3d::FindFundamentalMat));
  exports.Set("findFundamentalMatAsync", Napi::Function::New(env, Calib3d::FindFundamentalMatAsync));
  exports.Set("findEssentialMat", Napi::Function::New(env, Calib3d::FindEssentialMat));
  exports.Set("findEssentialMatAsync", Napi::Function::New(env, Calib3d::FindEssentialMatAsync));
  exports.Set("recoverPose", Napi::Function::New(env, Calib3d::RecoverPose));
  exports.Set("recoverPoseAsync", Napi::Function::New(env, Calib3d::RecoverPoseAsync));
  exports.Set("computeCorrespondEpilines", Napi::Function::New(env, Calib3d::ComputeCorrespondEpilines));
  exports.Set("computeCorrespondEpilinesAsync", Napi::Function::New(env, Calib3d::ComputeCorrespondEpilinesAsync));
  exports.Set("getValidDisparityROI", Napi::Function::New(env, Calib3d::GetValidDisparityROI));
  exports.Set("getValidDisparityROIAsync", Napi::Function::New(env, Calib3d::GetValidDisparityROIAsync));
  exports.Set("estimateAffine3D", Napi::Function::New(env, Calib3d::EstimateAffine3D));
  exports.Set("estimateAffine3DAsync", Napi::Function::New(env, Calib3d::EstimateAffine3DAsync));
#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
  exports.Set("sampsonDistance", Napi::Function::New(env, Calib3d::SampsonDistance));
  exports.Set("sampsonDistanceAsync", Napi::Function::New(env, Calib3d::SampsonDistanceAsync));
  exports.Set("calibrateCamera", Napi::Function::New(env, Calib3d::CalibrateCamera));
  exports.Set("calibrateCameraAsync", Napi::Function::New(env, Calib3d::CalibrateCameraAsync));
#endif
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  exports.Set("calibrateCameraExtended", Napi::Function::New(env, Calib3d::CalibrateCameraExtended));
  exports.Set("calibrateCameraExtendedAsync", Napi::Function::New(env, Calib3d::CalibrateCameraExtendedAsync));
  exports.Set("estimateAffine2D", Napi::Function::New(env, Calib3d::EstimateAffine2D));
  exports.Set("estimateAffine2DAsync", Napi::Function::New(env, Calib3d::EstimateAffine2DAsync));
  exports.Set("estimateAffinePartial2D", Napi::Function::New(env, Calib3d::EstimateAffinePartial2D));
  exports.Set("estimateAffinePartial2DAsync", Napi::Function::New(env, Calib3d::EstimateAffinePartial2DAsync));
#endif
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
  exports.Set("solveP3P", Napi::Function::New(env, Calib3d::SolveP3P));
  exports.Set("solveP3PAsync", Napi::Function::New(env, Calib3d::SolveP3PAsync));
#endif
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  exports.Set("undistortPoints", Napi::Function::New(env, Calib3d::UndistortPoints));
  exports.Set("undistortPointsAsync", Napi::Function::New(env, Calib3d::UndistortPointsAsync));
#endif
};

void Calib3d::FindHomography(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::FindHomographyWorker>(),
      "Calib3d::FindHomography",
      info);
}

void Calib3d::FindHomographyAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::FindHomographyWorker>(),
      "Calib3d::FindHomographyAsync",
      info);
}

void Calib3d::ComposeRT(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::ComposeRTWorker>(),
      "Calib3d::ComposeRT",
      info);
}

void Calib3d::ComposeRTAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::ComposeRTWorker>(),
      "Calib3d::ComposeRTAsync",
      info);
}

void Calib3d::SolvePnP(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::SolvePnPWorker>(),
      "Calib3d::SolvePnP",
      info);
}

void Calib3d::SolvePnPAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::SolvePnPWorker>(),
      "Calib3d::SolvePnPAsync",
      info);
}

void Calib3d::SolvePnPRansac(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::SolvePnPRansacWorker>(),
      "Calib3d::SolvePnPRansac",
      info);
}

void Calib3d::SolvePnPRansacAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::SolvePnPRansacWorker>(),
      "Calib3d::SolvePnPRansacAsync",
      info);
}

void Calib3d::ProjectPoints(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::ProjectPointsWorker>(),
      "Calib3d::ProjectPoints",
      info);
}

void Calib3d::ProjectPointsAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::ProjectPointsWorker>(),
      "Calib3d::ProjectPointsAsync",
      info);
}

void Calib3d::InitCameraMatrix2D(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::InitCameraMatrix2DWorker>(),
      "Calib3d::InitCameraMatrix2D",
      info);
}

void Calib3d::InitCameraMatrix2DAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::InitCameraMatrix2DWorker>(),
      "Calib3d::InitCameraMatrix2DAsync",
      info);
}

void Calib3d::StereoCalibrate(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::StereoCalibrateWorker>(),
      "Calib3d::StereoCalibrate",
      info);
}

void Calib3d::StereoCalibrateAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::StereoCalibrateWorker>(),
      "Calib3d::StereoCalibrateAsync",
      info);
}

void Calib3d::StereoRectifyUncalibrated(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::StereoRectifyUncalibratedWorker>(),
      "Calib3d::StereoRectifyUncalibrated",
      info);
}

void Calib3d::StereoRectifyUncalibratedAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::StereoRectifyUncalibratedWorker>(),
      "Calib3d::StereoRectifyUncalibratedAsync",
      info);
}

void Calib3d::FindFundamentalMat(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::FindFundamentalMatWorker>(),
      "Calib3d::FindFundamentalMat",
      info);
}

void Calib3d::FindFundamentalMatAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::FindFundamentalMatWorker>(),
      "Calib3d::FindFundamentalMatAsync",
      info);
}

void Calib3d::FindEssentialMat(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::FindEssentialMatWorker>(),
      "Calib3d::FindEssentialMat",
      info);
}

void Calib3d::FindEssentialMatAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::FindEssentialMatWorker>(),
      "Calib3d::FindEssentialMatAsync",
      info);
}

void Calib3d::RecoverPose(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::RecoverPoseWorker>(),
      "Calib3d::RecoverPose",
      info);
}

void Calib3d::RecoverPoseAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::RecoverPoseWorker>(),
      "Calib3d::RecoverPoseAsync",
      info);
}

void Calib3d::ComputeCorrespondEpilines(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::ComputeCorrespondEpilinesWorker>(),
      "Calib3d::ComputeCorrespondEpilines",
      info);
}

void Calib3d::ComputeCorrespondEpilinesAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::ComputeCorrespondEpilinesWorker>(),
      "Calib3d::ComputeCorrespondEpilinesAsync",
      info);
}

void Calib3d::GetValidDisparityROI(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::GetValidDisparityROIWorker>(),
      "Calib3d::GetValidDisparityROI",
      info);
}

void Calib3d::GetValidDisparityROIAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::GetValidDisparityROIWorker>(),
      "Calib3d::GetValidDisparityROIAsync",
      info);
}

void Calib3d::EstimateAffine3D(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::EstimateAffine3DWorker>(),
      "Calib3d::EstimateAffine3D",
      info);
}

void Calib3d::EstimateAffine3DAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::EstimateAffine3DWorker>(),
      "Calib3d::EstimateAffine3DAsync",
      info);
}

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

void Calib3d::SampsonDistance(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::SampsonDistanceWorker>(),
      "Calib3d::SampsonDistance",
      info);
}

void Calib3d::SampsonDistanceAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::SampsonDistanceWorker>(),
      "Calib3d::SampsonDistanceAsync",
      info);
}

void Calib3d::CalibrateCamera(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::CalibrateCameraWorker>(),
      "Calib3d::CalibrateCamera",
      info);
}

void Calib3d::CalibrateCameraAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::CalibrateCameraWorker>(),
      "Calib3d::CalibrateCameraAsync",
      info);
}

#endif

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)

void Calib3d::CalibrateCameraExtended(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::CalibrateCameraExtendedWorker>(),
      "Calib3d::CalibrateCameraExtended",
      info);
}

void Calib3d::CalibrateCameraExtendedAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::CalibrateCameraExtendedWorker>(),
      "Calib3d::CalibrateCameraExtendedAsync",
      info);
}

void Calib3d::EstimateAffine2D(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::EstimateAffine2DWorker>(),
      "Calib3d::EstimateAffine2D",
      info);
}

void Calib3d::EstimateAffine2DAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::EstimateAffine2DWorker>(),
      "Calib3d::EstimateAffine2DAsync",
      info);
}

void Calib3d::EstimateAffinePartial2D(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::EstimateAffinePartial2DWorker>(),
      "Calib3d::EstimateAffinePartial2D",
      info);
}

void Calib3d::EstimateAffinePartial2DAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::EstimateAffinePartial2DWorker>(),
      "Calib3d::EstimateAffinePartial2DAsync",
      info);
}
#endif

#if CV_VERSION_GREATER_EQUAL(3, 3, 0)

void Calib3d::SolveP3P(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<Calib3dBindings::SolveP3PWorker>(),
      "Calib3d::SolveP3P",
      info);
}

void Calib3d::SolveP3PAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<Calib3dBindings::SolveP3PWorker>(),
      "Calib3d::SolveP3PAsync",
      info);
}

#endif

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
void Calib3d::UndistortPoints(const Napi::CallbackInfo& info) {
  FF::syncBinding<Calib3dBindings::UndistortPoints>("Calib3d", "UndistortPoints", info);
}

void Calib3d::UndistortPointsAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<Calib3dBindings::UndistortPoints>("Calib3d", "UndistortPoints", info);
}
#endif

#endif