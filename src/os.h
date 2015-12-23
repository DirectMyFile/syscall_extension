#ifndef SYSCALLEXTENSION_OS_H
#define SYSCALLEXTENSION_OS_H

class KernelInfo {
public:
    const char* name;
    const char* version;
};

KernelInfo GetKernelInfo();
void FileSystem_Sync();
int GetParentPid();
void CloseFileDescriptor(int fd);
int WriteToFileDescriptor(int fd, int bytes[]);

#endif //SYSCALLEXTENSION_OS_H
