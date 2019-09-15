//
// Created by CHEN on 2019/9/15.
//

#include "CyEglHelper.h"

CyEglHelper::CyEglHelper() {
    mEglDisplay = EGL_NO_DISPLAY;
    mEglSurface = EGL_NO_SURFACE;
    mEglContext = EGL_NO_CONTEXT;
    mEglConfig = NULL;
}


CyEglHelper::~CyEglHelper() {

}



int CyEglHelper::initEgl(EGLNativeWindowType win) {
    //1、得到默认的显示设备（就是窗口）
    mEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (mEglDisplay == EGL_NO_DISPLAY){
        LOGE("eglGetDisplay error");
        return -1;
    }
    //2、初始化默认显示设备
    EGLint  *version = new EGLint[2];
    if (!eglInitialize(mEglDisplay, &version[0], &version[1])){
        LOGE("eglInitialize error");
        return -1;
    }
    //3、设置显示设备的属性
    const EGLint attribs[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 8,
            EGL_STENCIL_SIZE , 8,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_NONE
    };
    EGLint  num_config;
    if (!eglChooseConfig(mEglDisplay, attribs, NULL, 1, &num_config)){
        LOGE("eglChooseConfig error 1")
        return  -1;
    }
    //4、从系统中获取对应属性的配置
    if (!eglChooseConfig(mEglDisplay, attribs, &mEglConfig, num_config, &num_config)){
        LOGE("eglChooseConfig error 2");
        return -1;
    }
    //5、创建EglContext
    int attrib_list[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };

    //6、创建渲染的Surface
    mEglContext = eglCreateContext(mEglDisplay, mEglConfig, EGL_NO_CONTEXT, attrib_list);

    if (mEglContext == EGL_NO_CONTEXT){
        LOGE("eglCreateContext error");
        return -1;
    }
    //7、绑定EglContext和Surface到显示设备中
    if (!eglMakeCurrent(mEglDisplay, mEglSurface,mEglSurface, mEglContext )){
        LOGE("eglMakeCurrent error");
        return -1;
    }
    LOGD("egl init success!")
    return 0;
}

int CyEglHelper::swapBuffers() {
    if (mEglDisplay != EGL_NO_DISPLAY && mEglSurface != EGL_NO_SURFACE){
        if (eglSwapBuffers(mEglDisplay, mEglSurface)){
            return 0
        }
    }
    return -1;
}

void CyEglHelper::destoryEgl() {
    if (mEglDisplay != EGL_NO_DISPLAY){
        eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    }
    if (mEglDisplay != EGL_NO_DISPLAY && mEglSurface != EGL_NO_SURFACE){
        eglDestroySurface(mEglDisplay, mEglSurface);
        mEglSurface = EGL_NO_SURFACE;
    }

    if (mEglDisplay != EGL_NO_DISPLAY && mEglContext != EGL_NO_CONTEXT){
        eglDestroyContext(mEglDisplay, mEglContext);
        mEglContext = EGL_NO_CONTEXT;
    }

    if (mEglDisplay != EGL_NO_DISPLAY){
        eglTerminate(mEglDisplay);
        mEglDisplay = EGL_NO_DISPLAY;
    }
}
