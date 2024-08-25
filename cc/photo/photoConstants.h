#include "macros.h"
#include <opencv2/photo.hpp>

#ifndef __FF_PHOTO_CONSTANTS_H__
#define __FF_PHOTO_CONSTANTS_H__

class PhotoConstants {
public:
  static void Init(Napi::Object target);
};

#endif //__FF_PHOTOCONSTANTS_H__
