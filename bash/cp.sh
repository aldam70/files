#!/bin/bash

ME=$(basename $0)
HERE=$(cd `dirname $0`; pwd)
FILE=$PWD/$1

echo $1
echo ${FILE/ph-development\/development/system\/phcontrol}
cp -i $1 ${FILE/ph-development\/development/system\/phcontrol}
