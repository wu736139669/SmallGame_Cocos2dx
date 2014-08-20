#!/bin/sh

echo sssss   
        
DIRLIST=./
  
for DIR in `cat $DIRLIST`  
do  
    if [[ ! -d $DIR ]]  
    	echo 1
    then  
        echo $DIR not exists  
        continue  
    fi  

done
