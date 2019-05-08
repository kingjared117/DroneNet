all:
	gcc -g -pthread -o part1/wifisync part1/main.c part1/project3.c
	gcc -g -pthread -o part2/wifisync part2/main.c part2/project3.c
p1:
	gcc -g -pthread -o part1/wifisync part1/main.c part1/project3.c
p2:
	gcc -g -pthread -o part2/wifisync part2/main.c part2/project3.c
clean:
	$(RM) part1/wifisync
	$(RM) part2/wificync
	
