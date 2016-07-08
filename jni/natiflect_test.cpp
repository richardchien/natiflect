//
// Created by Richard Chien on 7/5/16.
//

#include "natiflect_test.h"

#include <iostream>
#include <vector>

#include "natiflect/object.h"
#include "natiflect/class.h"

using namespace std;
using namespace natiflect;

int total_count = 0;
int passed_count = 0;

vector<string> tests_not_passed;

void LogTestPass(string test_name, bool passed) {
    total_count++;
    if (passed) {
        passed_count++;
    } else {
        tests_not_passed.push_back(test_name);
    }
    cout << test_name << " passed? " << (passed ? "YES" : "NO") << endl;
}

void TestException(JNIEnv *env) {
    const string TAG = "TestException";

    bool passed = true;

    try {
        throw Exception();
    } catch (Exception e) {
        if (e.msg != "Exception occurred.") {
            passed = false;
        }
    }

    try {
        throw Exception("error");
    } catch (Exception e) {
        if (e.msg.substr(0, 10) != "Exception:") {
            passed = false;
        }
    }

    LogTestPass(TAG, passed);
}

void TestObjectEquals(JNIEnv *env) {
    const string TAG = "TestObjectEquals";

    bool passed = true;

    try {
        jclass clz1 = env->FindClass("java/lang/String");
        jclass clz2 = env->FindClass("java/lang/String");
        if (!(clz1 != clz2 && Object<jclass>(env, clz1).Equals(clz2))) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectGetSetValue(JNIEnv *env) {
    const string TAG = "TestObjectGetSetValue";

    bool passed = true;

    try {
        jclass clz_string = env->FindClass("java/lang/String");
        jstring str = env->NewStringUTF("abc");
        jintArray int_arr = env->NewIntArray(1);
        Object<jobject> obj(env, str);
        if (obj.GetValue() != str) {
            passed = false;
        }
        obj.SetValue(int_arr);
        jclass clz_int_arr = env->GetObjectClass(int_arr);
        if (!Class(env, clz_int_arr).Equals(obj.GetClass())) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassGetSuperClass(JNIEnv *env) {
    const string TAG = "TestClassGetSuperClass";

    bool passed = true;

    try {
        Class clz_string(env, "java/lang/String");
        Class clz_object(env, "java/lang/Object");
        if (!clz_string.GetSuperClass().Equals(clz_object)) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassNewInstance(JNIEnv *env) {
    const string TAG = "TestClassNewInstance";

    bool passed = true;

    try {
        jstring str1 = env->NewStringUTF("abc");
        Class clz_string(env, "java/lang/String");
        jstring str2 = (jstring) clz_string.NewInstance("(Ljava/lang/String;)V", str1);
        if (env->GetStringLength(str2) != 3) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCallStatic_V(JNIEnv *env) {
    const string TAG = "TestClassCallStatic_V";

    bool passed = true;

    try {
        Class clz(env, "java/util/Arrays");
        jintArray j_arr = env->NewIntArray(5);
        int arr[5] = {3, 4, 2, 5, 1};
        env->SetIntArrayRegion(j_arr, 0, 5, arr);
        clz.CallStatic_V("sort", "([I)V", j_arr);
        env->GetIntArrayRegion(j_arr, 0, 5, arr);
        int correct_arr[5] = {1, 2, 3, 4, 5};
        for (int i = 0; i < 5; i++) {
            if (arr[i] != correct_arr[i]) {
                passed = false;
                break;
            }
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCallStatic_Z(JNIEnv *env) {
    const string TAG = "TestClassCallStatic_Z";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Character");
        if (!clz.CallStatic_Z("isDigit", "(I)Z", '0'/*code point 48*/)) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCallStatic_B(JNIEnv *env) {
    const string TAG = "TestClassCallStatic_B";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Byte");
        jstring str = env->NewStringUTF("123");
        jbyte b = clz.CallStatic_B("parseByte", "(Ljava/lang/String;)B", str);
        if (b != 123) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCallStatic_C(JNIEnv *env) {
    const string TAG = "TestClassCallStatic_C";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Character");
        jchar c = clz.CallStatic_C("forDigit", "(II)C", 1, 10);
        if (c != '1') {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCallStatic_S(JNIEnv *env) {
    const string TAG = "TestClassCallStatic_S";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Short");
        jstring str = env->NewStringUTF("123");
        jshort s = clz.CallStatic_S("parseShort", "(Ljava/lang/String;)S", str);
        if (s != 123) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCallStatic_I(JNIEnv *env) {
    const string TAG = "TestClassCallStatic_I";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Integer");
        if (clz.CallStatic_I("compare", "(II)I", 1, 2) != -1) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCallStatic_J(JNIEnv *env) {
    const string TAG = "TestClassCallStatic_J";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Long");
        if (clz.CallStatic_J("max", "(JJ)J", 1, 2) != 2) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCallStatic_F(JNIEnv *env) {
    const string TAG = "TestClassCallStatic_F";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Float");
        if (clz.CallStatic_F("max", "(FF)F", 1.5f, 2.0f) != 2.0f) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCallStatic_D(JNIEnv *env) {
    const string TAG = "TestClassCallStatic_D";

    bool passed = true;

    try {
        Class clz(env, "java/lang/Double");
        if (clz.CallStatic_D("max", "(DD)D", 1.5, 2.0) != 2.0) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassCallStatic_L(JNIEnv *env) {
    const string TAG = "TestClassCallStatic_L";

    bool passed = true;

    try {
        Class clz(env, "java/lang/String");
        jstring str = (jstring) clz.CallStatic_L("valueOf", "(I)Ljava/lang/String;", 123);
        if (env->GetStringLength(str) != 3) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassGetSetStatic_Z(JNIEnv *env) {
    const string TAG = "TestClassGetSetStatic_Z";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/StaticFieldTest");
        clz.SetStatic_Z("sBoolean", 1);
        if (clz.GetStatic_Z("sBoolean") != 1) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassGetSetStatic_B(JNIEnv *env) {
    const string TAG = "TestClassGetSetStatic_B";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/StaticFieldTest");
        clz.SetStatic_B("sByte", 1);
        if (clz.GetStatic_B("sByte") != 1) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassGetSetStatic_C(JNIEnv *env) {
    const string TAG = "TestClassGetSetStatic_C";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/StaticFieldTest");
        clz.SetStatic_C("sChar", 'a');
        if (clz.GetStatic_C("sChar") != 'a') {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassGetSetStatic_S(JNIEnv *env) {
    const string TAG = "TestClassGetSetStatic_S";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/StaticFieldTest");
        clz.SetStatic_S("sShort", 1);
        if (clz.GetStatic_S("sShort") != 1) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassGetSetStatic_I(JNIEnv *env) {
    const string TAG = "TestClassGetSetStatic_I";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/StaticFieldTest");
        clz.SetStatic_I("sInt", 1);
        if (clz.GetStatic_I("sInt") != 1) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassGetSetStatic_J(JNIEnv *env) {
    const string TAG = "TestClassGetSetStatic_J";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/StaticFieldTest");
        clz.SetStatic_J("sLong", 1);
        if (clz.GetStatic_J("sLong") != 1) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassGetSetStatic_F(JNIEnv *env) {
    const string TAG = "TestClassGetSetStatic_F";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/StaticFieldTest");
        clz.SetStatic_F("sFloat", 1.5f);
        if (clz.GetStatic_F("sFloat") != 1.5f) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassGetSetStatic_D(JNIEnv *env) {
    const string TAG = "TestClassGetSetStatic_D";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/StaticFieldTest");
        clz.SetStatic_D("sDouble", 1.5);
        if (clz.GetStatic_D("sDouble") != 1.5) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestClassGetSetStatic_L(JNIEnv *env) {
    const string TAG = "TestClassGetSetStatic_L";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/StaticFieldTest");
        jstring str = env->NewStringUTF("abc");
        clz.SetStatic_L("sObject", "Ljava/lang/Object;", str);
        str = (jstring) clz.GetStatic_L("sObject", "Ljava/lang/Object;");
        if (env->GetStringLength(str) != 3) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectCall_V(JNIEnv *env) {
    const string TAG = "TestObjectCall_V";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        jobject obj = clz.NewInstance();
        jintArray j_arr = env->NewIntArray(1);
        Object<jobject>(env, obj).Call_V("testVoid", "([I)V", j_arr);
        int arr[1];
        env->GetIntArrayRegion(j_arr, 0, 1, arr);
        if (arr[0] != 1) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectCall_Z(JNIEnv *env) {
    const string TAG = "TestObjectCall_Z";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        jobject obj = clz.NewInstance();
        if (Object<jobject>(env, obj).Call_Z("testBoolean") != 1) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectCall_B(JNIEnv *env) {
    const string TAG = "TestObjectCall_B";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        jobject obj = clz.NewInstance();
        if (Object<jobject>(env, obj).Call_B("testByte") != 1) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectCall_C(JNIEnv *env) {
    const string TAG = "TestObjectCall_C";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        jobject obj = clz.NewInstance();
        if (Object<jobject>(env, obj).Call_C("testChar") != '1') {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectCall_S(JNIEnv *env) {
    const string TAG = "TestObjectCall_S";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        jobject obj = clz.NewInstance();
        if (Object<jobject>(env, obj).Call_S("testShort") != 1) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectCall_I(JNIEnv *env) {
    const string TAG = "TestObjectCall_I";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        jobject obj = clz.NewInstance();
        if (Object<jobject>(env, obj).Call_I("testInt") != 1) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectCall_J(JNIEnv *env) {
    const string TAG = "TestObjectCall_J";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        jobject obj = clz.NewInstance();
        if (Object<jobject>(env, obj).Call_J("testLong") != 1) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectCall_F(JNIEnv *env) {
    const string TAG = "TestObjectCall_F";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        jobject obj = clz.NewInstance();
        if (Object<jobject>(env, obj).Call_F("testFloat") != 1.5f) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectCall_D(JNIEnv *env) {
    const string TAG = "TestObjectCall_D";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        jobject obj = clz.NewInstance();
        if (Object<jobject>(env, obj).Call_D("testDouble") != 1.5) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectCall_L(JNIEnv *env) {
    const string TAG = "TestObjectCall_L";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        jobject obj = clz.NewInstance();
        jstring str = (jstring) Object<jobject>(env, obj).Call_L("testString", "()Ljava/lang/String;");
        if (env->GetStringLength(str) != 3) {
            passed = false;
        }
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectGetSet_Z(JNIEnv *env) {
    const string TAG = "TestObjectGetSet_Z";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        Object<jobject> obj(env, clz);
        obj.Set_Z("mBoolean", 1);
        if (obj.Get_Z("mBoolean") != 1) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectGetSet_B(JNIEnv *env) {
    const string TAG = "TestObjectGetSet_B";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        Object<jobject> obj(env, clz);
        obj.Set_B("mByte", 1);
        if (obj.Get_B("mByte") != 1) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectGetSet_C(JNIEnv *env) {
    const string TAG = "TestObjectGetSet_C";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        Object<jobject> obj(env, clz);
        obj.Set_C("mChar", '1');
        if (obj.Get_C("mChar") != '1') {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectGetSet_S(JNIEnv *env) {
    const string TAG = "TestObjectGetSet_S";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        Object<jobject> obj(env, clz);
        obj.Set_S("mShort", 1);
        if (obj.Get_S("mShort") != 1) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectGetSet_I(JNIEnv *env) {
    const string TAG = "TestObjectGetSet_I";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        Object<jobject> obj(env, clz);
        obj.Set_I("mInt", 1);
        if (obj.Get_I("mInt") != 1) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectGetSet_J(JNIEnv *env) {
    const string TAG = "TestObjectGetSet_J";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        Object<jobject> obj(env, clz);
        obj.Set_J("mLong", 1);
        if (obj.Get_J("mLong") != 1) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectGetSet_F(JNIEnv *env) {
    const string TAG = "TestObjectGetSet_F";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        Object<jobject> obj(env, clz);
        obj.Set_F("mFloat", 1.5f);
        if (obj.Get_F("mFloat") != 1.5f) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectGetSet_D(JNIEnv *env) {
    const string TAG = "TestObjectGetSet_D";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        Object<jobject> obj(env, clz);
        obj.Set_D("mDouble", 1.5);
        if (obj.Get_D("mDouble") != 1.5) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

void TestObjectGetSet_L(JNIEnv *env) {
    const string TAG = "TestObjectGetSet_L";

    bool passed = true;

    try {
        Class clz(env, "im/r_c/java/ObjectTest");
        Object<jobject> obj(env, clz);
        jstring str = env->NewStringUTF("abc");
        obj.Set_L("mObject", "Ljava/lang/Object;", str);
        str = (jstring) obj.Get_L("mObject", "Ljava/lang/Object;");
        if (env->GetStringLength(str) != 3) {
            passed = false;
        };
    } catch (Exception e) {
        cout << e.msg << endl;
        passed = false;
    }

    LogTestPass(TAG, passed);
}

extern "C" {

JNIEXPORT void JNICALL Java_im_r_1c_java_Main_nativeTestAll(JNIEnv *env, jclass type) {
    TestException(env);

    TestObjectEquals(env);
    TestObjectGetSetValue(env);

    TestClassGetSuperClass(env);
    TestClassNewInstance(env);

    TestClassCallStatic_V(env);
    TestClassCallStatic_Z(env);
    TestClassCallStatic_B(env);
    TestClassCallStatic_C(env);
    TestClassCallStatic_S(env);
    TestClassCallStatic_I(env);
    TestClassCallStatic_J(env);
    TestClassCallStatic_F(env);
    TestClassCallStatic_D(env);
    TestClassCallStatic_L(env);

    TestClassGetSetStatic_Z(env);
    TestClassGetSetStatic_B(env);
    TestClassGetSetStatic_C(env);
    TestClassGetSetStatic_S(env);
    TestClassGetSetStatic_I(env);
    TestClassGetSetStatic_J(env);
    TestClassGetSetStatic_F(env);
    TestClassGetSetStatic_D(env);
    TestClassGetSetStatic_L(env);

    TestObjectCall_V(env);
    TestObjectCall_Z(env);
    TestObjectCall_B(env);
    TestObjectCall_C(env);
    TestObjectCall_S(env);
    TestObjectCall_I(env);
    TestObjectCall_J(env);
    TestObjectCall_F(env);
    TestObjectCall_D(env);
    TestObjectCall_L(env);

    TestObjectGetSet_Z(env);
    TestObjectGetSet_B(env);
    TestObjectGetSet_C(env);
    TestObjectGetSet_S(env);
    TestObjectGetSet_I(env);
    TestObjectGetSet_J(env);
    TestObjectGetSet_F(env);
    TestObjectGetSet_D(env);
    TestObjectGetSet_L(env);

    cout << endl << "Tested: " << total_count << ", Passed: " << passed_count << "." << endl;
    if (tests_not_passed.size() > 0) {
        cout << "Tests didn't passed:" << endl;
    }
    for (int i = 0; i < tests_not_passed.size(); i++) {
        cout << tests_not_passed[i] << endl;
    }
}

}
