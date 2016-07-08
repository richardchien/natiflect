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

#include "object.h"

#include "utils.h"
#include "class.h"

namespace natiflect {

    template<typename T>
    Object<T>::Object(JNIEnv *env, T val) {
        env_ = env;
        val_ = val;
        clz_ = env_->GetObjectClass(val_);
        CheckNotFoundException(env_, "class of the object");
    }

#pragma mark - Base

    template<typename T>
    T Object<T>::GetValue() {
        return val_;
    };

    template<typename T>
    void Object<T>::SetValue(T val) {
        val_ = val;
        clz_ = env_->GetObjectClass(val_);
        CheckNotFoundException(env_, "class of the object");
    };

    template<typename T>
    Class Object<T>::GetClass() {
        return Class(env_, clz_);
    }

    template<typename T>
    bool Object<T>::Equals(Object<T> other) {
        return env_->IsSameObject(val_, other.val_);
    }

    template<typename T>
    bool Object<T>::Equals(jobject other) {
        return env_->IsSameObject(val_, other);
    }

#pragma mark - Instance Method

    template<typename T>
    void Object<T>::Call_V(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, clz_, name, sig);
        va_list args;
        va_start(args, sig);
        env_->CallVoidMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig);
    }

    template<typename T>
    jboolean Object<T>::Call_Z(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, clz_, name, sig);
        va_list args;
        va_start(args, sig);
        jboolean result = env_->CallBooleanMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig);
        return result;
    }

    template<typename T>
    jbyte Object<T>::Call_B(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, clz_, name, sig);
        va_list args;
        va_start(args, sig);
        jbyte result = env_->CallByteMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig);
        return result;
    }

    template<typename T>
    jchar Object<T>::Call_C(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, clz_, name, sig);
        va_list args;
        va_start(args, sig);
        jchar result = env_->CallCharMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig);
        return result;
    }

    template<typename T>
    jshort Object<T>::Call_S(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, clz_, name, sig);
        va_list args;
        va_start(args, sig);
        jshort result = env_->CallShortMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig);
        return result;
    }

    template<typename T>
    jint Object<T>::Call_I(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, clz_, name, sig);
        va_list args;
        va_start(args, sig);
        jint result = env_->CallIntMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig);
        return result;
    }

    template<typename T>
    jlong Object<T>::Call_J(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, clz_, name, sig);
        va_list args;
        va_start(args, sig);
        jlong result = env_->CallLongMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig);
        return result;
    }

    template<typename T>
    jfloat Object<T>::Call_F(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, clz_, name, sig);
        va_list args;
        va_start(args, sig);
        jfloat result = env_->CallFloatMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig);
        return result;
    }

    template<typename T>
    jdouble Object<T>::Call_D(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, clz_, name, sig);
        va_list args;
        va_start(args, sig);
        jdouble result = env_->CallDoubleMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig);
        return result;
    }

    template<typename T>
    jobject Object<T>::Call_L(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, clz_, name, sig);
        va_list args;
        va_start(args, sig);
        jobject result = env_->CallObjectMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig);
        return result;
    }
}

#include "object_template_explicit.h"
