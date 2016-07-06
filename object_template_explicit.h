//
// Created by Richard Chien on 7/7/16.
//

#ifndef NATIFLECT_TEST_OBJECT_TEMPLATE_EXPLICIT_H
#define NATIFLECT_TEST_OBJECT_TEMPLATE_EXPLICIT_H

#include <jni.h>

namespace natiflect {

    template
    class Object<jobject>;

    template
    class Object<jclass>;

    template
    class Object<jstring>;

    template
    class Object<jarray>;

    template
    class Object<jobjectArray>;

    template
    class Object<jbooleanArray>;

    template
    class Object<jbyteArray>;

    template
    class Object<jcharArray>;

    template
    class Object<jshortArray>;

    template
    class Object<jintArray>;

    template
    class Object<jlongArray>;

    template
    class Object<jfloatArray>;

    template
    class Object<jdoubleArray>;

    template
    class Object<jthrowable>;
}

#endif //NATIFLECT_TEST_OBJECT_TEMPLATE_EXPLICIT_H
