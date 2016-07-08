# Natiflect

[![License](https://img.shields.io/github/license/mashape/apistatus.svg?maxAge=2592000)](LICENSE)

[中文](#zh) [English](#en)

<a name="zh">

在 JNI 里调用 Java 的方法得通过反射，而且使用起来比直接在 Java 里用反射更麻烦，因此 Natiflect 就是为了解决这个问题而写的，把 JNI 提供的一些函数进行了封装，利用 C++ 面向对象的特性，使 API 更加简单。

Android NDK 是使用 JNI 的，因此 Natiflect 也可以用于 NDK。

注意：Natiflect 用到了很多 C++ 的特性，所以只支持 C++。

## 用法

在源文件头部包含头文件 `natiflect.h`，并根据需要添加 `using namespace natiflect;`。

### 创建 Java 对象

```cpp
jstring str1 = env->NewStringUTF("abc");
Class clz_string(env, "java/lang/String");
jstring str2 = (jstring) clz_string.NewInstance("(Ljava/lang/String;)V", str1);
```

### 调用静态方法

```cpp
Class clz(env, "java/util/Arrays");
clz.CallStatic_V("sort", "([I)V", j_int_array);
```

### 获取／设置静态变量

```cpp
Class clz(env, "im/r_c/java/StaticFieldTest");
clz.SetStatic_Z("sBoolean", 1);
jboolean b = clz.GetStatic_Z("sBoolean");
```

### 调用实例方法

```cpp
Class clz(env, "im/r_c/java/ObjectTest");
Object<jobject> obj(env, clz.NewInstance());
jint i = obj.Call_I("testInt");
```

### 获取／设置实例变量

```cpp
Class clz(env, "im/r_c/java/ObjectTest");
Object<jobject> obj(env, clz.NewInstance());
jstring str = env->NewStringUTF("abc");
obj.Set_L("mString", "Ljava/lang/String;", str);
str = (jstring) obj.Get_L("mString", "Ljava/lang/String;");
```

### 其它

还有一些其它函数的用法可以查看源码或在 test 分支查看 [`natiflect_test.cpp`](https://github.com/richardchien/natiflect/blob/test/jni/natiflect_test.cpp) 文件。

<a name="en">

It's quite a trouble to call Java methods in JNI and Natiflect is written to make that easy.

Android NDK is using JNI, thus Natiflect can be used in NDK development as well.

Note: Some C++ features have been used, so you must use Natiflect in C++.

## Usage

在源文件头部包含头文件 `natiflect.h`，并根据需要添加 `using namespace natiflect;`。
Include header file `natiflect.h` at the beginning of your source file, and add `using namespace natiflect;` as you need.

### Create Java objects

```cpp
jstring str1 = env->NewStringUTF("abc");
Class clz_string(env, "java/lang/String");
jstring str2 = (jstring) clz_string.NewInstance("(Ljava/lang/String;)V", str1);
```

### Call static methods

```cpp
Class clz(env, "java/util/Arrays");
clz.CallStatic_V("sort", "([I)V", j_int_array);
```

### Access static fields

```cpp
Class clz(env, "im/r_c/java/StaticFieldTest");
clz.SetStatic_Z("sBoolean", 1);
jboolean b = clz.GetStatic_Z("sBoolean");
```

### Call instance methods

```cpp
Class clz(env, "im/r_c/java/ObjectTest");
Object<jobject> obj(env, clz.NewInstance());
jint i = obj.Call_I("testInt");
```

### Access instance fields

```cpp
Class clz(env, "im/r_c/java/ObjectTest");
Object<jobject> obj(env, clz.NewInstance());
jstring str = env->NewStringUTF("abc");
obj.Set_L("mString", "Ljava/lang/String;", str);
str = (jstring) obj.Get_L("mString", "Ljava/lang/String;");
```

### Other

You can refer to the source code for usage of some other functions.
