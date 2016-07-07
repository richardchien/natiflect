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

namespace natiflect {

#pragma mark - Public

    Class::Class(JNIEnv *env, const char *name) {
        env_ = env;
        val_ = env_->FindClass(name);
        if (env_->ExceptionCheck()) {
            env_->ExceptionClear();
            throw NotFoundException(string("Cannot find class \"") + name + "\".");
        }
    }

#pragma mark -- Static Method

    void Class::CallStatic_V(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        env_->CallStaticVoidMethodV(val_, method_id, args);
        CheckCallMethodException(name, sig, args);
        va_end(args);
    }

    jboolean Class::CallStatic_Z(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jboolean result = env_->CallStaticBooleanMethodV(val_, method_id, args);
        CheckCallMethodException(name, sig, args);
        va_end(args);
        return result;
    }

    jbyte Class::CallStatic_B(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jbyte result = env_->CallStaticByteMethodV(val_, method_id, args);
        CheckCallMethodException(name, sig, args);
        va_end(args);
        return result;
    }

    jchar Class::CallStatic_C(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jchar result = env_->CallStaticCharMethodV(val_, method_id, args);
        CheckCallMethodException(name, sig, args);
        va_end(args);
        return result;
    }

    jshort Class::CallStatic_S(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jshort result = env_->CallStaticShortMethodV(val_, method_id, args);
        CheckCallMethodException(name, sig, args);
        va_end(args);
        return result;
    }

    jint Class::CallStatic_I(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jint result = env_->CallStaticIntMethodV(val_, method_id, args);
        CheckCallMethodException(name, sig, args);
        va_end(args);
        return result;
    }

    jlong Class::CallStatic_J(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jlong result = env_->CallStaticLongMethodV(val_, method_id, args);
        CheckCallMethodException(name, sig, args);
        va_end(args);
        return result;
    }

    jfloat Class::CallStatic_F(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jfloat result = env_->CallStaticFloatMethodV(val_, method_id, args);
        CheckCallMethodException(name, sig, args);
        va_end(args);
        return result;
    }

    jdouble Class::CallStatic_D(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jdouble result = env_->CallStaticDoubleMethodV(val_, method_id, args);
        CheckCallMethodException(name, sig, args);
        va_end(args);
        return result;
    }

    jobject Class::CallStatic_L(const char *name, const char *sig, ...) {
        jmethodID method_id = GetStaticMethodID(name, sig);

        va_list args;
        va_start(args, sig);
        jobject result = env_->CallStaticObjectMethodV(val_, method_id, args);
        CheckCallMethodException(name, sig, args);
        va_end(args);
        return result;
    }

#pragma mark -- Static Field

    jboolean Class::GetStatic_Z(const char *name) {
        jfieldID field_id = GetStaticFieldID(name, "Z");
        jboolean result = env_->GetStaticBooleanField(val_, field_id);
        CheckAccessFieldException(name, "Z");
        return result;
    }

    void Class::SetStatic_Z(const char *name, jboolean value) {
        jfieldID field_id = GetStaticFieldID(name, "Z");
        env_->SetStaticBooleanField(val_, field_id, value);
        CheckAccessFieldException(name, "Z");
    }

    jbyte Class::GetStatic_B(const char *name) {
        jfieldID field_id = GetStaticFieldID(name, "B");
        jbyte result = env_->GetStaticByteField(val_, field_id);
        CheckAccessFieldException(name, "B");
        return result;
    }

    void Class::SetStatic_B(const char *name, jbyte value) {
        jfieldID field_id = GetStaticFieldID(name, "B");
        env_->SetStaticByteField(val_, field_id, value);
        CheckAccessFieldException(name, "B");
    }

    jchar Class::GetStatic_C(const char *name) {
        jfieldID field_id = GetStaticFieldID(name, "C");
        jchar result = env_->GetStaticCharField(val_, field_id);
        CheckAccessFieldException(name, "C");
        return result;
    }

    void Class::SetStatic_C(const char *name, jchar value) {
        jfieldID field_id = GetStaticFieldID(name, "C");
        env_->SetStaticCharField(val_, field_id, value);
        CheckAccessFieldException(name, "C");
    }

    jshort Class::GetStatic_S(const char *name) {
        jfieldID field_id = GetStaticFieldID(name, "S");
        jshort result = env_->GetStaticShortField(val_, field_id);
        CheckAccessFieldException(name, "S");
        return result;
    }

    void Class::SetStatic_S(const char *name, jshort value) {
        jfieldID field_id = GetStaticFieldID(name, "S");
        env_->SetStaticShortField(val_, field_id, value);
        CheckAccessFieldException(name, "S");
    }

    jint Class::GetStatic_I(const char *name) {
        jfieldID field_id = GetStaticFieldID(name, "I");
        jint result = env_->GetStaticIntField(val_, field_id);
        CheckAccessFieldException(name, "I");
        return result;
    }

    void Class::SetStatic_I(const char *name, jint value) {
        jfieldID field_id = GetStaticFieldID(name, "I");
        env_->SetStaticIntField(val_, field_id, value);
        CheckAccessFieldException(name, "I");
    }

    jlong Class::GetStatic_J(const char *name) {
        jfieldID field_id = GetStaticFieldID(name, "J");
        jlong result = env_->GetStaticLongField(val_, field_id);
        CheckAccessFieldException(name, "J");
        return result;
    }

    void Class::SetStatic_J(const char *name, jlong value) {
        jfieldID field_id = GetStaticFieldID(name, "J");
        env_->SetStaticLongField(val_, field_id, value);
        CheckAccessFieldException(name, "J");
    }

    jfloat Class::GetStatic_F(const char *name) {
        jfieldID field_id = GetStaticFieldID(name, "F");
        jfloat result = env_->GetStaticFloatField(val_, field_id);
        CheckAccessFieldException(name, "F");
        return result;
    }

    void Class::SetStatic_F(const char *name, jfloat value) {
        jfieldID field_id = GetStaticFieldID(name, "F");
        env_->SetStaticFloatField(val_, field_id, value);
        CheckAccessFieldException(name, "F");
    }

    jdouble Class::GetStatic_D(const char *name) {
        jfieldID field_id = GetStaticFieldID(name, "D");
        jdouble result = env_->GetStaticDoubleField(val_, field_id);
        CheckAccessFieldException(name, "D");
        return result;
    }

    void Class::SetStatic_D(const char *name, jdouble value) {
        jfieldID field_id = GetStaticFieldID(name, "D");
        env_->SetStaticDoubleField(val_, field_id, value);
        CheckAccessFieldException(name, "D");
    }

    jobject Class::GetStatic_L(const char *name, const char *sig) {
        jfieldID field_id = GetStaticFieldID(name, sig);
        jobject result = env_->GetStaticObjectField(val_, field_id);
        CheckAccessFieldException(name, sig);
        return result;
    }

    void Class::SetStatic_L(const char *name, const char *sig, jobject value) {
        jfieldID field_id = GetStaticFieldID(name, sig);
        env_->SetStaticObjectField(val_, field_id, value);
        CheckAccessFieldException(name, sig);
    }

#pragma mark -- Class

    Class Class::GetSuperClass() {
        return Class(env_, env_->GetSuperclass(val_));
    }

#pragma mark - Private

    jmethodID Class::GetStaticMethodID(const char *name, const char *sig) {
        jmethodID method_id = env_->GetStaticMethodID(val_, name, sig);
        if (env_->ExceptionCheck()) {
            env_->ExceptionClear();
            throw NotFoundException(string("Cannot find static method \"")
                                    + name + "\" with signature \"" + sig + "\".");
        }
        return method_id;
    }

    void Class::CheckCallMethodException(const char *name, const char *sig, va_list args) {
        if (env_->ExceptionCheck()) {
            env_->ExceptionClear();
            va_end(args);
            throw InvokeException(string("Call static method \"")
                                  + name + "\" with signature \"" + sig + "\" failed.");
        }
    }

    jfieldID Class::GetStaticFieldID(const char *name, const char *sig) {
        jfieldID field_id = env_->GetStaticFieldID(val_, name, sig);
        if (env_->ExceptionCheck()) {
            env_->ExceptionClear();
            throw NotFoundException(string("Cannot find static field \"")
                                    + name + "\" with signature \"" + sig + "\".");
        }
        return field_id;
    }

    void Class::CheckAccessFieldException(const char *name, const char *sig) {
        if (env_->ExceptionCheck()) {
            env_->ExceptionClear();
            throw AccessException(string("Access static field \"")
                                  + name + "\" with signature \"" + sig + "\" failed.");
        }
    }
}