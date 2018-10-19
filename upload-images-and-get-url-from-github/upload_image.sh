#!/bin/bash

pushd /Users/rjerk/github/learning-notes/img

new_images=$(git ls-files --others --exclude-standard)

IFS=$'\n'
# Save current IFS
SAVEIFS=$IFS
# Change IFS to new line. 
IFS=$'\n'
new_images=($new_images)
# Restore IFS
IFS=$SAVEIFS

for (( i=0; i<${#new_images[@]}; i++ ))
do
    if [[ "${new_images[$i]}" != *"DS_Store"*  ]]; then
        git add ${new_images[$i]}
        echo "https://github.com/Rjerk/learning-notes/raw/master/img/${new_images[$i]}"
    fi
done


git commit -q -m "add new images: $new_images"

git push -q -u origin master

popd
