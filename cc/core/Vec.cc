#include "Vec.h"

Napi::FunctionReference Vec2::constructor;
Napi::FunctionReference Vec3::constructor;
Napi::FunctionReference Vec4::constructor;
Napi::FunctionReference Vec6::constructor;

Napi::Object Vec(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference vec2Ctor = Napi::Function::New(env, Vec2::New);
  Vec2::constructor.Reset(vec2Ctor);

  vec2Ctor->SetClassName(Napi::String::New(env, "Vec2"));
  Napi::SetAccessor(vec2Ctor->InstanceTemplate(), Napi::String::New(env, "x"), Vec2::x_getter);
  Napi::SetAccessor(vec2Ctor->InstanceTemplate(), Napi::String::New(env, "y"), Vec2::y_getter);
  Napi::SetPrototypeMethod(vec2Ctor, "at", Vec2::At);
  Napi::SetPrototypeMethod(vec2Ctor, "norm", Vec2::Norm);
  Vec2::Init(vec2Ctor);

  Napi::FunctionReference vec3Ctor = Napi::Function::New(env, Vec3::New);
  Vec3::constructor.Reset(vec3Ctor);

  vec3Ctor->SetClassName(Napi::String::New(env, "Vec3"));
  Napi::SetAccessor(vec3Ctor->InstanceTemplate(), Napi::String::New(env, "x"), Vec3::x_getter);
  Napi::SetAccessor(vec3Ctor->InstanceTemplate(), Napi::String::New(env, "y"), Vec3::y_getter);
  Napi::SetAccessor(vec3Ctor->InstanceTemplate(), Napi::String::New(env, "z"), Vec3::z_getter);
  Napi::SetPrototypeMethod(vec3Ctor, "at", Vec3::At);
  Napi::SetPrototypeMethod(vec3Ctor, "cross", Vec3::Cross);
  Napi::SetPrototypeMethod(vec3Ctor, "norm", Vec3::Norm);
  Vec3::Init(vec3Ctor);

  Napi::FunctionReference vec4Ctor = Napi::Function::New(env, Vec4::New);
  Vec4::constructor.Reset(vec4Ctor);

  vec4Ctor->SetClassName(Napi::String::New(env, "Vec4"));
  Napi::SetAccessor(vec4Ctor->InstanceTemplate(), Napi::String::New(env, "w"), Vec4::w_getter);
  Napi::SetAccessor(vec4Ctor->InstanceTemplate(), Napi::String::New(env, "x"), Vec4::x_getter);
  Napi::SetAccessor(vec4Ctor->InstanceTemplate(), Napi::String::New(env, "y"), Vec4::y_getter);
  Napi::SetAccessor(vec4Ctor->InstanceTemplate(), Napi::String::New(env, "z"), Vec4::z_getter);
  Napi::SetPrototypeMethod(vec4Ctor, "at", Vec4::At);
  Napi::SetPrototypeMethod(vec4Ctor, "norm", Vec4::Norm);
  Vec4::Init(vec4Ctor);

  Napi::FunctionReference vec6Ctor = Napi::Function::New(env, Vec6::New);
  Vec6::constructor.Reset(vec6Ctor);

  vec6Ctor->SetClassName(Napi::String::New(env, "Vec6"));
  Napi::SetAccessor(vec6Ctor->InstanceTemplate(), Napi::String::New(env, "u"), Vec6::u_getter);
  Napi::SetAccessor(vec6Ctor->InstanceTemplate(), Napi::String::New(env, "v"), Vec6::v_getter);
  Napi::SetAccessor(vec6Ctor->InstanceTemplate(), Napi::String::New(env, "w"), Vec6::w_getter);
  Napi::SetAccessor(vec6Ctor->InstanceTemplate(), Napi::String::New(env, "x"), Vec6::x_getter);
  Napi::SetAccessor(vec6Ctor->InstanceTemplate(), Napi::String::New(env, "y"), Vec6::y_getter);
  Napi::SetAccessor(vec6Ctor->InstanceTemplate(), Napi::String::New(env, "z"), Vec6::z_getter);
  Napi::SetPrototypeMethod(vec6Ctor, "at", Vec6::At);
  Napi::SetPrototypeMethod(vec6Ctor, "norm", Vec6::Norm);
  Vec6::Init(vec6Ctor);

  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, Vec::New));

  ctor->SetClassName(Napi::String::New(env, "Vec"));
  target.Set("Vec", FF::getFunction(ctor));
  target.Set("Vec2", FF::getFunction(ctor));
  target.Set("Vec3", FF::getFunction(ctor));
  target.Set("Vec4", FF::getFunction(ctor));
  target.Set("Vec6", FF::getFunction(ctor));
};

void Vec::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Vec::New");
  FF_ASSERT_CONSTRUCT_CALL();
  if (info.Length() < 2 || info.Length() > 6 || info.Length() == 5) {
    return tryCatch.throwError("Vec::New - expected arguments (u, v), (w), x, y, (z)");
  }
  Napi::Object jsVec;

  switch (info.Length()) {
  case 2:
    jsVec = FF::newInstance(Napi::New(env, Vec2::constructor));
    Napi::ObjectWrap::Unwrap<Vec2>(jsVec)->self = cv::Vec2d(
        info[0].ToNumber(Napi::GetCurrentContext())->Value(),
        info[1].ToNumber(Napi::GetCurrentContext())->Value());
    break;
  case 3:
    jsVec = FF::newInstance(Napi::New(env, Vec3::constructor));
    Napi::ObjectWrap::Unwrap<Vec3>(jsVec)->self = cv::Vec3d(
        info[0].ToNumber(Napi::GetCurrentContext())->Value(),
        info[1].ToNumber(Napi::GetCurrentContext())->Value(),
        info[2].ToNumber(Napi::GetCurrentContext())->Value());
    break;
  case 4:
    jsVec = FF::newInstance(Napi::New(env, Vec4::constructor));
    Napi::ObjectWrap::Unwrap<Vec4>(jsVec)->self = cv::Vec4d(
        info[0].ToNumber(Napi::GetCurrentContext())->Value(),
        info[1].ToNumber(Napi::GetCurrentContext())->Value(),
        info[2].ToNumber(Napi::GetCurrentContext())->Value(),
        info[3].ToNumber(Napi::GetCurrentContext())->Value());
    break;
  case 6:
    jsVec = FF::newInstance(Napi::New(env, Vec6::constructor));
    Napi::ObjectWrap::Unwrap<Vec6>(jsVec)->self = cv::Vec6d(
        info[0].ToNumber(Napi::GetCurrentContext())->Value(),
        info[1].ToNumber(Napi::GetCurrentContext())->Value(),
        info[2].ToNumber(Napi::GetCurrentContext())->Value(),
        info[3].ToNumber(Napi::GetCurrentContext())->Value(),
        info[4].ToNumber(Napi::GetCurrentContext())->Value(),
        info[5].ToNumber(Napi::GetCurrentContext())->Value());
    break;
  }
  return jsVec;
}
