#include "CatchCvExceptionWorker.h"
#include "Mat.h"
#include "NativeNodeUtils.h"
#include "Net.h"
#include "opencv2/dnn.hpp"

#ifndef __FF_DNN_H__
#define __FF_DNN_H__

class Dnn {
public:
  static NAN_MODULE_INIT(Init);

  static NAN_METHOD(ReadNetFromTensorflow);
  static NAN_METHOD(ReadNetFromTensorflowAsync);
  static NAN_METHOD(ReadNetFromCaffe);
  static NAN_METHOD(ReadNetFromCaffeAsync);
  static NAN_METHOD(BlobFromImage);
  static NAN_METHOD(BlobFromImageAsync);
  static NAN_METHOD(BlobFromImages);
  static NAN_METHOD(BlobFromImagesAsync);
#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
  static NAN_METHOD(ReadNetFromDarknet);
  static NAN_METHOD(ReadNetFromDarknetAsync);
  static NAN_METHOD(NMSBoxes);
#endif
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  static NAN_METHOD(ReadNetFromONNX);
  static NAN_METHOD(ReadNetFromONNXAsync);
#endif
#if CV_VERSION_GREATER_EQUAL(3, 4, 2)
  static NAN_METHOD(ReadNet);
  static NAN_METHOD(ReadNetAsync);
#endif
};

#endif
