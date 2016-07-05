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

#include "exception.h"

namespace natiflect {
    Exception::Exception() {
        msg = "";
    }

    Exception::Exception(const char *msg) {
        this->msg = msg;
    }

    NoSuchClassException::NoSuchClassException() {
        msg = string("Cannot find class.");
    }

    NoSuchClassException::NoSuchClassException(const char *name) {
        msg = string("Cannot find class \"")
              + string(name)
              + "\".";
    }

    NoSuchStaticMethodException::NoSuchStaticMethodException() {
        msg = string("Cannot find static method.");
    }

    NoSuchStaticMethodException::NoSuchStaticMethodException(const char *name, const char *sig) {
        msg = string("Cannot find static method \"")
              + string(name)
              + "\" with signature \""
              + string(sig)
              + "\".";
    }

    NoSuchMethodException::NoSuchMethodException() {
        msg = string("Cannot find method.");
    }

    NoSuchMethodException::NoSuchMethodException(const char *name, const char *sig) {
        msg = string("Cannot find method \"")
              + string(name)
              + "\" with signature \""
              + string(sig)
              + "\".";
    }

    InvokeException::InvokeException() {
        msg = string("Invoke method failed.");
    }

    InvokeException::InvokeException(const char *name, const char *sig) {
        msg = string("Invoke method \"")
              + string(name)
              + "\" with signature \""
              + string(sig)
              + "\" failed.";
    }
}
