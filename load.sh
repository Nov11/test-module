#!/bin/bash
rmmod cdev.ko
insmod cdev.ko
dmesg|tail
