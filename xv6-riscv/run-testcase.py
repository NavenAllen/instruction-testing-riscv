import os, subprocess, signal, time, sys
from pwn import *

if(len(sys.argv) !=2):
    print("Usage: ./run <mode>\n      0 - User Mode, 1 - Supervisor Mode, 2 - Machine Mode\n      .. e.g. ./run 0")
    exit(-1)


timeout = 2
cmdline = ["make", "qemu-gdb", sys.argv[1]]
child = subprocess.Popen(cmdline, preexec_fn=os.setsid)

time.sleep(0.5)

try:
    io = process('riscv64-unknown-elf-gdb')
    io.sendline(b'b *test_end')
    io.sendline(b'b *trap_vector')
    io.sendline(b'c')
    output = io.recvuntil(b"Breakpoint 1, ", timeout=5).decode()
    if output == '':
        io.recvuntil(b"Breakpoint 2, ", timeout=5).decode()
    
    io.sendline(b"info all-registers")
    print(io.clean().decode())

    if output == '':
        print("ERROR OCCURED WHILE EXECUTING TESTCASE!!")
finally:
    os.killpg(os.getpgid(child.pid), signal.SIGKILL)


