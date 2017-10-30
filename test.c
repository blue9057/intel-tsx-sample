#include <stdio.h>
#include <stdlib.h>

#include "tsx-cpuid.h"
#include "rtm.h"

int *ptr;

void tsx_fault() {
  int value = 0;
  ptr = NULL;
  if(_xbegin() == _XBEGIN_STARTED) {
    value++;
    // causes abort
    *ptr = value;
    _xend();
  }
  else {
    printf("Aborted!\n");
  }
  printf("Value is %d\n", value);
}

void tsx_normal() {
  int value = 0;
  if(_xbegin() == _XBEGIN_STARTED) {
    value++;
    _xend();
  }
  else {
    printf("Aborted, should never reach here\n");
  }
  printf("Value is %d\n", value);
}

int main() {
  if(!cpu_has_rtm()) {
    printf("This CPU does not support RTM (Intel TSX)\n");
    exit(-1);
  }
  else {
    printf("This CPU supports RTM (Intel TSX)\n");
  }
  printf("### Launching ABORT test ###\n");
  tsx_fault();
  printf("### ABORT test END ###\n");
  printf("### Launching NORMAL test ###\n");
  tsx_normal();
  printf("### NORMAL test END ###\n");
}
