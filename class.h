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
// Created by Richard Chien on 7/5/16.
//

#ifndef NATIFLECT_CLASS_H
#define NATIFLECT_CLASS_H

#include <jni.h>

#include "exception.h"
#include "object.h"

namespace natiflect {

    class Class : public Object<jclass> {
    public:
        Class(JNIEnv *env, jclass clz) : Object(env, clz) { };

        Class(JNIEnv *env, const char *name);

        jclass GetJClass() { return GetValue(); };

        void SetJClass(jclass clz) { SetValue(clz); }

#pragma mark - Static Method

        void CallStatic_V(const char *name, const char *sig, ...);

        jboolean CallStatic_Z(const char *name, const char *sig, ...);

        jbyte CallStatic_B(const char *name, const char *sig, ...);

        jchar CallStatic_C(const char *name, const char *sig, ...);

        jshort CallStatic_S(const char *name, const char *sig, ...);

        jint CallStatic_I(const char *name, const char *sig, ...);

        jlong CallStatic_J(const char *name, const char *sig, ...);

        jfloat CallStatic_F(const char *name, const char *sig, ...);

        jdouble CallStatic_D(const char *name, const char *sig, ...);

        jobject CallStatic_L(const char *name, const char *sig, ...);

#pragma mark - Static Field

        jboolean GetStatic_Z(const char *name);

        void SetStatic_Z(const char *name, jboolean value);

        jbyte GetStatic_B(const char *name);

        void SetStatic_B(const char *name, jbyte value);

        jchar GetStatic_C(const char *name);

        void SetStatic_C(const char *name, jchar value);

        jshort GetStatic_S(const char *name);

        void SetStatic_S(const char *name, jshort value);

        jint GetStatic_I(const char *name);

        void SetStatic_I(const char *name, jint value);

        jlong GetStatic_J(const char *name);

        void SetStatic_J(const char *name, jlong value);

        jfloat GetStatic_F(const char *name);

        void SetStatic_F(const char *name, jfloat value);

        jdouble GetStatic_D(const char *name);

        void SetStatic_D(const char *name, jdouble value);

        jobject GetStatic_L(const char *name, const char *sig);

        void SetStatic_L(const char *name, const char *sig, jobject value);

#pragma mark - Instance Method

        Class GetSuperClass();

    private:
        jmethodID GetStaticMethodID(const char *name, const char *sig);

        void CheckCallMethodException(const char *name, const char *sig, va_list args);

        jfieldID GetStaticFieldID(const char *name, const char *sig);

        void CheckAccessFieldException(const char *name, const char *sig);
    };
}

#endif //NATIFLECT_CLASS_H
