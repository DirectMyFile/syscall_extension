import "dart:io";

import "../build/syscall.dart";

class Expect {
  static void equals(a, b) {
    if (a != b) {
      throw "${a} != ${b}";
    }
  }

  static void notNull(a) {
    if (a == null) {
      throw "Expected value to not be null";
    }
  }
}

void main() {
  testKernelInfo();
  testGetParentPid();
  testCloseFileDescriptor();
}

void testKernelInfo() {
  var info = getKernelInfo();
  Expect.notNull(info.name);
  Expect.notNull(info.version);
}

void testGetParentPid() {
  var ppid = getParentPid();
  Expect.notNull(ppid);
}

void testCloseFileDescriptor() {
  var file = new File("src/os.h");
  var raf = file.openSync();
  var fd = getFileDescriptor(raf);
  closeFileDescriptor(fd);
}
