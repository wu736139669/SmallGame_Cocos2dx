#!/bin/sh

#  PackTextures.sh
#  OnceAgain
#
#  Created by 王少培 on 14-6-18.
#
TP="/Users/wangshaopei/Downloads/TexturePacker"

if [ "${ACTION}" = "clean" ]
then
echo "cleaning..."

rm resources/sprites-hd.pvr.ccz
rm resources/sprites-hd.plist

# ....
# add all files to be removed in clean phase
# ....
else
echo "building..."

# create hd assets
${TP} --smart-update
--format cocos2d
--data resources/sprites-hd.plist
--sheet resources/sprites-hd.pvr.ccz
--dither-fs-alpha
--opt RGBA4444
numberBox/*.jpg


# ....
# add other sheets to create here
# ....
fi
exit 0