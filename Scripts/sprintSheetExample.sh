#! /bin/sh
TP=/usr/local/bin/TexturePacker
if [ "${ACTION}" = "clean" ]
then
# remove all files
rm ../Resources/Assets/sheet*.png
rm ../Resources/Assets/sheet*.plist
else
echo "TexturePacker building..."

#当前设置路径为Assets

#创建目录
#mkdir -p ../Resources/res/test

#1.调用TP生成sprintsheet
#2.到--data和--sheet时会自动创建目录
#3.最后小图从Assets取得,路径对应Assets里面的
${TP} --smart-update \
--format cocos2d \
--data ../Resources/res/funfilename/funfilename.plist \
--sheet ../Resources/res/funfilename/funfilename.png \
funfilename/*.png

${TP} --smart-update \
--format cocos2d \
--data ../Resources/res/funfilename/funfilename_funfilesubname.plist \
--sheet ../Resources/res/funfilename/funfilename_funfilesubname.png \
funfilename/funfilesubname/*.png


... add more sheets ....
fi
exit 0