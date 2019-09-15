//
// Created by CHEN on 2019/9/15.
//

#ifndef OPENGLDEMO_CYEGLHELPER_H
#define OPENGLDEMO_CYEGLHELPER_H

#include "EGL/egl.h"
#include "../log/AndroidLog.h"
class CyEglHelper {

public:
    EGLDisplay  mEglDisplay;
    EGLSurface  mEglSurface;
    EGLConfig mEglConfig;
    EGLContext mEglContext;
public:
    CyEglHelper();
    ~CyEglHelper();

    int initEgl(EGLNativeWindowType win);

    int swapBuffers();

    void destoryEgl();
};


#endif //OPENGLDEMO_CYEGLHELPER_H
