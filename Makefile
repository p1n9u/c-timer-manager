.PHONY: all main clean

CC = g++

LIBS = -lm -lnsl
MGR_LIB = -lCTIMERMgrEngine
MGR_LIB_DIR = -L./timer-manager -Wl,-rpath,./timer-manager

all: main

main: ctimermgr main.o 
	$(CC) -o $@ main.o $(LIBS) $(MGR_LIB_DIR) $(MGR_LIB)

ctimermgr:
	$(CC) -fPIC -c ./timer-manager/timer-manager.cpp $(INCS) $(LIBS_DIRS) $(LIBS)
	$(CC) -shared -o ./timer-manager/libCTIMERMgrEngine.so timer-manager.o $(INCS) $(LIBS_DIRS) $(LIBS)

clean:
	rm -f main *.o
	rm -f ./timer-manager/libCTIMERMgrEngine.so