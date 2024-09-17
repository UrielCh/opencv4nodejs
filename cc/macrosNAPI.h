#define FF_ASSERT_CONSTRUCT_CALL()                                                   \
  if (!info.IsConstructCall()) {                                                     \
    return tryCatch.throwError("constructor has to be called with \"new\" keyword"); \
  }
