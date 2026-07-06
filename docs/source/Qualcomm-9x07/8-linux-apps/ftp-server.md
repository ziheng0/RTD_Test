# FTP server use guide on module

## Overview

There is a ftp server in quecopen module by default\. But we cannot use it directly\. Need some step as below\.

## Set the ftpd

Open file /etc/inet\.conf and add below line, /usrdata is directory where your file will be located in after transfer\.

21 stream tcp nowait root ftpd ftpd \-w /usrdata 

**Note: this step depends on inetd running\. In some version, inetd is not running\. So you have to run it firstly\.**

For quickly test, you can directly use command '**tcpsvd 0 21 ftpd \-w /usrdata \&**'\. In the newer busybox version, it ask username and password for such setting\. If customer won't ask username and password\.

We can use command 'tcpsvd 0\.0\.0\.0 21 ftpd **\-A **\-w /usrdata \&' to instead above command\.

![Image](https://internal-api-drive-stream.feishu.cn/space/api/box/stream/download/authcode/?code=Zjg4MTI3NWQyYTYyZjU4NWFmOWFkZTdjNzhmYzM4OWNfNDJhZWQyZjNiNGIxMGM1MTQxZGVlNDQ1MzE5ZWU1OWJfSUQ6NzYzNDA5OTgzNTEwNDc3NTM5MF8xNzgwNDg1MTMxOjE3ODA1NzE1MzFfVjM)

## Ftp server test

Use below command in client to transfer file\.** **Of course, you need a network link\. We can use ECM mode to quickly set up a link and test here\.

![Image](https://internal-api-drive-stream.feishu.cn/space/api/box/stream/download/authcode/?code=YjBiMWZjOTNhYTQwNmJiYzhhYjQwYmI1NWVkYzU5NmFfMWZlYmVkNzhmNGYzMGIzMmI1YWY3MGNjY2NhMjY5M2VfSUQ6NzYzNDA5OTkwNTUwMTk5MDA5N18xNzgwNDg1MTMxOjE3ODA1NzE1MzFfVjM)

After that, you can find the file in directory which is set at the step 1\.

![Image](https://internal-api-drive-stream.feishu.cn/space/api/box/stream/download/authcode/?code=YjFhODdjNWQ5NGZkMzI1NmM4N2YyZjI1N2ZhYjU1YzVfYzA1MmQ5OThhMDlmNDViYzU3MWFmMjhkNTIxZmFkODhfSUQ6NzYzNDA5OTk3MzY5MjgwNDA1MF8xNzgwNDg1MTMxOjE3ODA1NzE1MzFfVjM)



