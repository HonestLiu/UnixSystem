#!/bin/bash
for ((i = 0; i < 10; i++)); 
do
	fileName="file${i}"
	touch "${fileName}.txt"
	echo ${fileName} >>"${fileName}.txt"
done
