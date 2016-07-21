all:find mycp
.PHONY:all	
find:find.c
	gcc myfind.c -o find
mycp:mycp.c
	gcc mycp.c -o mycp
clean:
	rm find
