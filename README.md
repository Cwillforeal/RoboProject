TODO:
-Read accel data in determine motor direction
-Init second motor for pwm1 and clean up init
-Write motor function for setting speed based on percent -100% to 100%
-Setup GPIO for motor direction
-Setup init dts file for peripherals

Debug Basics:
-Run debug.py is the DEBUG folder
-In another window run gdb-multiarch ROBO
    -Run "target remote 192.168.7.2:1234"
-You should be off and debugging
