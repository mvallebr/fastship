#!/bin/sh

rm -f ../levels/level*.fas

for x in 1 2 3 4 5 6 7 8 9
do		
	./levmaker ../levels/level$x.fas 20 $x	
done

for x in 10 11 12 13 14 
do		
	./levmaker ../levels/level$x.fas 25 $x	
done

for x in 15 16
do		
	./levmaker ../levels/level$x.fas 35 $x	
done

for x in 17
do		
	./levmaker ../levels/level$x.fas 80 $x	
done

