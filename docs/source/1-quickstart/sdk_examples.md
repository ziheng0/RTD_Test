# SDK Examples
Here we recommend you use Docker environment to compile, so as not to limit the Ubuntu version of the host machine.

You can find more here.

## Example GPIO

1. Prepare to compile environment
   We suggest using Docker for compilation, and you can refer to this link for more information.

2. Compilation Example

   ```bash
   $  cd ql-ol-sdk/
   $  source ql-ol-crosstool/ql-ol-crosstool-env-init
   $  cd ql-ol-extsdk/example/gpio/
   $  make 
   $  adb push example_gpio /usrdata
   ```

3. Test

   ```bash
   $  cd /usrdata
   $  ./example_gpio
   ```

    Users can short-circuit the GPIO used for testing to the LED lights on the development board and observe the LED lights turning on and off.
    Please refer to the following video for more information

## Demo Video
<video src="../_static/example_gpio.mp4" autoplay="true" controls="controls" width="600" height="400">
</video>

## Example UART
    Need to add something.

## Example SPI
    Need to add something.

## Example I2C
    Need to add something.



