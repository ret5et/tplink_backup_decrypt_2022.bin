#!/bin/bash

key="30313233343536373839616263646566"
iv="31323334353637383930616263646566"

input="$1"
output="$2"
tfile="$(mktemp /tmp/tplink.XXXXXXXXX)" || exit 1

if [ -z $input ] || [ -z $output ]; then
    echo "$0 <cfg.bin> <out.tgz>"
    exit 1
fi
dd if=$input of=$tfile bs=1 skip=128 
openssl aes-128-cbc -v -d -K $key -iv $iv -in $tfile -out $output

rm $tfile
