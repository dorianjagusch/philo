!#/bin/bash
for i in {1..200}
do 
    grep " $i is eating" out | wc -l
done