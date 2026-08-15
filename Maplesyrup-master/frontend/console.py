#!/usr/bin/env python3
import sys
import os
import code
import ctypes
import ctypes.util

try:
    import readline
except ImportError:
    pass

def load_maplesyrup_lib():
    candidates = [
        "libmaplesyrup.so",
        "./libmaplesyrup.so",
        "../lib/src/.libs/libmaplesyrup.so",
        "/usr/local/lib/libmaplesyrup.so",
        "/usr/lib/libmaplesyrup.so",
    ]
    found = ctypes.util.find_library("maplesyrup")
    if found:
        candidates.insert(0, found)

    for path in candidates:
        try:
            return ctypes.CDLL(path)
        except OSError:
            continue
    return None

ms_lib = load_maplesyrup_lib()

env_vars = globals().copy()
env_vars.update(locals())
shell = code.InteractiveConsole(env_vars)
shell.interact(banner="")
