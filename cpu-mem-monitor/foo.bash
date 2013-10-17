#!/bin/bash



while true
do


ps -eo pcpu,pmem,pid,args | sort -k 1 -r | head -6
echo -e "\n"
       	

	cat /proc/loadavg
	ps aux | head -n1



	for var in $@
        do
  
                
		
		ps aux | egrep -i "$var" | grep -v "egrep" | grep -v "bash"
  	   
		
        	       

   
   

	done
   echo -e "\n" 

   
	sleep 2
done
