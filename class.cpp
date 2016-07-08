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

#include "class.h"

#include "utils.h"

namespace natiflect {

#pragma mark - Public

    Class::Class(JNIEnv *env, const char *name) {
        env_ = env;
        val_ = env_->FindClass(name);
        CheckNotFoundException(env_, string("class \"") + name + "\"");
    }

#pragma mark - Static Method

    void Class::CallStatic_V(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, val_, name, sig, true);

        va_list args;
        va_start(args, sig);
        env_->CallStaticVoidMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig, true);
    }

    jboolean Class::CallStatic_Z(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, val_, name, sig, true);

        va_list args;
        va_start(args, sig);
        jboolean result = env_->CallStaticBooleanMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig, true);
        return result;
    }

    jbyte Class::CallStatic_B(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, val_, name, sig, true);

        va_list args;
        va_start(args, sig);
        jbyte result = env_->CallStaticByteMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig, true);
        return result;
    }

    jchar Class::CallStatic_C(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, val_, name, sig, true);

        va_list args;
        va_start(args, sig);
        jchar result = env_->CallStaticCharMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig, true);
        return result;
    }

    jshort Class::CallStatic_S(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, val_, name, sig, true);

        va_list args;
        va_start(args, sig);
        jshort result = env_->CallStaticShortMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig, true);
        return result;
    }

    jint Class::CallStatic_I(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, val_, name, sig, true);

        va_list args;
        va_start(args, sig);
        jint result = env_->CallStaticIntMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig, true);
        return result;
    }

    jlong Class::CallStatic_J(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, val_, name, sig, true);

        va_list args;
        va_start(args, sig);
        jlong result = env_->CallStaticLongMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig, true);
        return result;
    }

    jfloat Class::CallStatic_F(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, val_, name, sig, true);

        va_list args;
        va_start(args, sig);
        jfloat result = env_->CallStaticFloatMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig, true);
        return result;
    }

    jdouble Class::CallStatic_D(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, val_, name, sig, true);

        va_list args;
        va_start(args, sig);
        jdouble result = env_->CallStaticDoubleMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig, true);
        return result;
    }

    jobject Class::CallStatic_L(const char *name, const char *sig, ...) {
        jmethodID method_id = GetMethodID(env_, val_, name, sig, true);

        va_list args;
        va_start(args, sig);
        jobject result = env_->CallStaticObjectMethodV(val_, method_id, args);
        va_end(args);
        CheckCallMethodException(env_, name, sig, true);
        return result;
    }

#pragma mark - Static Field

    jboolean Class::GetStatic_Z(const char *name) {
        jfieldID field_id = GetFieldID(env_, val_, name, "Z", true);
        jboolean result = env_->GetStaticBooleanField(val_, field_id);
        CheckAccessFieldException(env_, name, "Z", true);
        return result;
    }

    void Class::SetStatic_Z(const char *name, jboolean value) {
        jfieldID field_id = GetFieldID(env_, val_, name, "Z", true);
        env_->SetStaticBooleanField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "Z", true);
    }

    jbyte Class::GetStatic_B(const char *name) {
        jfieldID field_id = GetFieldID(env_, val_, name, "B", true);
        jbyte result = env_->GetStaticByteField(val_, field_id);
        CheckAccessFieldException(env_, name, "B", true);
        return result;
    }

    void Class::SetStatic_B(const char *name, jbyte value) {
        jfieldID field_id = GetFieldID(env_, val_, name, "B", true);
        env_->SetStaticByteField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "B", true);
    }

    jchar Class::GetStatic_C(const char *name) {
        jfieldID field_id = GetFieldID(env_, val_, name, "C", true);
        jchar result = env_->GetStaticCharField(val_, field_id);
        CheckAccessFieldException(env_, name, "C", true);
        return result;
    }

    void Class::SetStatic_C(const char *name, jchar value) {
        jfieldID field_id = GetFieldID(env_, val_, name, "C", true);
        env_->SetStaticCharField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "C", true);
    }

    jshort Class::GetStatic_S(const char *name) {
        jfieldID field_id = GetFieldID(env_, val_, name, "S", true);
        jshort result = env_->GetStaticShortField(val_, field_id);
        CheckAccessFieldException(env_, name, "S", true);
        return result;
    }

    void Class::SetStatic_S(const char *name, jshort value) {
        jfieldID field_id = GetFieldID(env_, val_, name, "S", true);
        env_->SetStaticShortField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "S", true);
    }

    jint Class::GetStatic_I(const char *name) {
        jfieldID field_id = GetFieldID(env_, val_, name, "I", true);
        jint result = env_->GetStaticIntField(val_, field_id);
        CheckAccessFieldException(env_, name, "I", true);
        return result;
    }

    void Class::SetStatic_I(const char *name, jint value) {
        jfieldID field_id = GetFieldID(env_, val_, name, "I", true);
        env_->SetStaticIntField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "I", true);
    }

    jlong Class::GetStatic_J(const char *name) {
        jfieldID field_id = GetFieldID(env_, val_, name, "J", true);
        jlong result = env_->GetStaticLongField(val_, field_id);
        CheckAccessFieldException(env_, name, "J", true);
        return result;
    }

    void Class::SetStatic_J(const char *name, jlong value) {
        jfieldID field_id = GetFieldID(env_, val_, name, "J", true);
        env_->SetStaticLongField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "J", true);
    }

    jfloat Class::GetStatic_F(const char *name) {
        jfieldID field_id = GetFieldID(env_, val_, name, "F", true);
        jfloat result = env_->GetStaticFloatField(val_, field_id);
        CheckAccessFieldException(env_, name, "F", true);
        return result;
    }

    void Class::SetStatic_F(const char *name, jfloat value) {
        jfieldID field_id = GetFieldID(env_, val_, name, "F", true);
        env_->SetStaticFloatField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "F", true);
    }

    jdouble Class::GetStatic_D(const char *name) {
        jfieldID field_id = GetFieldID(env_, val_, name, "D", true);
        jdouble result = env_->GetStaticDoubleField(val_, field_id);
        CheckAccessFieldException(env_, name, "D", true);
        return result;
    }

    void Class::SetStatic_D(const char *name, jdouble value) {
        jfieldID field_id = GetFieldID(env_, val_, name, "D", true);
        env_->SetStaticDoubleField(val_, field_id, value);
        CheckAccessFieldException(env_, name, "D", true);
    }

    jobject Class::GetStatic_L(const char *name, const char *sig) {
        jfieldID field_id = GetFieldID(env_, val_, name, sig, true);
        jobject result = env_->GetStaticObjectField(val_, field_id);
        CheckAccessFieldException(env_, name, sig, true);
        return result;
    }

    void Class::SetStatic_L(const char *name, const char *sig, jobject value) {
        jfieldID field_id = GetFieldID(env_, val_, name, sig, true);
        env_->SetStaticObjectField(val_, field_id, value);
        CheckAccessFieldException(env_, name, sig, true);
    }

#pragma mark - Instance Method

    Class Class::GetSuperClass() {
        return Class(env_, env_->GetSuperclass(val_));
    }

    jobject Class::NewInstance(const char *constructor_sig, ...) {
        jmethodID constructor = GetMethodID(env_, val_, "<init>", constructor_sig);
        va_list args;
        va_start(args, constructor_sig);
        jobject result = env_->NewObjectV(val_, constructor, args);
        va_end(args);
        CheckCallMethodException(env_, "<init>", constructor_sig);
        return result;
    }
}
