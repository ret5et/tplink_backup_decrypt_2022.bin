#!/bin/bash

bincfg="$1"

c/decrypt $bincfg /tmp/out.tar
tar -xvf /tmp/out.tar -C ./out
cp ./out/ori-backup-user-config.bin ./out/ori-backup-user-config.tgz

cd out
pwd 

tar -xf ori-backup-user-config.tgz
ls -lh ./tmp
