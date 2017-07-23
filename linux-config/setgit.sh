#!/bin/bash

git config --global user.name "Rjerk"
git config --global user.email "460139918@qq.com"

ssh-keygen -t rsa -b 4096 -C "460139918@qq.com"

eval "$(ssh-agent -s)"

ssh-add ~/.ssh/id_rsa

# copy the ssh key to clipboard.

sudo apt-get install xclip
xclip -sel clip < ~/.ssh/id_rsa.pub

# add ssh key to github account.
