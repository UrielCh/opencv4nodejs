#ifndef __MAT_MACRO_H__
#define __MAT_MACRO_H__

// only used in Mat::At and Mat::AtRaw
#define FF_MAT_AT(mat, val, get)                                                                                                                    \
  if (mat.dims > 2)                                                                                                                                 \
    val = get(env, mat, info[0].As<Napi::Number>().Int32Value(), info[1].As<Napi::Number>().Int32Value(), info[2].As<Napi::Number>().Int32Value()); \
  else                                                                                                                                              \
    val = get(env, mat, info[0].As<Napi::Number>().Int32Value(), info[1].As<Napi::Number>().Int32Value());

// only used in Mat::At
#define FF_MAT_AT_ARRAY(mat, val, get)                          \
  {                                                             \
    std::vector<int> vec;                                       \
    if (FF::IntArrayConverter::arg(0, &vec, info)) {            \
      throw Napi::TypeError::New(env, "FF_MAT_AT_ARRAY ERROR"); \
    }                                                           \
    const int* idx = &vec.front();                              \
    val = get(env, mat, idx);                                   \
  }

// only used in Mat::Set
#define FF_MAT_SET(mat, val, put)                                                                                                             \
  if (mat.dims > 2)                                                                                                                           \
    put(mat, val, info[0].As<Napi::Number>().Int32Value(), info[1].As<Napi::Number>().Int32Value(), info[2].As<Napi::Number>().Int32Value()); \
  else                                                                                                                                        \
    put(mat, val, info[0].As<Napi::Number>().Int32Value(), info[1].As<Napi::Number>().Int32Value());

// only used in Mat::New
#define FF_MAT_FILL(mat, vec, put)       \
  for (int r = 0; r < mat.rows; r++) {   \
    for (int c = 0; c < mat.cols; c++) { \
      put(mat, vec, r, c);               \
    }                                    \
  }

// only used in Mat::Set
#define FF_ASSERT_CHANNELS(cn, have, what)                                                        \
  if (cn != have) {                                                                               \
    return tryCatch.throwError(std::string(what) + " - expected vector with "                     \
                               + std::to_string(cn) + " channels, have " + std::to_string(have)); \
  }

#define FF_MAT_APPLY_TYPED_OPERATOR(mat, arg, type, ITERATOR, OPERATOR)  \
  switch (type) {                                                        \
  case CV_8UC1: ITERATOR(mat, arg, OPERATOR##Val<uchar>)    break;       \
  case CV_8UC2: ITERATOR(mat, arg, OPERATOR##Vec2<uchar>)   break;       \
  case CV_8UC3: ITERATOR(mat, arg, OPERATOR##Vec3<uchar>)   break;       \
  case CV_8UC4: ITERATOR(mat, arg, OPERATOR##Vec4<uchar>)   break;       \
  case CV_8SC1: ITERATOR(mat, arg, OPERATOR##Val<char>)     break;       \
  case CV_8SC2: ITERATOR(mat, arg, OPERATOR##Vec2<char>)    break;       \
  case CV_8SC3: ITERATOR(mat, arg, OPERATOR##Vec3<char>)    break;       \
  case CV_8SC4: ITERATOR(mat, arg, OPERATOR##Vec4<char>)    break;       \
  case CV_16UC1: ITERATOR(mat, arg, OPERATOR##Val<ushort>)  break;       \
  case CV_16UC2: ITERATOR(mat, arg, OPERATOR##Vec2<ushort>) break;       \
  case CV_16UC3: ITERATOR(mat, arg, OPERATOR##Vec3<ushort>) break;       \
  case CV_16UC4: ITERATOR(mat, arg, OPERATOR##Vec4<ushort>) break;       \
  case CV_16SC1: ITERATOR(mat, arg, OPERATOR##Val<short>)   break;       \
  case CV_16SC2: ITERATOR(mat, arg, OPERATOR##Vec2<short>)  break;       \
  case CV_16SC3: ITERATOR(mat, arg, OPERATOR##Vec3<short>)  break;       \
  case CV_16SC4: ITERATOR(mat, arg, OPERATOR##Vec4<short>)  break;       \
  case CV_32SC1: ITERATOR(mat, arg, OPERATOR##Val<int>)     break;       \
  case CV_32SC2: ITERATOR(mat, arg, OPERATOR##Vec2<int>)    break;       \
  case CV_32SC3: ITERATOR(mat, arg, OPERATOR##Vec3<int>)    break;       \
  case CV_32SC4: ITERATOR(mat, arg, OPERATOR##Vec4<int>)    break;       \
  case CV_32FC1: ITERATOR(mat, arg, OPERATOR##Val<float>)   break;       \
  case CV_32FC2: ITERATOR(mat, arg, OPERATOR##Vec2<float>)  break;       \
  case CV_32FC3: ITERATOR(mat, arg, OPERATOR##Vec3<float>)  break;       \
  case CV_32FC4: ITERATOR(mat, arg, OPERATOR##Vec4<float>)  break;       \
  case CV_64FC1: ITERATOR(mat, arg, OPERATOR##Val<double>)  break;       \
  case CV_64FC2: ITERATOR(mat, arg, OPERATOR##Vec2<double>) break;       \
  case CV_64FC3: ITERATOR(mat, arg, OPERATOR##Vec3<double>) break;       \
  case CV_64FC4: ITERATOR(mat, arg, OPERATOR##Vec4<double>) break;       \
  default:                                                               \
    throw Napi::TypeError::New(env, "invalid matType: " + std::to_string(type)); \
  }
// return env.Undefined();

#define FF_JS_ARRAY_FROM_MAT_2D(mat, rowArray, get)         \
  for (int r = 0; r < mat.rows; r++) {                      \
    Napi::Array colArray = Napi::Array::New(env, mat.cols); \
    for (int c = 0; c < mat.cols; c++) {                    \
      (colArray).Set(c, get(mat, r, c));                    \
    }                                                       \
    (rowArray).Set(r, colArray);                            \
  }

#define FF_JS_ARRAY_FROM_MAT_3D(mat, rowArray, get)                \
  for (int r = 0; r < mat.size[0]; r++) {                          \
    Napi::Array colArray = Napi::Array::New(env, mat.size[1]);     \
    for (int c = 0; c < mat.size[1]; c++) {                        \
      Napi::Array depthArray = Napi::Array::New(env, mat.size[2]); \
      for (int z = 0; z < mat.size[2]; z++) {                      \
        (depthArray).Set(z, get(mat, r, c, z));                    \
      }                                                            \
      (colArray).Set(c, depthArray);                               \
    }                                                              \
    (rowArray).Set(r, colArray);                                   \
  }

#define FF_JS_ARRAY_FROM_MAT_4D(mat, rowArray, get)             \
  {                                                             \
    cv::MatSize sizes = mat.size;                               \
    cv::Vec4i cur = cv::Vec4i(0, 0, 0, 0);                      \
    for (cur[0] = 0; cur[0] < sizes[0]; cur[0]++) {             \
      Napi::Array array1 = Napi::Array::New(env, sizes[1]);     \
      for (cur[1] = 0; cur[1] < sizes[1]; cur[1]++) {           \
        Napi::Array array2 = Napi::Array::New(env, sizes[2]);   \
        for (cur[2] = 0; cur[2] < sizes[2]; cur[2]++) {         \
          Napi::Array array3 = Napi::Array::New(env, sizes[3]); \
          for (cur[3] = 0; cur[3] < sizes[3]; cur[3]++) {       \
            (array3).Set(cur[3], get(mat, cur));                \
          }                                                     \
          (array2).Set(cur[2], array3);                         \
        }                                                       \
        (array1).Set(cur[1], array2);                           \
      }                                                         \
      (rowArray).Set(cur[0], array1);                           \
    }                                                           \
  }

#define FF_JS_ARRAY_FROM_MAT_5D(mat, rowArray, get)               \
  {                                                               \
    cv::MatSize sizes = mat.size;                                 \
    cv::Vec4i cur = cv::Vec5i(0, 0, 0, 0, 0);                     \
    for (cur[0] = 0; cur[0] < sizes[0]; cur[0]++) {               \
      Napi::Array array1 = Napi::Array::New(env, sizes[1]);       \
      for (cur[1] = 0; cur[1] < sizes[1]; cur[1]++) {             \
        Napi::Array array2 = Napi::Array::New(env, sizes[2]);     \
        for (cur[2] = 0; cur[2] < sizes[2]; cur[2]++) {           \
          Napi::Array array3 = Napi::Array::New(env, sizes[3]);   \
          for (cur[3] = 0; cur[3] < sizes[3]; cur[3]++) {         \
            Napi::Array array4 = Napi::Array::New(env, sizes[4]); \
            for (cur[4] = 0; cur[4] < sizes[4]; cur[4]++) {       \
              (array4).Set(cur[4], get(mat, cur));                \
            }                                                     \
            (array3).Set(cur[3], array3);                         \
          }                                                       \
          (array2).Set(cur[2], array3);                           \
        }                                                         \
        (array1).Set(cur[1], array2);                             \
      }                                                           \
      (rowArray).Set(cur[0], array1);                             \
    }                                                             \
  }

// only used in Mat::New
#define FF_MAT_FROM_JS_ARRAY_2D(mat, rowArray, put)             \
  for (int r = 0; r < mat.rows; r++) {                          \
    Napi::Array colArray = (rowArray).Get(r).As<Napi::Array>(); \
    for (int c = 0; c < mat.cols; c++) {                        \
      put(mat, (colArray).Get(c), r, c);                        \
    }                                                           \
  }

#define FF_MAT_FROM_JS_ARRAY_3D(mat, rowArray, put)                        \
  {                                                                        \
    cv::MatSize sizes = mat.size;                                          \
    cv::Vec3i cur = cv::Vec3b(0, 0, 0);                                    \
    for (cur[0] = 0; cur[0] < sizes[0]; cur[0]++) {                        \
      Napi::Array colArray1 = (rowArray).Get(cur[0]).As<Napi::Array>();    \
      for (cur[1] = 0; cur[1] < sizes[1]; cur[1]++) {                      \
        Napi::Array colArray2 = (colArray1).Get(cur[1]).As<Napi::Array>(); \
        for (cur[2] = 0; cur[2] < sizes[2]; cur[2]++) {                    \
          put(mat, (colArray2).Get(cur[2]), cur);                          \
        }                                                                  \
      }                                                                    \
    }                                                                      \
  }

// std::cout << "loop line " << cur[0] << "/" << sizes[1] << std::endl;
// std::cout << "loop cell " << cur[0] << "/" << sizes[0] << ", " << cur[1] << "/" << sizes[1] << std::endl;
// std::cout << "loop cell " << cur[0] << "/" << sizes[0] << ", " << cur[1] << "/" << sizes[1] << ", " << cur[2] << "/" << sizes[2]<< std::endl;
// std::cout << "loop pos " << cur[0] << ", " << cur[1] << ", " << cur[2] << ", " << cur[3] << std::endl;

#define FF_MAT_FROM_JS_ARRAY_4D(mat, rowArray, put)                          \
  {                                                                          \
    cv::MatSize sizes = mat.size;                                            \
    cv::Vec4i cur = cv::Vec4i(0, 0, 0, 0);                                   \
    for (cur[0] = 0; cur[0] < sizes[0]; cur[0]++) {                          \
      Napi::Array colArray1 = (rowArray).Get(cur[0]).As<Napi::Array>();      \
      for (cur[1] = 0; cur[1] < sizes[1]; cur[1]++) {                        \
        Napi::Array colArray2 = (colArray1).Get(cur[1]).As<Napi::Array>();   \
        for (cur[2] = 0; cur[2] < sizes[2]; cur[2]++) {                      \
          Napi::Array colArray3 = (colArray2).Get(cur[2]).As<Napi::Array>(); \
          for (cur[3] = 0; cur[3] < sizes[3]; cur[3]++) {                    \
            put(mat, (colArray3).Get(cur[3]), cur);                          \
          }                                                                  \
        }                                                                    \
      }                                                                      \
    }                                                                        \
  }

#define FF_MAT_FROM_JS_ARRAY_5D(mat, rowArray, put)                            \
  {                                                                            \
    cv::MatSize sizes = mat.size;                                              \
    cv::Vec4i cur = cv::Vec5b(0, 0, 0, 0, 0);                                  \
    for (cur[0] = 0; cur[0] < sizes[0]; cur[0]++) {                            \
      Napi::Array colArray1 = (rowArray).Get(cur[0]).As<Napi::Array>();        \
      for (cur[1] = 0; cur[1] < sizes[1]; cur[1]++) {                          \
        Napi::Array colArray2 = (colArray1).Get(cur[1]).As<Napi::Array>();     \
        for (cur[2] = 0; cur[2] < sizes[2]; cur[2]++) {                        \
          Napi::Array colArray3 = (colArray2).Get(cur[2]).As<Napi::Array>();   \
          for (cur[3] = 0; cur[3] < sizes[3]; cur[3]++) {                      \
            Napi::Array colArray4 = (colArray3).Get(cur[3]).As<Napi::Array>(); \
            for (cur[4] = 0; cur[4] < sizes[4]; cur[4]++) {                    \
              put(mat, (colArray4).Get(cur[4]), cur);                          \
            }                                                                  \
          }                                                                    \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  }

#endif /* __MAT_MACRO_H__ */