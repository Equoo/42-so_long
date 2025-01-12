

while (( 1 == 1 )); do
	echo "scale=10; $(grep now /proc/timer_list | sed "s/now at //" | sed "s/ nsecs//") / 1000000000" | bc
done
