set -o nounset                              # Treat unset variables as an error

if [ ! -d "debug" ]; 
then
  mkdir debug
fi

if [ ! -d "bin" ]; 
then
  mkdir bin
fi

if [ ! -d "fig" ]; 
then
  mkdir fig
fi


for i in $(ls ../src/fig/fig*)
do
	echo ${i}
	filename=${i#*../src/fig/}
	cp "$i" "./fig/$filename.c"
	sed -i '1i\#include "myerr.h"' "./fig/$filename.c"
done   
 
# cp ../src/fig/fig1.3 ./fig/fig1.3.c