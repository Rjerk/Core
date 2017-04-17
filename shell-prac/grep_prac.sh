#!/bin/bash

# --color display color
grep --color 'echo' 1.txt

# -n display matched content with line number
grep -n 'echo' 1.txt

# -c print line number
grep -c 'echo' 1.txt

# -v print unmatched line
grep -v 'echo' 1.txt


