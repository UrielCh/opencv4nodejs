#include "AbstractConverter.h"
#include "UnwrapperBase.h"
#include "utils.h"

#ifndef __FF_PRIMITIVE_TYPE_CONVERTERS_H__
#define __FF_PRIMITIVE_TYPE_CONVERTERS_H__

namespace FF {

template <class ConverterImpl, class T>
class PrimitiveTypeConverter : public UnwrapperBase<ConverterImpl, T> {
public:
  static Napi::Value wrap(Napi::Env env, T val) {
    return Napi::Value::From(env, val);
  }
};

class IntConverterImpl : public PrimitiveTypeConverter<IntConverterImpl, int> {
public:
  typedef int Type;

  static std::string getTypeName() {
    return std::string("int");
  }

  static bool assertType(Napi::Value jsVal) {
    return jsVal.IsNumber();
  }

  static int unwrapUnchecked(Napi::Value jsVal) {
    return jsVal.As<Napi::Number>().Int32Value();
  }
};

class UintConverterImpl : public PrimitiveTypeConverter<UintConverterImpl, uint> {
public:
  typedef uint Type;

  static std::string getTypeName() {
    return std::string("uint");
  }

  static bool assertType(Napi::Value jsVal) {
    return jsVal.IsNumber();
  }

  static uint32_t unwrapUnchecked(Napi::Value jsVal) {
    return jsVal.As<Napi::Number>().Uint32Value();
  }
};

class LongConverterImpl : public PrimitiveTypeConverter<LongConverterImpl, long> {
public:
  typedef long Type;

  static std::string getTypeName() {
    return std::string("long");
  }

  static bool assertType(Napi::Value jsVal) {
    return jsVal.IsNumber();
  }

  static long unwrapUnchecked(Napi::Value jsVal) {
    return jsVal.As<Napi::Number>().Int64Value();
  }
};

class UlongConverterImpl : public PrimitiveTypeConverter<UlongConverterImpl, ulong> {
public:
  typedef ulong Type;

  static std::string getTypeName() {
    return std::string("ulong");
  }

  static bool assertType(Napi::Value& jsVal) {
    return jsVal.IsNumber();
  }

  static ulong unwrapUnchecked(Napi::Value jsVal) {
    return static_cast<ulong>(jsVal.As<Napi::Number>().Uint32Value());
  }
};

class CharConverterImpl : public PrimitiveTypeConverter<CharConverterImpl, char> {
public:
  typedef char Type;

  static std::string getTypeName() {
    return std::string("char");
  }

  static bool assertType(Napi::Value jsVal) {
    return jsVal.IsNumber();
  }

  static char unwrapUnchecked(Napi::Value jsVal) {
    return static_cast<char>(jsVal.As<Napi::Number>().Int32Value());
  }
};

class UcharConverterImpl : public PrimitiveTypeConverter<UcharConverterImpl, uchar> {
public:
  typedef uchar Type;

  static std::string getTypeName() {
    return std::string("uchar");
  }

  static bool assertType(Napi::Value jsVal) {
    return jsVal.IsNumber();
  }

  static char unwrapUnchecked(Napi::Value jsVal) {
    return static_cast<uchar>(jsVal.As<Napi::Number>().Uint32Value());
  }
};

class BoolConverterImpl : public PrimitiveTypeConverter<BoolConverterImpl, bool> {
public:
  typedef bool Type;

  static std::string getTypeName() {
    return std::string("bool");
  }

  static bool assertType(Napi::Value jsVal) {
    return jsVal.IsBoolean();
  }

  static bool unwrapUnchecked(Napi::Value jsVal) {
    return jsVal.As<Napi::Boolean>().Value();
  }
};

class DoubleConverterImpl : public PrimitiveTypeConverter<DoubleConverterImpl, double> {
public:
  typedef double Type;

  static std::string getTypeName() {
    return std::string("double");
  }

  static bool assertType(Napi::Value jsVal) {
    return jsVal.IsNumber();
  }

  static double unwrapUnchecked(Napi::Value jsVal) {
    return jsVal.As<Napi::Number>().DoubleValue();
  }
};

class FloatConverterImpl : public PrimitiveTypeConverter<FloatConverterImpl, float> {
public:
  typedef float Type;

  static std::string getTypeName() {
    return std::string("float");
  }

  static bool assertType(Napi::Value jsVal) {
    return jsVal.IsNumber();
  }

  static float unwrapUnchecked(Napi::Value jsVal) {
    return jsVal.As<Napi::Number>().FloatValue();
  }
};

class StringConverterImpl : public UnwrapperBase<StringConverterImpl, std::string> {
public:
  typedef std::string Type;

  static std::string getTypeName() {
    return std::string("string");
  }

  static bool assertType(Napi::Value& jsVal) {
    return jsVal.IsString();
  }

  static std::string unwrapUnchecked(Napi::Value& jsVal) {
    return jsVal.As<Napi::String>().Utf8Value();
  }

  static Napi::Value wrap(Napi::Env env, std::string val) {
    return Napi::String::New(env, val);
  }
};

} // namespace FF

#endif