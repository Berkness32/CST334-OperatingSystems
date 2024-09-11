#include "src/student_code.h"

#include "unistd.h"
#include <sys/syscall.h>
#include <stdio.h>

int main() {
  const char msg[] = "Hello World!\n";
  write(STDOUT_FILENO, msg, sizeof(msg)-1);
  syscall(SYS_write, STDOUT_FILENO, msg, sizeof(msg)-1);

  char buff[1024];
  syscall(SYS_read, STDIN_FILENO, buff, 5);
  printf("%s\n", buff);
  return 0;
}
