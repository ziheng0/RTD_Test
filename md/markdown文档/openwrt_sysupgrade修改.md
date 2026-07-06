# openwrt如何快速修改sysupgrade.bin

---

## DESCRIPTION

`sysupgrade.bin` 是 MTK 5G 平台 OpenWrt 系统编译后的产物，也是 FOTA 升级镜像包。

本质上它是一个 `.tar.gz` 压缩包，通过 `tar` 解压后可以得到实际烧录用的镜像文件。实际开发中，为了快速调试，可以手动修改 `sysupgrade.bin` 来制作需要的镜像。

---

## SOLUTION

### 1. 解压 sysupgrade.bin

```bash
mkdir tmp  # 创建临时目录（目录名必须与后续步骤一致）

# 解压到 tmp 目录
tar -xzf sysupgrade.bin -C tmp
```

解压后即可对其中的镜像文件进行替换或修改。

---

### 2. 重新打包 sysupgrade.bin

```bash
# 在 tmp 上级目录执行
# --transform 用于去掉 tmp 目录层级，只打包内部文件
tar -cvzf sysupgrade_new.bin tmp/* --transform 's:.*/::'
```

---

### 3. 示例（生成一个损坏的 sysupgrade.bin）

1. 使用 WinHex（或其他二进制编辑工具）打开目标镜像（如 `modem-verified.img`）
2. 任意修改几个字节并保存
3. 将修改后的文件替换回 `tmp` 目录
4. 按步骤 2 重新打包

即可得到一个“损坏”的 `sysupgrade.bin`，用于调试测试。

---

