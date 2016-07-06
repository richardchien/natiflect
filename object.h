//
// Created by Richard Chien on 7/6/16.
//

#ifndef NATIFLECT_TEST_OBJECT_H
#define NATIFLECT_TEST_OBJECT_H

#include <jni.h>

namespace natiflect {

    template<typename T>
    class Object {
    public:
        Object() { };

        Object(JNIEnv *env, T val) {
            env_ = env;
            val_ = val;
        };

        T GetValue() { return val_; };

        void SetValue(T val) { val_ = val; };

        bool Equals(Object<T> other);

        bool Equals(jobject other);

    protected:
        JNIEnv *env_;
        T val_;
    };
}

#endif //NATIFLECT_TEST_OBJECT_H
