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

#ifndef NATIFLECT_EXCEPTION_H
#define NATIFLECT_EXCEPTION_H

#include <string>

using namespace std;

namespace natiflect {

    struct Exception {
    public:
        Exception() { msg = "Exception occurred."; };

        Exception(string message) { msg = "Exception: " + message; };

        string msg;
    };

    struct NotFoundException : Exception {
    public:
        NotFoundException() { };

        NotFoundException(string message) : Exception(message) { };
    };

    struct InvokeException : Exception {
    public:
        InvokeException() { };

        InvokeException(string message) : Exception(message) { };
    };

    struct AccessException : Exception {
    public:
        AccessException() { };

        AccessException(string message) : Exception(message) { };
    };
}

#endif //NATIFLECT_EXCEPTION_H
