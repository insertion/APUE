all:find mycp logkey
.PHONY:all	
find:find.c
	gcc myfind.c -o find
mycp:mycp.c
	gcc mycp.c -o mycp
logkey:keyboard.c
	gcc keyboard.c -o logkey
clean:
	rm find
