# SDK Examples
Here we recommend you use Docker environment to compile, so as not to limit the Ubuntu version of the host machine.

You can find more here.

## Example GPIO

1. Prepare to compile environment
   We suggest using Docker for compilation, and you can refer to this link for more information.

1. Compilation Example

   ```bash
   $  cd ql-ol-sdk/
   $  source ql-ol-crosstool/ql-ol-crosstool-env-init
   $  cd ql-ol-extsdk/example/gpio/
   $  make 
   $  adb push example_gpio /usrdata
   ```

1. Test

   ```bash
   $  cd /usrdata
   $  ./example_gpio
   ```

    Users can short-circuit the GPIO used for testing to the LED lights on the development board and observe the LED lights turning on and off.
    Please refer to the following video for more information

1. Demo Video
<video src="../_static/video/example_gpio.mp4" controls="controls" width="600" height="400">
</video>

## Example UART

1. Prepare to compile environment
   We suggest using Docker for compilation, and you can refer to this link for more information.

1. Compilation Example

   ```bash
   $  cd ql-ol-sdk/
   $  source ql-ol-crosstool/ql-ol-crosstool-env-init
   $  cd ql-ol-extsdk/example/uart/
   $  make 
   $  adb push example_uart /usrdata
   ```

1. Test

   ```bash
   $  cd /usrdata
   $  ./example_uart 115200
   ```

1. Demo Video
<video src="../_static/video/example_uart.mp4" controls="controls" width="600" height="400">
</video>

## Example SPI
1. Prepare to compile environment
   We suggest using Docker for compilation, and you can refer to this link for more information.

1. Compilation Example

   ```bash
   $  cd ql-ol-sdk/
   $  source ql-ol-crosstool/ql-ol-crosstool-env-init
   $  cd ql-ol-extsdk/example/spi/std_spi
   $  make 
   $  adb push example_spi /usrdata
   ```

1. Test

   ```bash
   $  insmod /usr/lib/modules/3.18.20/kernel/drivers/spi/spidev.ko busnum=6 chipselect=0 spimode=0 maxspeed=19200000 
   $  cd /usrdata
   $  ./example_spi
   ```

1. Demo Video
<video src="../_static/video/example_spi.mp4" controls="controls" width="600" height="400">
</video>

## Example I2C
1. Prepare to compile environment
   We suggest using Docker for compilation, and you can refer to this link for more information.

1. Compilation Example

   ```bash
   $  cd ql-ol-sdk/
   $  source ql-ol-crosstool/ql-ol-crosstool-env-init
   $  cd ql-ol-extsdk/example/i2c/
   $  make 
   $  adb push example_i2c /usrdata
   ```

1. Test

   ```bash
   $  cd /usrdata
   $  ./example_i2c
   ```

1. Demo Video
<video src="../_static/video/example_i2c.mp4" controls="controls" width="600" height="400">
</video>



