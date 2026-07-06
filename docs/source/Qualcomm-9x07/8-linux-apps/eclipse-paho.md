# Eclipse paho-the third MQTT library porting and use guide

## Overview

This article explains how to port an open\-source code library to a module\. If customers require a lower\-level API approach to implement MQTT functionality, they can refer to this article\.

### Compatibility Description

|Product Category|Cellular module|Product Line|LTE|Platform|MDM9X07|
|---|---|---|---|---|---|
|Series|EC2X/EG2X/EG9X|Model||SW solution||

### Tag

MQTT library, paho\.



## Porting

### Source code downloading

You can download the source code here: https://github\.com/eclipse/paho\.mqtt\.c\. Or google the latest eclipse paho project address\. The source code directory is as follows:

![Image](https://internal-api-drive-stream.feishu.cn/space/api/box/stream/download/authcode/?code=MmI4MGFmZDJmZWVmNjQxODRlYTU1N2NkOWQ1N2VkZjVfZWZiMWY4OGU3ZDBjMmUxYzFhMWE3M2Y0ODFhOWY1ZDNfSUQ6NzYzNDA5NjU0NTY4ODQ3MjUxNl8xNzgwNDg1MTE4OjE3ODA1NzE1MThfVjM)

### Compiling setting

Because it needs to run on the module, cross\-compilation of the library is required\. First, source the SDK environment variables, and then set the CC variable to arm\-oe\-linux\-gnueabi\-gcc in the Makefile\.

![Image](https://internal-api-drive-stream.feishu.cn/space/api/box/stream/download/authcode/?code=ZGVlYjE0NGM2ODAxMzY4NDE2NDFmNTJjMjdlM2I1OTZfYmUwOTE5YWY2Zjc2ZDRhOWU1Yzk4Yzk0OWI3YzA3OTJfSUQ6NzYzNDA5NjYwOTQ1Mzk2ODMzMV8xNzgwNDg1MTE4OjE3ODA1NzE1MThfVjM)

If you need to conveniently group library files and header files together for easy copying later, you need to set a prefix variable, which is the path where you want to store the library files and header files\.

![Image](https://internal-api-drive-stream.feishu.cn/space/api/box/stream/download/authcode/?code=M2MzNGM0YmNlYTk5ZTU0M2ExNWI5NWExMjkwZGUyNGVfMDY2ZWRlYjViMDdjMWUwNGRjZmUxMjFjYTUxNzNiYjVfSUQ6NzYzNDA5NjY2NjQ3NDk1Nzc4Ml8xNzgwNDg1MTE4OjE3ODA1NzE1MThfVjM)

### Compile and Install

Use the `make install` command to compile and install\. The compiled files will be stored in the previously specified `prefix` directory\. Ignore any installation errors in the man pages\. The compiled header and library files are as follows\.

![Image](https://internal-api-drive-stream.feishu.cn/space/api/box/stream/download/authcode/?code=NDhmYzI4MGVlYjViMzRkMTAyNGRmMWQ3YzIyNDgyNWJfOTVlNjczMzgwMjFhMjZiNTkwOGM5YzZmY2QwYTczMjhfSUQ6NzYzNDA5NzAwODYxNDMxMzE4NF8xNzgwNDg1MTE4OjE3ODA1NzE1MThfVjM)

Note: In some version, the makefile has some bug which causes installing is failure\. You should change it as below\.

![Image](https://internal-api-drive-stream.feishu.cn/space/api/box/stream/download/authcode/?code=M2EyNzc5NjkxZmFlMDRkM2JlNjMzOGQyMmYyNmU2NjZfNjdmZjljOGNkNTU4NzlkNzgyMjZjNTJjZDMzNzc4NjZfSUQ6NzYzNDA5NzI4Njk2NDc1OTQ5Ml8xNzgwNDg1MTE4OjE3ODA1NzE1MThfVjM)

## Example 

Copy the compiled libraries and header files to the `lib` and `include` folders under the `ql-ol-extsdk/` directory, and the `lib` and `include` folders under the `ql-ol-rootfs/usr/` directory, respectively\. The former is required during compilation, and the latter is required for MQTT application runtime\. Later, you can also directly copy them to the `/usr/lib` and `/usr/include` directories of the module\.

Create an `mqtt` folder under `example`\. Refer to the code `mqtt.cpp` to create an MQTT application\. Here, a Mosquitto test server is used, with a non\-SSL connection\.

![Image](https://internal-api-drive-stream.feishu.cn/space/api/box/stream/download/authcode/?code=YmI4YWIzZGY1M2ZiY2NlYTY3YTlhYzhiYzI3NGFhMGVfMGY0Yzc3OTExOWRlODVmYmVlMTliNWZjNjU2YWU1MjNfSUQ6NzYzNDA5NzgyMzExODA4NTA2OF8xNzgwNDg1MTE4OjE3ODA1NzE1MThfVjM)

The above example publishes a message once and then continuously subscribes to messages with the title "quectel"\.

We will test this on Ubuntu by using mosquitto to first subscribe to a message and then continuously publish messages\. Since this is a live network test, the module needs to be connected to the internet first\.

The image below shows that mosquitto successfully subscribed to the MQTT\_test message, and then sent three messages with the title "quectel", all of which the module received\.

![Image](https://internal-api-drive-stream.feishu.cn/space/api/box/stream/download/authcode/?code=ODYzZDNmNGI2ZjA3N2ZkZjBmNWU2MDNiMzk2OTE1ZGFfY2ExNzdlMjAzOWEwNjFkZDllNDkyYzFlYmY2YTNkYjFfSUQ6NzYzNDA5Nzk2OTQ5MTU5NDE3OF8xNzgwNDg1MTE4OjE3ODA1NzE1MThfVjM)

![Image](https://internal-api-drive-stream.feishu.cn/space/api/box/stream/download/authcode/?code=MGNhNjhiMzNhZmU3ODFmNThhMjJjMDJmMGM3YWI3YjBfZTQ2ZTZhYzVjMGUwZTAzMDY0ZjA2Zjg5MGRiYjNjNzVfSUQ6NzYzNDA5ODAxMDA5MTg1MDk4MF8xNzgwNDg1MTE4OjE3ODA1NzE1MThfVjM)



