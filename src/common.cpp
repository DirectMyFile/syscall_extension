//
// Created by Kenneth Endfinger on 11/8/15.
//

#include <string.h>
#include <sys/errno.h>
#include "dart_api.h"
#include "common.h"

void CheckResultAndThrow(int err) {
    if (err != -1) {
        return;
    }

    Dart_Handle msg = Dart_NewStringFromCString(strerror(errno));

    Dart_Handle dh_class;
    Dart_Handle dh_instance;
    Dart_Handle dh_library;
    Dart_Handle list[1];

    dh_library = Dart_LookupLibrary(Dart_NewStringFromCString("dart:core"));
    dh_class = Dart_GetClass(dh_library, Dart_NewStringFromCString("Exception"));
    list[0] = msg;
    dh_instance = Dart_New(dh_class, Dart_Null(), 1, list);
    Dart_ThrowException(dh_instance);
}
