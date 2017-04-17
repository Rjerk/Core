#!/bin/bash

FILES="/usr/sbin/accept
/usr/sbin/pwck
/usr/sbin/chroot
/usr/bin/fakefile
/sbin/badblocks
/sbin/ypbind"

echo

for file in $FILES
do
    if [ ! -e "$file"] # check if file exists.
    then
        echo "$file does not exist."; echo
        continue # on to next.
    fi

    ls -l $file | awk ' { print $8 "   file size: " $5 }' # print 2 fields
    whatis `basename $file` # file info.
    # the whatis database needs to have been set up for this to work
    # to do this, as root run /usr/bin/makewhatis.
    echo
done

exit 0
