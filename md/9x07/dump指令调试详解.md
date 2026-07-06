# Modem 重启级别配置与 Crash 测试指南

## 1. AT 指令参数说明

### 1.1 `AT+QCFG="ModemRstLevel"`
该参数用于配置 Modem 发生致命错误（如 assert）时的重启行为。
*   &zwnj;**默认值**&zwnj;：1
*   &zwnj;**保存特性**&zwnj;：参数设置&zwnj;**保存**&zwnj;。

| 参数值 | 模式名称 | 行为描述 |
| :---: | :--- | :--- |
| &zwnj;**0**&zwnj; | SYSTEM | Modem 发生 fatal error 时，关联 Linux 系统。根据 `ApRstLevel` 的值，模块将进入 Dump 模式或整机重启。 |
| &zwnj;**1**&zwnj; | RELATED | Modem 发生 fatal error 时，仅重启 Modem，Linux 系统不受影响。 |

> &zwnj;**注意**&zwnj;：在 9x40 平台上，由于 Linux 不支持 SSR（Subsystem Restart），该参数的实际意义有限。无论设置为多少，模块是重启还是进入 Dump 主要取决于 `ApRstLevel` 的值。

### 1.2 `AT+QCFG="ApRstLevel"`
该参数用于配置系统发生致命错误时的整体行为。
*   &zwnj;**默认值**&zwnj;：1
*   &zwnj;**保存特性**&zwnj;：参数设置&zwnj;**不保存**&zwnj;。

| 参数值 | 行为描述 |
| :---: | :--- |
| &zwnj;**0**&zwnj; | Modem 或 System 发生 fatal error 时，模块重启并进入 &zwnj;**Dump**&zwnj; 模式以抓取日志。 |
| &zwnj;**1**&zwnj; | Modem 或 System 发生 fatal error 时，模块&zwnj;**直接重启**&zwnj;，不进入 Dump 模式。 |

---

## 2. 手动触发 Dump 与重启方法

当需要抓取完整日志或模拟故障时，可通过以下方式进行操作。

### 2.1 配置系统重置模式（控制台操作）
若需配置为抓 Dump 且控制台可登录（适用于 Modem 不停重启的场景），执行以下命令：

```bash
echo 0 > /sys/devices/4080000.qcom,mss/subsys1/system_reset_mode
echo "SYSTEM" > /sys/devices/4080000.qcom,mss/subsys1/restart_level
echo c > /proc/sysrq-trigger
