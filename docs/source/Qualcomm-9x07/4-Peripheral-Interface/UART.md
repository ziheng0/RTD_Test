# UART Interface configuration



## Overview

The module based on the Qualcomm MDM9x07 chipset offers powerful peripheral interface expansion capabilities\. This chipset integrates multiple BLSP \(Berry Low\-Speed Peripheral\) controllers\. According to the hardware design specifications, each BLSP can be flexibly configured as a UART, I2C, or SPI interface\. To maximize the utilization of the module's serial port resources and meet the needs of multiple peripheral connections, this document will guide you on how to modify the kernel device tree \(DTS\) to configure all available BLSP interfaces as UART, and provides the corresponding patch and detailed principle analysis\.

### Compatibility Description

|Product Category|Cellular module|Product Line|LTE|Platform|MDM9X07|
|---|---|---|---|---|---|
|Series|EC2X/EG2X/EG9X|Model||SW solution||

### Tag

UART, Device Tree, Driver

## Pin Mapping

|UART 接口|BLSP|Pins|Function|
|---|---|---|---|
|UART1|BLSP1|pin129,pin130,pin131,pin132|It supports hardware flow control|
|UART2|BLSP2|pin63,pin66|2 lines（TX, RX），low speed UART|
|UART3|BLSP3|pin64,pin65,pin67,pin68|Main port\. It supports hardware flow control|
|UART4|BLSP4|pin133,pin134|2 lines（TX, RX），low speed UART|
|UART5|BLSP5|pin11,pin12|2 lines（TX, RX），debug uart port|
|UART6|BLSP6|pin38,pin39|2 lines（TX, RX），low speed UART|

Note: Please cross\-check the table above with your actual hardware schematic and attached images to ensure that the pins do not physically conflict with other peripherals such as I2C, SPI, or SDIO\.。



## Device tree modification

### SOC configuration \(`mdm9607.dtsi`\)

Objective: To declare UART nodes at the system level, allocating register base addresses, interrupt numbers, clocks, and bus configurations\.

\- Add UART1 \(HS\-UART\): Since UART1 needs to support higher baud rates and hardware flow control, the qcom,msm\-hsuart\-v14 driver is used, and a BAM DMA controller \(dma\_blsp1\) is mounted\.

\- Add UART2 \& UART4 \(LS\-UART\): Using the standard qcom,msm\-lsuart\-v14 driver, suitable for general low\-speed serial communication\.

### Pinmux \(`mdm9607-pinctrl.dtsi`\)

Objective: Define the multiplexing functions and electrical attributes of GPIO pins in Active and Sleep states\.

\- Added two pinctrl nodes, \_active and \_sleep, to blsp1\_uart1, blsp1\_uart2, and blsp1\_uart4 respectively\.

\- Parameter Explanation:

\- function = "blsp\_uartX": Multiplexes the pin as the corresponding UART function\.

\- function = "gpio": Restores the pin to GPIO mode during sleep to reduce power consumption\.

\- drive\-strength = \<2\>: Sets the drive strength to 2mA \(can be adjusted to 4, 6, 8, etc\., depending on the actual wire length and interference\)\.

### Enable the interface \(`mdm9607-mtp.dtsi`\)

Objective: In the specific board\-level configuration file, set the node status defined above to "ok" and disable conflicting peripherals\.

\- Enable serial port: Add \&blsp1\_uart1, \&blsp1\_uart2, \&blsp1\_uart4 and set status = "ok";

\- Disable conflicting nodes: Set the status of spi\_1 and sdhc\_2 \(SD card/SDIO\) to "disable"\. This step is very important because these peripherals may use the same GPIO pins as UART1/UART2/UART4\.

## How to use this Patch file

Follow below steps to apply the patch `5serials.patch` in kernel directory\.

```Shell
cd ql-ol-kernel/

git status

patch -p1 < ../5serials.patch

#Verificaiton
git diff arch/arm/boot/dts/qcom/mdm9607-mtp.dtsi
git diff arch/arm/boot/dts/qcom/mdm9607-pinctrl.dtsi
git diff arch/arm/boot/dts/qcom/mdm9607.dtsi
```

- HS\-UART \(High\-Speed UART\): UART1 in this configuration is an example\. It relies on BAM \(Bus Access Manager\) DMA to transfer data, resulting in extremely low CPU utilization\. It is suitable for high baud rates \(such as 921600bps, 1\.5Mbps, etc\.\) or large data transfers\.。Device name looks like `/dev/ttyHSx`\.

- LS\-UART \(Low\-Speed UART\): 如 UART2、UART3、UART4。This method uses a traditional interrupt\-driven approach, suitable for simple peripheral communication at low baud rates \(such as 115200bps\)\. The device node is typically /dev/ttyHSLx\.

## Use guide in application layer

After compiling and flashing the new kernel, the system will generate the corresponding device nodes\. You can use standard Linux serial port tools for reading and writing, or you can use the Quectel routines for testing\. The path of example code is ql\-ol\-sdk/ql\-ol\-extsdk/example/uart\.

```
diff --git a/ql-ol-kernel/arch/arm/boot/dts/qcom/mdm9607-mtp.dtsi b/ql-ol-kernel/arch/arm/boot/dts/qcom/mdm9607-mtp.dtsi
index 2fd469383..96b01a2ca 100755
--- a/ql-ol-kernel/arch/arm/boot/dts/qcom/mdm9607-mtp.dtsi
+++ b/ql-ol-kernel/arch/arm/boot/dts/qcom/mdm9607-mtp.dtsi
@@ -43,13 +43,27 @@
 //2016-01-19, comment out by jun.wu, remove UART3 && spi_1 from device tree
 /*
 &spi_1 {
-        status = "ok";
+        status = "disable";
 };
 */
 &blsp1_uart3 {
         status = "ok";
 };
 
+/* add by rodney.wang*/
+&blsp1_uart1 {
+        status = "ok";
+};
+
+&blsp1_uart2 {
+        status = "ok";
+};
+
+&blsp1_uart4 {
+        status = "ok";
+};
+/* add end */
+
 /*end jun.wu*/
 
 &spi_6 {
@@ -129,7 +143,7 @@
         qcom,nonhotplug;
         /*qcom,nonremovable;*/ /*carl.yin /sys/devices/7824900.sdhcii/polling*/
         qcom,core_3_0v_support;
-        status = "ok";
+        status = "disable";
 };
 
 &pm8019_gpios {
diff --git a/ql-ol-kernel/arch/arm/boot/dts/qcom/mdm9607-pinctrl.dtsi b/ql-ol-kernel/arch/arm/boot/dts/qcom/mdm9607-pinctrl.dtsi
index 88a56fc97..e64898470 100755
--- a/ql-ol-kernel/arch/arm/boot/dts/qcom/mdm9607-pinctrl.dtsi
+++ b/ql-ol-kernel/arch/arm/boot/dts/qcom/mdm9607-pinctrl.dtsi
@@ -20,7 +20,7 @@
                 #gpio-cells = <2>;
                 interrupt-controller;
                 #interrupt-cells = <2>;
-                qcom,tlmm-emmc-boot-select = <0x1>;
+                #qcom,tlmm-emmc-boot-select = <0x1>; 
 
                 uart_console_sleep: uart_console_sleep {
                         mux {
@@ -172,6 +172,87 @@
                                 bias-disable;
                         };
                 };
+                /* add comment by Rodney.wang */
+                blsp1_uart1_active: blsp1_uart1_active {
+                        mux {
+                                pins = "gpio12", "gpio13", "gpio14", "gpio15";
+                                function = "blsp_uart1";
+                        };
+
+                        config {
+                                pins = "gpio12", "gpio13", "gpio14", "gpio15";
+                                drive-strength = <2>;
+                                bias-disable;
+                        };
+                };
+
+                blsp1_uart1_sleep: blsp1_uart1_sleep {
+                        mux {
+                                pins = "gpio12", "gpio13", "gpio14", "gpio15";
+                                function = "gpio";
+                        };
+
+
+                        config {
+                                pins = "gpio12", "gpio13", "gpio14", "gpio15";
+                                drive-strength = <2>;
+                                bias-disable;
+                        };
+                };
+
+                blsp1_uart4_active: blsp1_uart4_active {
+                        mux {
+                                pins = "gpio16", "gpio17";
+                                function = "blsp_uart4";
+                        };
+
+                        config {
+                                pins = "gpio16", "gpio17";
+                                drive-strength = <2>;
+                                bias-disable;
+                        };
+                };
+
+                blsp1_uart4_sleep: blsp1_uart4_sleep {
+                        mux {
+                                pins = "gpio16", "gpio17";
+                                function = "gpio";
+                        };
+
+
+                        config {
+                                pins = "gpio16", "gpio17";
+                                drive-strength = <2>;
+                                bias-disable;
+                        };
+                };
+                blsp1_uart2_active: blsp1_uart2_active {
+                        mux {
+                                pins = "gpio4", "gpio5";
+                                function = "blsp_uart2";
+                        };
+
+                        config {
+                                pins = "gpio4", "gpio5";
+                                drive-strength = <2>;
+                                bias-disable;
+                        };
+                };
+
+                blsp1_uart2_sleep: blsp1_uart2_sleep {
+                        mux {
+                                pins = "gpio4", "gpio5";
+                                function = "gpio";
+                        };
+
+
+                        config {
+                                pins = "gpio4", "gpio5";
+                                drive-strength = <2>;
+                                bias-disable;
+                        };
+                };
+                /*add end */
 
                 spi1 {
 
diff --git a/ql-ol-kernel/arch/arm/boot/dts/qcom/mdm9607.dtsi b/ql-ol-kernel/arch/arm/boot/dts/qcom/mdm9607.dtsi
index e53def3cb..a15054ec2 100755
--- a/ql-ol-kernel/arch/arm/boot/dts/qcom/mdm9607.dtsi
+++ b/ql-ol-kernel/arch/arm/boot/dts/qcom/mdm9607.dtsi
@@ -356,25 +356,7 @@
         };
 
         /*2018-03-15, Modify by Quinn.Zhao, to support hardware flow control*/ 
-        blsp1_uart6: serial@78b4000 {
-                compatible = "qcom,msm-lsuart-v14";
-                reg = <0x78b4000 0x200>;
-                interrupts = <0 122 0>;                        
-                qcom,master-id = <86>;
-                clock-names = "core_clk", "iface_clk";
-                clocks = <&clock_gcc clk_gcc_blsp1_uart6_apps_clk>,
-                                <&clock_gcc clk_gcc_blsp1_ahb_clk>;
-                pinctrl-names = "sleep", "default";
-                pinctrl-0 = <&blsp1_uart6_tx_sleep &blsp1_uart6_rx_sleep &blsp1_uart6_rts_sleep &blsp1_uart6_cts_sleep>;
-                pinctrl-1 = <&blsp1_uart6_tx_active &blsp1_uart6_rx_active &blsp1_uart6_rts_active &blsp1_uart6_cts_active>;
-                qcom,msm-bus,name = "blsp1_uart6";
-                qcom,msm-bus,num-cases = <2>;
-                qcom,msm-bus,num-paths = <1>;
-                qcom,msm-bus,vectors-KBps =
-                                <86 512 0 0>,
-                                <86 512 500 800>;
-                status = "disabled";
-        };
+
 
         dma_blsp1: qcom,sps-dma@7884000 { /* BLSP1 */
                 #dma-cells = <4>;
@@ -618,6 +600,86 @@
         
         /*end jun.wu*/
 
+        /* add by Rodney.wang*/
+        
+        blsp1_uart1: uart@78AF000 {
+                compatible = "qcom,msm-hsuart-v14";
+                reg = <0x78AF000 0x200>,
+                        <0x7884000 0x2b000>;
+                reg-names = "core_mem", "bam_mem";
+                interrupt-names = "core_irq", "bam_irq";
+                #address-cells = <0>;
+                interrupt-parent = <&blsp1_uart1>;
+                interrupts = <0 1>;
+                #interrupt-cells = <1>;
+                interrupt-map-mask = <0xffffffff>;
+                interrupt-map = <0 &intc 0 107 0
+                                1 &intc 0 238 0
+                                2 &tlmm_pinmux 1 0>;
+
+                qcom,inject-rx-on-wakeup;
+                qcom,rx-char-to-inject = <0xFD>;
+
+                qcom,bam-tx-ep-pipe-index = <0>;
+                qcom,bam-rx-ep-pipe-index = <1>;
+                qcom,master-id = <86>;
+                clock-names = "core_clk", "iface_clk";
+                clocks = <&clock_gcc clk_gcc_blsp1_uart1_apps_clk>,
+                                <&clock_gcc clk_gcc_blsp1_ahb_clk>;
+                pinctrl-names = "sleep", "default";
+                pinctrl-0 = <&blsp1_uart1_sleep>;
+                pinctrl-1 = <&blsp1_uart1_active>;
+                qcom,msm-bus,name = "blsp1_uart1";
+                qcom,msm-bus,num-cases = <2>;
+                qcom,msm-bus,num-paths = <1>;
+                qcom,msm-bus,vectors-KBps =
+                                <86 512 0 0>,
+                                <86 512 500 800>;
+                status = "disabled";
+        };
+
+        blsp1_uart2: serial@78b0000 {
+                compatible = "qcom,msm-lsuart-v14";
+                reg = <0x78b0000 0x200>;
+                interrupts = <0 108 0>;                        
+                qcom,master-id = <86>;
+                clock-names = "core_clk", "iface_clk";
+                clocks = <&clock_gcc clk_gcc_blsp1_uart2_apps_clk>,
+                                <&clock_gcc clk_gcc_blsp1_ahb_clk>;
+                pinctrl-names = "sleep", "default";
+                pinctrl-0 = <&blsp1_uart2_sleep>;
+                pinctrl-1 = <&blsp1_uart2_active>;
+                qcom,msm-bus,name = "blsp1_uart2";
+                qcom,msm-bus,num-cases = <2>;
+                qcom,msm-bus,num-paths = <1>;
+                qcom,msm-bus,vectors-KBps =
+                                <86 512 0 0>,
+                                <86 512 500 800>;
+                status = "disabled";
+        };
+
+        blsp1_uart4: serial@78b2000 {
+                compatible = "qcom,msm-lsuart-v14";
+                reg = <0x78b2000 0x200>;
+                interrupts = <0 120 0>;                        
+                qcom,master-id = <86>;
+                clock-names = "core_clk", "iface_clk";
+                clocks = <&clock_gcc clk_gcc_blsp1_uart4_apps_clk>,
+                                <&clock_gcc clk_gcc_blsp1_ahb_clk>;
+                pinctrl-names = "sleep", "default";
+                pinctrl-0 = <&blsp1_uart4_sleep>;
+                pinctrl-1 = <&blsp1_uart4_active>;
+                qcom,msm-bus,name = "blsp1_uart4";
+                qcom,msm-bus,num-cases = <2>;
+                qcom,msm-bus,num-paths = <1>;
+                qcom,msm-bus,vectors-KBps =
+                                <86 512 0 0>,
+                                <86 512 500 800>;
+                status = "disabled";
+        };
+        /* add end */
+
+
         qcom,cnss-sdio {
                 compatible = "qcom,cnss_sdio";
                 reg = <0x87a00000 0x200000>;
@@ -1178,7 +1240,7 @@
                 qcom,msm-cpudai-auxpcm-data = <0>, <0>;
                 qcom,msm-cpudai-auxpcm-pcm-clk-rate = <2048000>, <40960000>;
                 qcom,msm-auxpcm-interface = "secondary";
-                pinctrl-names = "default", "idle";
+/*                pinctrl-names = "default", "idle";
                         pinctrl-0 = <&sec_auxpcm_ws_active
                                         &sec_auxpcm_sck_active
                                         &sec_auxpcm_dout_active
@@ -1187,6 +1249,7 @@
                                         &sec_auxpcm_sck_sleep
                                         &sec_auxpcm_dout_sleep
                                         &sec_auxpcm_din_sleep>;
+*/
         };
         //end jun.wu
 

```

