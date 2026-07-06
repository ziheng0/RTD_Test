# MTK Dump 使用说明

## 一、设置 dump 后自动抓取 modem dump log

1. modem dump 后可以将 modem dump log 保存在 Flash 中：

```bash
adb shell uci set system.@system[0].md_start='1'
adb shell uci set system.@system[0].md_save_mode='3'
adb shell uci set system.@system[0].md_dumpback_mode='0'
adb shell uci commit
adb shell reload_config
adb shell sync
adb shell /etc/init.d/mdlogger reload
```

---

## 二、触发 dump 命令

```bash
AT+ESWLA=0   # 重启恢复

echo off > /sys/power/autosleep
echo ccif_assert > /sys/kernel/ccci/mdsys1/control
```

---

## 三、dump 后判断 dump 类型

```bash
cat sys/kernel/ccci/boot
```

- 当输出为：
  ```
  md1:5
  ```
  表示出现了 dump

---

## 四、dump 文件说明

- 设备发生 dump 后，底层通常会生成文件：
  ```
  db.00.EE
  ```
- 文件目录：
  ```
  /data/log/aee_exp
  ```

### dump 文件数量规则

- 通常最多保存 **8 个 dump 文件**
- 第 **9 个 dump** 会覆盖第 **1 个文件**
- 可通过查看以下文件确认 dump 时间：
  ```
  db_history
  ```

---

## 五、问题分析建议

- 客户可以将 `aee_exp` 文件夹导出（pull）提供分析
- 通过解析可以判断：
  - 是 **AP 侧 dump**
  - 还是 **modem dump**

- 根据结果决定是否开启：
  ```
  MDlog 开关
  ```
