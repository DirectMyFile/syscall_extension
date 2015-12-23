library syscall;

import "dart-ext:syscall_extension";

import "dart:io";

class KernelInfo {
  final String name;
  final String version;

  KernelInfo._(this.name, this.version);

  @override
  String toString() => "KernelInfo(name: ${name}, version: ${version})";
}

void sync() native "Syscall_Sync";
int getFileDescriptor(RandomAccessFile file) native "Syscall_GetFileDescriptor";
int getParentPid() native "Syscall_GetParentPid";
List _getKernelInfo() native "Syscall_GetKernelInfo";
void closeFileDescriptor(int fd) native "Syscall_CloseFileDescriptor";

KernelInfo getKernelInfo() {
  if (_kernelInfo == null) {
    var info = _getKernelInfo();
    _kernelInfo = new KernelInfo._(info[0], info[1]);
  }
  return _kernelInfo;
}

KernelInfo _kernelInfo;
