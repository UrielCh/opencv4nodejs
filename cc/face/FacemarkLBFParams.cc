#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "FacemarkLBFParams.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

Napi::FunctionReference FacemarkLBFParams::constructor;

Napi::Object FacemarkLBFParams(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor =
      Napi::Function::New(env, FacemarkLBFParams::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "FacemarkLBFParams"));

  Napi::SetAccessor(instanceTemplate, FF::newString(env, "bagging_overlap"), bagging_overlap_getter, bagging_overlap_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "cascade_face"), cascade_face_getter, cascade_face_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "detectROI"), detectROI_getter, detectROI_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "feats_m"), feats_m_getter, feats_m_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "initShape_n"), initShape_n_getter, initShape_n_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "model_filename"), model_filename_getter, model_filename_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "n_landmarks"), n_landmarks_getter, n_landmarks_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "pupils"), pupils_getter, pupils_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "radius_m"), radius_m_getter, radius_m_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "save_model"), save_model_getter, save_model_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "seed"), seed_getter, seed_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "shape_offset"), shape_offset_getter, shape_offset_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "stages_n"), stages_n_getter, stages_n_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "tree_depth"), tree_depth_getter, tree_depth_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "tree_n"), tree_n_getter, tree_n_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "verbose"), verbose_getter, verbose_setter);

  (target).Set("FacemarkLBFParams", FF::getFunction(ctor));
};

void FacemarkLBFParams::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "FacemarkLBFParams::New");
  FF_ASSERT_CONSTRUCT_CALL();
  FacemarkLBFParams* self = new FacemarkLBFParams();
  self->self = cv::face::FacemarkLBF::Params();
  self->Wrap(info.Holder());
  return info.Holder();
};

#endif

#endif
