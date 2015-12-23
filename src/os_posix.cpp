//
// Created by Kenneth Endfinger on 11/8/15.
//

#include "os.h"
#include "common.h"

#if defined(__APPLE__) || defined(__LINUX__) || defined(__UNIX__)
#include <sys/utsname.h>
#include <unistd.h>

KernelInfo GetKernelInfo() {
    struct utsname *name = new utsname;
    CheckResultAndThrow(uname(name));
    KernelInfo info;
    info.name = name->sysname;
    info.version = name->version;
    return info;
}

void FileSystem_Sync() {
    sync();
}

int GetParentPid() {
    return getppid();
}

void CloseFileDescriptor(int *fd) {
    CheckResultAndThrow(close(fd));
}

int WriteToFileDescriptor(int fd, int bytes[]) {
    return (int) write(fd, bytes, 0);
}
#endif
