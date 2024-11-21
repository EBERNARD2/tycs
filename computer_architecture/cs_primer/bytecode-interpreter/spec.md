
# The virtual computer

The device we’re modeling is much simpler than a modern CPU; it has:

* **256 bytes of memory**, simulated by an array with length 256
* **Three 8-bit registers**: 2 general purpose registers and 1 for the “program counter”
* **5 basic instructions**: load word, store word, add, subtract and halt
* As a stretch goal, **4 more instructions**: add immediate, subtract immediate, jump, and branch if equal to zero


# Memory

For the "machine" in this exercise, main memory is 256 “bytes”. We will use a fixed size array to model this.

Here is one way to picture our memory:

```
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f ... ff
__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ ... __
```

All of the instructions and all of the data for a particular “program” must fit within these 256 bytes “bytes”.

Our computer follows a special convention for organizing memory:

- Data is stored in the first 8 bytes
- Instructions are stored immediately after the data
- Any program output is expected to be written to byte zero

This can be pictured as so, where XX indicates the output location:

```
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f ... ff
__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ ... __
XX ^==OTHER DATA======^ ^==INSTRUCTIONS==============^
```

# Instruction Format

Our architecture has a very limited instruction set, with only 5 basic instructions. Each can be mapped to a specific byte value, which is how we'll specify the instruction in byte code:

```
load    0x01
store   0x02
add     0x03
sub     0x04
halt    0xff
```

Other than halt, each of these instructions has "op args" that need to be supplied:

```
load    r1  addr    # Load value at given address into given register
store   r2  addr    # Store the value in register at the given memory address
add     r1  r2      # Set r1 = r1 + r2
sub     r1  r2      # Set r1 = r1 - r2
halt
```

For simplicity, each “parameter” is encoded in a byte. This means that all the instructions except `halt` will take three bytes—and `halt`, just one—to encode. The `reg` parameters may only take one of two values, because our architecture only has 2 general purpose registers. We can choose any single byte value to identify the registers, we’ve chosen the values `0x01` and `0x02` (reserving value `0x00` for the program counter).

Now we have enough information to write a program. The “assembly”:

```
load    r1 0x01     # Load data from byte 1 into register 1
load    r2 0x02     # Load data from byte 2 into register 2
add     r1 r2       # Add the two register values, store the result in r1
store   r1 0x00     # Store the sum into the output location
halt
```

When translated line by line to our byte code:

```
0x010101
0x010202
0x030102
0x020100
0xff
```

And, partially, into our visualization of memory:

```
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f ... ff
__ __ __ __ __ __ __ __ 01 01 01 01 02 02 03 01 ... __
XX ^==OTHER DATA======^ ^==INSTRUCTIONS==============^
```

By loading two values into locations 0x01 and 0x02, and running the VM with the entirety of memory as input, it should modify memory, writing the sum to location 0x00.

For instance, say the input to our program were the numbers 3 and 5:

```
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f ... ff
__ 03 05 __ __ __ __ __ 01 01 01 01 02 02 03 01 ... __
XX ^==OTHER DATA======^ ^==INSTRUCTIONS==============^
```

After running the VM, the state of memory should be:

```
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f ... ff
08 03 05 __ __ __ __ __ 01 01 01 01 02 02 03 01 ... __
XX ^==OTHER DATA======^ ^==INSTRUCTIONS==============^
```

# The exercise

Write an "interpret function that takes as input a reference to "memory" (an array of 256 bytes), executes the stored program by fetching and decoding each instruction until it reaches halt, then returns. This function shouldn't return anything, but should have the side-effect of mutating “main memory”.

Your VM should follow the fetch-decode-execute format, which you can model in a loop. The program counter should always contain the address of the “next instruction” (and so should start at 8). Fetch the current instruction by getting all of the relevant information from memory, decode the instruction to find out what operation should be performed using which registers/memory-addresses, then execute the instruction and update the program counter appropriately.

Your virtual computer should have one piece of internal state, an array of three registers: two general purpose registers and a program counter. Main memory is considered external state because it is passed in as an argument. The provided test suite will test your program against a number of such sequences of bytes.


# Stretch goals

If you have time, attempt to implement 4 additional instructions with the following opcodes:

```
addi    0x05
subi    0x06
jump    0x07
beqz    0x08
```

`addi` and `subi` are the "immediate" versions of `add` and `sub`. Instead of adding or subtracting the value stored at a memory location, they add/subtract the value stored as the second argument. E.g. `addi  r1  4` will result in r1 = r1 + 4.

`jump` has a single argument, which is the address that the program counter should be set to. It is absolute, i.e. "jump 40" will cause the program to continue from the 40th byte in memory. In practice, `jump` is used for such things as function calls.

`beqz` has two arguments: a register and a relative offset amount. If the value in that register is zero, then the program counter should be increased or decreased by that offset amount (in addition to any increase due to the `beqz` instruction itself having been processed). Most instruction set architectures support a variety of such "conditional branch" instructions, which are used for such things as conditional statements, switch statements and loops.

As a further stretch goal, you may also wish to implement some degree of memory protection, such as preventing instructions from being accidentally overwritten.



