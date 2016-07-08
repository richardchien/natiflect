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

    template<typename T>
    Object<T>::Object(JNIEnv *env, Class clz, const char *constructor_sig, ...) {
        env_ = env;
        clz_ = clz.GetJClass();
        va_list args;
        va_start(args, constructor_sig);
        val_ = (T) clz.NewInstanceV(constructor_sig, args);
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

#pragma mark - Instance Field

    template<typename T>
    jboolean Object<T>::Get_Z(const char *name) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "Z");
        jboolean result = env_->GetBooleanField(val_, field_id);
        CheckAccessFieldException(env_, name, "Z");
        return result;
    }

    template<typename T>
    void Object<T>::Set_Z(const char *name, jboolean value) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "Z");
        env_->SetBooleanField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "Z");
    }

    template<typename T>
    jbyte Object<T>::Get_B(const char *name) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "B");
        jbyte result = env_->GetByteField(val_, field_id);
        CheckAccessFieldException(env_, name, "B");
        return result;
    }

    template<typename T>
    void Object<T>::Set_B(const char *name, jbyte value) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "B");
        env_->SetByteField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "B");
    }

    template<typename T>
    jchar Object<T>::Get_C(const char *name) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "C");
        jchar result = env_->GetCharField(val_, field_id);
        CheckAccessFieldException(env_, name, "C");
        return result;
    }

    template<typename T>
    void Object<T>::Set_C(const char *name, jchar value) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "C");
        env_->SetCharField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "C");
    }

    template<typename T>
    jshort Object<T>::Get_S(const char *name) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "S");
        jshort result = env_->GetShortField(val_, field_id);
        CheckAccessFieldException(env_, name, "S");
        return result;
    }

    template<typename T>
    void Object<T>::Set_S(const char *name, jshort value) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "S");
        env_->SetShortField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "S");
    }

    template<typename T>
    jint Object<T>::Get_I(const char *name) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "I");
        jint result = env_->GetIntField(val_, field_id);
        CheckAccessFieldException(env_, name, "I");
        return result;
    }

    template<typename T>
    void Object<T>::Set_I(const char *name, jint value) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "I");
        env_->SetIntField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "I");
    }

    template<typename T>
    jlong Object<T>::Get_J(const char *name) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "J");
        jlong result = env_->GetLongField(val_, field_id);
        CheckAccessFieldException(env_, name, "J");
        return result;
    }

    template<typename T>
    void Object<T>::Set_J(const char *name, jlong value) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "J");
        env_->SetLongField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "J");
    }

    template<typename T>
    jfloat Object<T>::Get_F(const char *name) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "F");
        jfloat result = env_->GetFloatField(val_, field_id);
        CheckAccessFieldException(env_, name, "F");
        return result;
    }

    template<typename T>
    void Object<T>::Set_F(const char *name, jfloat value) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "F");
        env_->SetFloatField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "F");
    }

    template<typename T>
    jdouble Object<T>::Get_D(const char *name) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "D");
        jdouble result = env_->GetDoubleField(val_, field_id);
        CheckAccessFieldException(env_, name, "D");
        return result;
    }

    template<typename T>
    void Object<T>::Set_D(const char *name, jdouble value) {
        jfieldID field_id = GetFieldID(env_, clz_, name, "D");
        env_->SetDoubleField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "D");
    }

    template<typename T>
    jobject Object<T>::Get_L(const char *name, const char *sig) {
        jfieldID field_id = GetFieldID(env_, clz_, name, sig);
        jobject result = env_->GetObjectField(val_, field_id);
        CheckAccessFieldException(env_, name, sig);
        return result;
    }

    template<typename T>
    void Object<T>::Set_L(const char *name, const char *sig, jobject value) {
        jfieldID field_id = GetFieldID(env_, clz_, name, sig);
        env_->SetObjectField(val_, field_id, value);
        CheckAccessFieldException(env_, name, sig);
    }
}

#include "object_template_explicit.h"
