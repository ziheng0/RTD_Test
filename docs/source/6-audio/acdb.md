# ACDB

ACDB (Audio Calibration Database)

ACDB is used to adjust ADSP audio parameters. As shown in the figure below, there are currently 7 ACDB 
files available for use. The workspaceFile.qwsp shown below is a project file for the QACT tool to open the
ACDB files. 

QACT, a kind of audio parameters adjustment tool provided by Qualcomm, is used to calibrate ACDB.
ACDB files are loaded into memory in the process of alsaucm_test. If the process is not enabled, online 
calibration mode cannot be used on QACT tool.

## Import ACDB

Copy the SDK to Linux and execute the following command to unzip the SDK.

```bash
$ tar xvf EC25EFAR06A12M4G_OCPU_20.200.20.200_SDK.tar.bz2
$ source ql-ol-crosstool/ql-ol-crosstool-env-init

# Copy all the ACDB file to ql-ol-rootfs/etc
$ make rootfs

# Then flash the mdm9607-perf-sysfs.ubi to update the rootfs partition. 
```

