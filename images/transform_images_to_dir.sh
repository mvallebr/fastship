#!/bin/sh

extension="png"
for dir in *
do
for file in $dir/*.$extension
do
len=$(expr length $file - 4)
subdir=$(expr substr $file 1 $len)
mkdir $subdir
mv $file $subdir/00001.$extension
done  #subdir
done  #dir
