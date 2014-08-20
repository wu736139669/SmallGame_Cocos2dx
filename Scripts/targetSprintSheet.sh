#! /bin/sh
TP=/usr/local/bin/TexturePacker
if [ "${ACTION}" = "clean" ]
then
# remove all files
#rm ../Resources/Assets/*.png
#rm ../Resources/Assets/*.plist
else
echo "TexturePacker building..."

#当前设置路径为Assets

#创建目录
#mkdir -p ../Resources/res/test

#1.调用TP生成sprintsheet
#2.到--data和--sheet时会自动创建目录
#3.最后小图从Assets取得,路径对应Assets里面的

#CocoStudioResources
echo "CocoStudioResources building..."
${TP} --smart-update \
--format cocos2d \
--data ../Resources/CocoStudioResources/layoutLoading0/layoutLoading0.plist \
--sheet ../Resources/CocoStudioResources/layoutLoading0/layoutLoading0.png \
CocoStudioResources/layoutLoading0/*.png




... add more sheets ....
fi
exit 0