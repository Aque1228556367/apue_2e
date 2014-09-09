set -o nounset                              # Treat unset variables as an error

 for i in $(ls fig*)
 do   
     mv "$i" "$i.c"
 done    
