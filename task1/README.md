# Lab 1 - Learning System Verilog with Verilator and VBuddy

Having completed Lab0, I have the following installed:
- VSCode
- VSCode Extensions for SystemVerilog, C++, Verilog, Markdown
- Git and Github
- GTKwave
- GNU toolchain
- And most importantly, WSL2 (Ubuntu 22.04) with USBIPD

## Task 1

**Starting the project**
- Forked the Github repo to my own GitHub account
- Cloned the repo to my WSL Ubuntu distribution using `git clone`
- Opened the folder in VS Code using `code .` within WSL

**Creating counter.sv**

A counter module was created in `counter.sv`

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/3ce4c567-5c8d-4ec1-9427-ce00442d3f9a)

The System Verilog code synthesizes:

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/7e967846-0853-4666-9e7a-cdcf55fb824d)

which is a combination of multiplexer and D-type flip-flop

Note that 

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/3d80d850-1dd3-4f1a-9a21-d1f046cca496)

And specifically for line 14, the line starting with the `else` statement: `count <= count + {{WIDTH-1{1'b0}}, en};`, concatenation is used to form WIDTH-1 bits with the LSB being the bit of the enable signal, as explained the the comments in my code:

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/58a080e1-29a8-495a-99a7-01552082062a)

**Creating a testbench**

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/26fb9fc2-a021-4ff1-a7f9-023a10d1d180)

The part below traces through 99 levels of hierarchy:

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/32990a0a-a83d-4d66-bdf3-f4fa91d04338)

In the testbench, I set my initial inputs:

- top->clk = 1
- top->rst = 1
- top->en = 0

The waveform is shown below here:

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/b0998a5b-baca-4342-86fb-842d0934d8e5)

We see that, assuming clock is -1 before the first cycle, 
- rst is HIGH until the 2nd clock cycle
- rst is HIGH at the 15th clock cycle
- en is HIGH from the 5th clock cycle

Why?

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/ca4d48ad-ecec-4bf2-8828-a2e0fe352579)

We can see that the eval() function comes after the clk line. This means all the evaluations occur "during the clock cycle" but that does not show up until the positive edge of the next clock cycle in the waveform on GTK. So if rst is to be 0 when i == 2. This means at positive edge of clock cycle 2, rst is still 1. During this clock cycle the eval function occurs and rst changes. However this change is displayed at the positive edge of clock cycle 3.

## Test Yourself Challenge

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/2f4576e7-0812-4852-962a-5a49c8ba30a9)

To stop counting for 3 cycles once the counter reaches `0x09`, and then to resume counting, I modified the testbench so that `en` is LOW between cycles 14-16

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/d0d381ca-1d7b-401e-9576-12e0da76661d)

To implement an asynchronous reset, I changed the sensitivity list of the always_ff block to:

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/1e785368-4a6e-4d20-8fb5-de35839c771e)

To test this, the testbench stimulus for the rst block is changed to:
- rst is also HIGH during cycle 20

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/f4802292-9fbc-42b1-b373-4f53a5e1c72c)

This resulted in the following waveform:

![image](https://github.com/booth-algo/Lab1-Counter/assets/107279223/587e9bae-a336-49b7-9cc5-8bf8cca282b2)

The stimulus correctly caused the count to stop at 0x09 for three cycles.

The reset occurs at cycle 20, and the count sets to zero mid-cycle due to Verilator twice per cycle evaluation --> the asynchronous reset has worked.
