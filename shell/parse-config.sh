#!/usr/bin/env bash

set -o nounset

CONFIGFILE=".jenkins"
target_version=

FAILED=1
OK=0

config_verify() {
  if [[ ! -f $CONFIGFILE ]]; then
    echo "Sorry, file $CONFIGFILE not found!"
    return $FAILED;
  fi

  # read file and parse key:val
  eval $(sed '/:/!d;/^ *#/d;s/:/ /;' < "$CONFIGFILE" | while read -r key val
         do
             str="$key='$val'"
             echo "$str"
         done)

  # lower case convertion
  if ${build,,} = true; then
    # handle version number like: 2.8 2.8.1 2.8.1.1, but 2.8.1.2.3 is invalid
    if [[ $version =~ ^[0-9]+(\.[0-9]+){1,3}$ ]]; then
      echo "============ Building starts ================"
      target_version=$(echo $version | egrep -o '^[0-9]+.[0-9]+')
      return $OK
    else
      echo "Invalid version number: $version"
      return $FAILED;
    fi
  elif ${build,,} = false; then
    echo "Do nothing, just exits..."
    return $OK;
  else
    echo "Parameter value is invalid!"
    return $FAILED;
  fi
}


