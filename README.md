## prepare env
* install qemu-user
* install g++-arm-linux-gnueabi


## run
* qemu-arm exec-file

## debug
* qemu+gdb
```shell
qemu-arm -singlestep -g 1234  exec-file
arm-linux-gnueabi-gdb
    file  exec-file
    target  remote  localhost:1234
     press Ctrl+x and then A to active it
     layout regs

## ref doc
ARM体系结构与编程第二版
ARM嵌入式系统编程与优化