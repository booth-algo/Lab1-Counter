**How does top.sv work?**
>> Interconnect wire: Declaration of an internal wire `count` of width `WIDTH`. This wire is not directly accessible from outside the `top` module but is used internally to connect the submodules.
>> The `counter` module is created with the name `myCounter`. It uses interface signals of the `top` module to communicate with its environment.
>> When the `top` module receives a clock, reset, enable signal, and preload value, it passes these to the `myCounter` instance. The `myCounter` instance then produces a `count` value based on its internal logic. This `count` value is then fed into the `myDecoder` instance, which converts this binary value into BCD format. The resulting BCD value is then outputted from the `top` module through the `bcd` port.

**Change to vbHex**
>> 3 BCD digits include 12 bits [11:0], since [11,10,9,8],[7,6,5,4],[3,2,1,0] after binary conversion to BCD-encoded binary
>> e.g. `vbdHex(4, (int(top->bcd) >> 8) & 0xF);`
>> The example here extracts the 4 bits starting from the 9th bit of `bcd`, i.e. [11:8]
>> How it works: (1) Takes value from `bcd` signal from top module, shifts right by 8 bits, isolates these 8 bits using bitwise AND operation, results in an integer respresenting these 8 bits.

**Change to doit.sh**
>> `verilator -Wall --cc --trace -top top top.sv counter.sv bin2bcd.sv --exe top_tb.cpp`
>> Use of `-top` to state that it is the top module

**Double dabble algorithm / shift-and-add-3 algorithm**
>> Ref.: 
>>>"https://www.realdigital.org/doc/6dae6583570fd816d1d675b93578203d#:~:text=The%20%E2%80%9Cdouble%20dabble%E2%80%9D%20algorithm%20is,of%20the%20accumulating%20BCD%20number."
>>>"https://www.youtube.com/watch?v=IBgiB7KXfEY"
>> Check if greater than 4 everytime when shifting, do it for ones, repeat it for tens, etc.
>> Shift until >4, then add 3 to it, then continue shifting.
>> By adding 3 before the shift, the algorithm ensures that the BCD digit carries over to the next BCD digit correctly, and the BCD representation remains valid.
>> e.g. How to show 10 in BCD?
>>> (1) If we left shift 5 in binary directly, it results in out of range number, since `0101` shifts to `1010`, which is not a valid BCD value
>>> (2) So we start with 5 in binary, and since it is >4, we add 3 to it: `0101 + 0011 = 1000`
>>> (3) Double (shift left) the value: `1000` becomes `10000`
>>> (4) Now it is `0001 0000`, which in BCD, is `10`

