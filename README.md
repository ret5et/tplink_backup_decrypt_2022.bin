```
+-+-+-+-+ +-+-+-+-+                                                                                                                                         
|l|u|l|z| |C|r|e|w|                                                                                                                                         
+-+-+-+-+ +-+-+-+-+ 

tp-link Decrypt/Crypt Config files
```

# Compile

```
$ cd c/
./build.sh

```
# Usage

```
./decrypt <config.bin> <output.tar>
./encrypt <inpit.tar> <output.bin>

$ ./decryp_and_unpack.sh backup-ArcherC7v5-2022-04-29.bin
$ cat ./out/tmp/user-config.xml
$ ./repack.sh /tmp/out.bin
```

# Info

Tested on: Archer C7 tp-link.

# Crypt
```
AES 128 bit (cbc)
iv:  "1234567890abcdef"
key: "0123456789abcdef";
```
