#!/usr/bin/env python3

import subprocess

# All of these functions are adapted from
# https://stackoverflow.com/a/52544846/7418735

def start(executable_file):
    return subprocess.Popen(
        executable_file,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE)


def read(process):
    # NOTE: expects a single line response
    return process.stdout.readline().decode("utf-8").strip()


def write(process, message):
    process.stdin.write(f"{message.strip()}\n".encode("utf-8"))
    process.stdin.flush()


def terminate(process):
    write(process, 'exit')
    process.stdin.close()
    process.terminate()
    process.wait(timeout=0.2)

if __name__ == '__main__':
    # compiled from ../src/main.cpp
    proc = start("../src/a.out")
    # write(proc, 'hello "world" hey')
    print(read(proc))

    terminate(proc)
