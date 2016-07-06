//
// Created by Richard Chien on 7/5/16.
//

#include "natiflect_test.h"

#include <iostream>

#include "natiflect/class.h"

using namespace std;
using namespace natiflect;

void LogTestPass(string test_name, bool passed) {
    cout << "Test \"" << test_name << "\" passed? " << (passed ? "YES" : "NO") << endl;
}

void TestClassConstructor(JNIEnv *env) {
    const string TAG = "TestClassConstructor";

    bool passed = true;

    try {
        jclass j_clz = env->FindClass("java/lang/String");
        Class clz1(env, j_clz);
        Class clz2(env, "java/lang/String");
    } catch (Exception e) {
        passed = false;
    }

    try {
        Class clz(env, "java/lang/string"); // should fail
        passed = false;
    } catch (Exception e) {
    }

    LogTestPass(TAG, passed);
}

void TestClassCall_V(JNIEnv *env) {
    const string TAG = "TestClassCall_V";

    bool passed = true;

    try {
        Class clz(env, "java/util/Arrays");
        jintArray j_arr = env->NewIntArray(5);
        int arr[5] = {3, 4, 2, 5, 1};
        env->SetIntArrayRegion(j_arr, 0, 5, arr);
        clz.Call_V("sort", "([I)V", j_arr);
        env->GetIntArrayRegion(j_arr, 0, 5, arr);
        int correct_arr[5] = {1, 2, 3, 4, 5};
        for (int i = 0; i < 5; i++) {
            if (arr[i] != correct_arr[i]) {
                passed = false;
                break;
            }
        }
    } catch (Exception e) {
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCall_Z(JNIEnv *env) {
    const string TAG = "TestClassCall_Z";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Character");
        if (!clz.Call_Z("isDigit", "(I)Z", '0'/*code point 48*/)) {
            passed = false;
        }
    } catch (Exception e) {
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCall_B(JNIEnv *env) {
    const string TAG = "TestClassCall_B";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Byte");
        jstring str = env->NewStringUTF("123");
        jbyte b = clz.Call_B("parseByte", "(Ljava/lang/String;)B", str);
        if (b != 123) {
            passed = false;
        }
    } catch (Exception e) {
        passed = false;
    }

    LogTestPass(TAG, passed);
}

extern "C" {

JNIEXPORT void JNICALL Java_im_r_1c_java_Main_nativeTestAll(JNIEnv *env, jclass type) {
    TestClassConstructor(env);
    TestClassCall_V(env);
    TestClassCall_Z(env);
    TestClassCall_B(env);
}

}
