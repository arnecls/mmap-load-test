#!/bin/bash

mkdir -p data

sudo dd if=/dev/zero of=data/1.raw bs=64m count=64
sudo dd if=/dev/random of=data/2.raw bs=64m count=64
sudo dd if=/dev/urandom of=data/3.raw bs=64m count=128
