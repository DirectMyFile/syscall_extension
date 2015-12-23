#include <string.h>

#include "dart_api.h"
#include "os.h"

Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool* auto_setup_scope);

Dart_Handle HandleError(Dart_Handle handle) {
    if (Dart_IsError(handle)) Dart_PropagateError(handle);
    return handle;
}

DART_EXPORT Dart_Handle syscall_extension_Init(Dart_Handle parent_library) {
    if (Dart_IsError(parent_library)) return parent_library;

    Dart_Handle result_code =
            Dart_SetNativeResolver(parent_library, ResolveName, NULL);
    if (Dart_IsError(result_code)) return result_code;

    return Dart_Null();
}


void Syscall_Sync(Dart_NativeArguments arguments) {
    FileSystem_Sync();
}

void Syscall_GetFileDescriptor(Dart_NativeArguments arguments) {
    Dart_Handle raf = HandleError(Dart_GetNativeArgument(arguments, 0));
    Dart_Handle id = HandleError(Dart_GetField(raf, Dart_NewStringFromCString("_id")));
    Dart_Handle *args = {&id};
    Dart_Handle type = HandleError(Dart_InstanceGetType(raf));
    Dart_Handle result = HandleError(Dart_Invoke(type, Dart_NewStringFromCString("_getFD"), 1, args));

    Dart_SetReturnValue(arguments, result);
}

void Syscall_GetKernelInfo(Dart_NativeArguments arguments) {
    Dart_Handle list = HandleError(Dart_NewList(2));

    KernelInfo info = GetKernelInfo();

    HandleError(Dart_ListSetAt(list, 0, Dart_NewStringFromCString(info.name)));
    HandleError(Dart_ListSetAt(list, 1, Dart_NewStringFromCString(info.version)));

    Dart_SetReturnValue(arguments, list);
}

void Syscall_GetParentPid(Dart_NativeArguments arguments) {
    Dart_Handle handle_ppid = HandleError(Dart_NewInteger(GetParentPid()));
    Dart_SetReturnValue(arguments, handle_ppid);
}

void Syscall_CloseFileDescriptor(Dart_NativeArguments arguments) {
    Dart_Handle handle_fd = Dart_GetNativeArgument(arguments, 0);
    int64_t *fd = NULL;
    HandleError(Dart_IntegerToInt64(handle_fd, fd));
    CloseFileDescriptor((int) fd);
}

struct FunctionLookup {
    const char* name;
    Dart_NativeFunction function;
};

struct FunctionLookup function_list[] = {
        {"Syscall_Sync", Syscall_Sync},
        {"Syscall_GetFileDescriptor", Syscall_GetFileDescriptor},
        {"Syscall_GetKernelInfo", Syscall_GetKernelInfo},
        {"Syscall_GetParentPid", Syscall_GetParentPid},
        {"Syscall_CloseFileDescriptor", Syscall_CloseFileDescriptor}
};

Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool* auto_setup_scope) {
    const char* cname;
    Dart_NativeFunction result;
    int i;

    if (!Dart_IsString(name)) {
        return NULL;
    }

    result = NULL;
    HandleError(Dart_StringToCString(name, &cname));
    for (i = 0; function_list[i].name != NULL; ++i) {
        if (strcmp(function_list[i].name, cname) == 0) {
            result = function_list[i].function;
            break;
        }
    }

    return result;
}
