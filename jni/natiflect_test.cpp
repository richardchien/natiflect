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

void TestClassCall_C(JNIEnv *env) {
    const string TAG = "TestClassCall_C";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Character");
        jchar c = clz.Call_C("forDigit", "(II)C", 1, 10);
        if (c != '1') {
            passed = false;
        }
    } catch (Exception e) {
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCall_S(JNIEnv *env) {
    const string TAG = "TestClassCall_S";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Short");
        jstring str = env->NewStringUTF("123");
        jshort s = clz.Call_S("parseShort", "(Ljava/lang/String;)S", str);
        if (s != 123) {
            passed = false;
        }
    } catch (Exception e) {
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCall_I(JNIEnv *env) {
    const string TAG = "TestClassCall_I";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Integer");
        if (clz.Call_I("compare", "(II)I", 1, 2) != -1) {
            passed = false;
        }
    } catch (Exception e) {
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCall_J(JNIEnv *env) {
    const string TAG = "TestClassCall_J";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Long");
        if (clz.Call_J("max", "(JJ)J", 1, 2) != 2) {
            passed = false;
        }
    } catch (Exception e) {
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCall_F(JNIEnv *env) {
    const string TAG = "TestClassCall_F";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Float");
        if (clz.Call_F("max", "(FF)F", 1.5f, 2.0f) != 2.0f) {
            passed = false;
        }
    } catch (Exception e) {
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCall_D(JNIEnv *env) {
    const string TAG = "TestClassCall_D";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Double");
        if (clz.Call_D("max", "(DD)D", 1.5, 2.0) != 2.0) {
            passed = false;
        }
    } catch (Exception e) {
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCall_L(JNIEnv *env) {
    const string TAG = "TestClassCall_L";

    bool passed = true;

    try {
        Class clz(env, "java/lang/String");
        jstring str = (jstring) clz.Call_L("valueOf", "(I)Ljava/lang/String;", 123);
        if (env->GetStringLength(str) != 3) {
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
    TestClassCall_C(env);
    TestClassCall_S(env);
    TestClassCall_I(env);
    TestClassCall_J(env);
    TestClassCall_F(env);
    TestClassCall_D(env);
    TestClassCall_L(env);
}

}
