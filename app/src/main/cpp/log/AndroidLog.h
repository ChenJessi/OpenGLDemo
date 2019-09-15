//
// Created by CHEN on 2019/9/15.
//

#ifndef OPENGLDEMO_ANDROIDLOG_H
#define OPENGLDEMO_ANDROIDLOG_H

#include "android/log.h"

#define LOGD(FORMAT, ...) __android_log_print(ANDROID_LOG_DEBUG, "chen188669", FORMAT, ##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR, "chen188669", FORMAT, ##__VA_ARGS__);


#endif //OPENGLDEMO_ANDROIDLOG_H
