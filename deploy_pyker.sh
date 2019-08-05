#!/bin/bash

make satan -j 32 && dfu-programmer atmega32u4 erase && dfu-programmer atmega32u4 flash satan_pyker.hex && dfu-programmer atmega32u4 reset
