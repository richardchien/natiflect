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
// Created by Richard Chien on 7/6/16.
//

#ifndef NATIFLECT_OBJECT_H
#define NATIFLECT_OBJECT_H

#include <jni.h>

#include "exception.h"

namespace natiflect {

    class Class;

    template<typename T>
    class Object {
    public:
        Object(JNIEnv *env, T val);

#pragma mark - Base

        T GetValue();

        void SetValue(T val);

        Class GetClass();

        bool Equals(Object<T> other);

        bool Equals(jobject other);

#pragma mark - Instance Method

        void Call_V(const char *name, const char *sig = "()V", ...);

        jboolean Call_Z(const char *name, const char *sig = "()Z", ...);

        jbyte Call_B(const char *name, const char *sig = "()B", ...);

        jchar Call_C(const char *name, const char *sig = "()C", ...);

        jshort Call_S(const char *name, const char *sig = "()S", ...);

        jint Call_I(const char *name, const char *sig = "()I", ...);

        jlong Call_J(const char *name, const char *sig = "()J", ...);

        jfloat Call_F(const char *name, const char *sig = "()F", ...);

        jdouble Call_D(const char *name, const char *sig = "()D", ...);

        jobject Call_L(const char *name, const char *sig, ...);

    protected:
        Object() { };

        JNIEnv *env_;
        T val_;
        jclass clz_;
    };
}

#endif //NATIFLECT_OBJECT_H
