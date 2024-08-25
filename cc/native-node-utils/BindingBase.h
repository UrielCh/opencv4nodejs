#include "utils.h"

#ifndef __FF_BINDING_BASE_H__
#define __FF_BINDING_BASE_H__

namespace FF {
class INamedValue {
public:
  virtual std::string getName() = 0;
  virtual Napi::Value wrap() = 0;
};

class IArg {
public:
  virtual bool unwrapArg(int argN, const Napi::CallbackInfo& info) = 0;
};

class IOptArg : public IArg {
public:
  virtual bool unwrapProp(Napi::Object opts) = 0;
  virtual bool assertType(Napi::Value jsVal) = 0;
};

template <class T>
class Value {
public:
  Value() {};
  Value(T val)
      : val(val) {};

  T& ref() {
    return val;
  }

  T* ptr() {
    return &val;
  }
  virtual ~Value() {
  }

private:
  T val;
};

template <class Converter>
class NamedValue : public INamedValue, public Value<typename Converter::Type> {
public:
  typedef Value<typename Converter::Type> super;

  NamedValue(std::string name)
      : name(name) {};
  NamedValue(std::string name, typename Converter::Type defaultValue)
      : super(defaultValue), name(name) {};

  Napi::Value wrap() {
    return Converter::wrap(super::ref());
  }

  std::string getName() {
    return name;
  }

  virtual ~NamedValue() {
  }

private:
  std::string name;
};

template <class Converter>
class Arg : public NamedValue<Converter>, public IArg {
public:
  typedef NamedValue<Converter> super;

  Arg()
      : super("") {};

  bool unwrapArg(int argN, const Napi::CallbackInfo& info) {
    return Converter::arg(argN, super::super::ptr(), info);
  }

  virtual ~Arg() {};
};

template <class Converter>
class OptArg : public NamedValue<Converter>, public IOptArg {
public:
  typedef NamedValue<Converter> super;

  OptArg(std::string name)
      : super(name) {};
  OptArg(std::string name, typename Converter::Type defaultValue)
      : super(name, defaultValue) {};

  bool unwrapArg(int argN, const Napi::CallbackInfo& info) {
    return Converter::optArg(argN, super::super::ptr(), info);
  }

  bool unwrapProp(Napi::Object opts) {
    return Converter::optProp(super::super::ptr(), super::getName().c_str(), opts);
  }

  bool assertType(Napi::Value jsVal) {
    return Converter::assertType(jsVal);
  }

  virtual ~OptArg() {
  }
};

class BindingBase {
public:
  /**
   * @brief Create a new required argument
   *
   * @tparam Converter
   * @return std::shared_ptr<Value<typename Converter::Type>>
   */
  template <class Converter>
  std::shared_ptr<Value<typename Converter::Type>> req() {
    std::shared_ptr<Arg<Converter>> val = std::make_shared<Arg<Converter>>();
    requiredArgs.push_back(val);
    return val;
  }

  /**
   * @brief Create a new optional argument
   *
   * @tparam Converter
   * @param name
   * @param defaultValue
   * @return std::shared_ptr<Value<typename Converter::Type>>
   */
  template <class Converter>
  std::shared_ptr<Value<typename Converter::Type>> opt(std::string name, typename Converter::Type defaultValue) {
    std::shared_ptr<OptArg<Converter>> val = std::make_shared<OptArg<Converter>>(name, defaultValue);
    optionalArgs.push_back(val);
    return val;
  }

  /**
   * @brief Returned value from the binding
   *
   * @tparam Converter
   * @param name
   * @return std::shared_ptr<Value<typename Converter::Type>>
   */
  template <class Converter>
  std::shared_ptr<Value<typename Converter::Type>> ret(std::string name) {
    std::shared_ptr<NamedValue<Converter>> val = std::make_shared<NamedValue<Converter>>(name);
    returnValues.push_back(val);
    return val;
  }

  /**
   * @brief Returned value from the binding with default value
   *
   * @tparam Converter
   * @param name
   * @param defaultValue
   * @return std::shared_ptr<Value<typename Converter::Type>>
   */
  template <class Converter>
  std::shared_ptr<Value<typename Converter::Type>> ret(std::string name, typename Converter::Type defaultValue) {
    std::shared_ptr<NamedValue<Converter>> val = std::make_shared<NamedValue<Converter>>(name, defaultValue);
    returnValues.push_back(val);
    return val;
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    for (uint idx = 0; idx < requiredArgs.size(); idx++) {
      if (requiredArgs[idx]->unwrapArg(idx, info)) {
        return true;
      }
    }
    return false;
  }

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    uint optArgsIdx = requiredArgs.size();
    for (uint idx = 0; idx < optionalArgs.size(); idx++) {
      if (optionalArgs[idx]->unwrapArg(optArgsIdx + idx, info)) {
        return true;
      }
    }
    return false;
  }

  bool hasOptArgsObject(const Napi::CallbackInfo& info) {
    if (optionalArgs.size() < 1) {
      return false;
    }
    int optArgsIdx = requiredArgs.size();
    return FF::isArgObject(info, optArgsIdx) && !optionalArgs[0]->assertType(info[optArgsIdx]);
  }

  bool unwrapOptionalArgsFromOpts(const Napi::CallbackInfo& info) {
    int optArgsIdx = requiredArgs.size();
    Napi::Object opts = info[optArgsIdx]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
    for (uint idx = 0; idx < optionalArgs.size(); idx++) {
      if (optionalArgs[idx]->unwrapProp(opts)) {
        return true;
      }
    }
    return false;
  }

  Napi::Value getReturnValue() {
    if (returnValues.size() == 0) {
      return Nan::Undefined();
    }
    if (returnValues.size() == 1) {
      return returnValues[0]->wrap();
    }
    Napi::Object ret = Nan::New<v8::Object>();
    for (std::shared_ptr<INamedValue> val : returnValues) {
      Nan::Set(ret, Nan::New(val->getName()).ToLocalChecked(), val->wrap());
    }
    return ret;
  }

  bool applyUnwrappers(const Napi::CallbackInfo& info) {
    return unwrapRequiredArgs(info)
           || (!hasOptArgsObject(info) && unwrapOptionalArgs(info))
           || (hasOptArgsObject(info) && unwrapOptionalArgsFromOpts(info));
  }

protected:
  std::vector<std::shared_ptr<IArg>> requiredArgs;
  std::vector<std::shared_ptr<IOptArg>> optionalArgs;
  std::vector<std::shared_ptr<INamedValue>> returnValues;
};

} // namespace FF

#endif
