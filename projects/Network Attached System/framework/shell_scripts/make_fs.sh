#!/bin/bash

sudo mkfs.ext2 /dev/nbd$1
sudo mount /dev/nbd$1 ~/nbd_test/mount/
