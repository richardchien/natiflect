//
// Copyright (c) 2016 Richard Chien
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//
// Created by Richard Chien on 7/7/16.
//

#ifndef NATIFLECT_UTILS_H
#define NATIFLECT_UTILS_H

#include <jni.h>

namespace natiflect {

    jmethodID GetMethodID(JNIEnv *env, jclass clz, const char *name, const char *sig, bool is_static = false);

    void CheckCallMethodException(JNIEnv *env, const char *name, const char *sig, va_list args, bool is_static = false);

    jfieldID GetFieldID(JNIEnv *env, jclass clz, const char *name, const char *sig, bool is_static = false);

    void CheckAccessFieldException(JNIEnv *env, const char *name, const char *sig, bool is_static = false);
}

#endif //NATIFLECT_UTILS_H
