# Constants for opcodes
LOAD = 0x01
STORE = 0x02
ADD = 0x03
SUB = 0x04
HALT = 0xff

# Stretch goals
ADDI = 0x05
SUBI = 0x06
JUMP = 0x07
BEQZ = 0x08


def compute(memory):
    """
    Given a 256 byte array of "memory", run the stored program
    to completion, modifying the data in place to reflect the result

    The memory format is:

    00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f ... ff
    **        **... __
    ^==DATA===============^ ^==INSTRUCTIONS==============^
    """
    registers = [8, 0, 0]  # PC, R1 and R2

    while True:  # keep looping, like a physical computer's clock
        # op = TODO fetch the opcode
        
        # if op == TODO decode the opcode and execuet
        break

