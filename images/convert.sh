#!/bin/sh

for x in $(find . | grep \.tga)
do
echo .
echo "Converting $x to ${x//\.tga/\.png}"
rm -f ${x//\.tga/\.png}
convert -transparent black -transparent-color transparent -depth 32 $x ${x//\.tga/\.png}
done