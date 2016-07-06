//
// Created by Richard Chien on 7/6/16.
//

#include "object.h"

namespace natiflect {

    template<typename T>
    bool Object<T>::Equals(Object<T> other) {
        return env_->IsSameObject(val_, other.val_);
    }

    template<typename T>
    bool Object<T>::Equals(jobject other) {
        return env_->IsSameObject(val_, other);
    }
}

#include "object_template_explicit.h"
