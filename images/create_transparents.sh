#!/bin/sh

for dir in *
do

for file in $dir/*.bmp
do
len=$(expr length $file - 4)
file=$(expr substr $file 1 $len)
convert -verbose -type TrueColorMatte -transparent black $file.bmp $file.tga
#ini=$(expr length $dir + 2)
#onlyf=$(expr substr $file $ini $len)
done  #file

done  #dir
