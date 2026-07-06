一.测试之前，debug串口进控制台执行以下三条shell命令：
    echo 1 > /sys/module/printk/parameters/perf_mode_console;
    echo 1 > /sys/module/msm_show_resume_irq/parameters/debug_mask;
    echo 0x2 > /sys/module/ipc_router_core/parameters/debug_mask

二.内核信息打印到串口控制台
    cat /proc/kmsg &

三.执行休眠指令
    标准版本执行： at+qsclk=1
	  open版本执行：echo mem > /sys/power/autosleep

四.确认拔掉USB
    如果是USB是插入状态上位机，要保证USB在休眠状态，尽量拔掉。

五.观察是否进入休眠状态
       1. <1.1>如果设备已进入休眠，则敲串口无法响应，串口无持续打印。 <1.2>如果串口无法输入输出，则证明ap侧正常进入休眠。
       2. 不满足1.1，则设备未进入休眠，执行awk '$6 != 0 {print $1" "$6}' /sys/kernel/debug/wakeup_sources查看是否有唤醒源。
       如果不定时被唤醒，等待5分钟后。把串口输出log保存(secureCRT等工具可以设置log保存到本地文件),发给软件分析。