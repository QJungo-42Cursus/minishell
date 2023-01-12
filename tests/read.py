#!/usr/bin/env python
import sys

for arg in sys.argv:
    print(arg)
    print(repr(arg))



# args to test :
# "\"\""    '\"\"'  echo $'\"\"'  echo $'\"\"' | python read.py
