# Task 2: Linking Verilator Simulation with VBuddy

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/8e309070-d3e5-4168-8593-7dd2af204801)

**Functions learned:**\
*vbdFlag()*: VBuddy has a rotary encode (at the bottom left of the display screen). This comes with two features:
* you can rotate the encoder to change value
* you can press the encoder button to change flag state

The vbdFlag() function returns the current state of the flag (1 or 0). Pressing the button changes the flag state (aka toggle switch state) between 0 and 1.

*vbdHex()*: presents numbers in hex display.

# Test Yourself Challenge

I modified the `counter.sv` file so that if `en` is HIGH (taking the value from vbdFlag), then it will add 1 to the counter, else (`en` is low) and it subtracts from the `count`.

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/629a7f6c-2313-4172-bbeb-f8b1b145d3a5)

My initialisation in the testbench:

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/96784722-b1d2-4611-88fc-00e5c6e1166b)

Using Hex: (you can also see that I commented out vbdPlot, which I tested)

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/cf266e92-47e8-4ffe-b4da-b861d2aed1c7)

which is shown in the following video:

https://github.com/booth-algo/Lab1-Counter/assets/107279223/dd01d631-adb1-4e6f-8c68-099dd4808a0d

I also tested the vbdPlot function:

https://github.com/booth-algo/Lab1-Counter/assets/107279223/c0567f4e-8cf1-4ff2-9618-3e81834d20a6
