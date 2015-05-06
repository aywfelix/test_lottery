#!/bin/bash
icount=`cat $1|wc -l`
let icount=icount;
echo "total="${icount};
for ((i=1; i<=12; ++i))
do
  cat $1|awk -F'|' -v num=$i -v total=$icount 'BEGIN{c1=0;} {if ($1==num) c1=c1+1;} END{print num"="c1/total*100"%"}'
done
