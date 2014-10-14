OBJS = CClock.o CLogger.o CInputHandler.o CParser.o CCommandFactory.o
OBJS_REL = main.o
OBJS_MT = tmain.o

# This is the rule for making release binary
med : $(OBJS_REL) $(OBJS)
	g++ -std=c++11 -o med $(OBJS_REL) $(OBJS)

# This is the rule for making binary for module test
tmed : $(OBJS_MT) $(OBJS)
	g++ -std=c++11 -o tmed $(OBJS_MT) $(OBJS)

main.o : main.cpp CStorageHandler.h ICommand.h CInputHandler.h CLogger.h
	g++ -std=c++11 -c main.cpp

tmain.o : tmain.cpp CStorageHandler.h ICommand.h CInputHandler.h CLogger.h
	g++ -std=c++11 -c tmain.cpp

CClock.o : CClock.h CClock.cpp
	g++ -std=c++11 -c CClock.cpp

CLogger.o : CLogger.h CLogger.cpp
	g++ -std=c++11 -c CLogger.cpp

CInputHandler.o : CInputHandler.h CInputHandler.cpp CLogger.h CExceptions.h
	g++ -std=c++11 -c CInputHandler.cpp

CParser.o : CParser.cpp CParser.h SCommonStructures.h
	g++ -std=c++11 -c CParser.cpp

CCommandFactory.o : CCommandFactory.h CCommandFactory.cpp SCommonStructures.h
	g++ -std=c++11 -c CCommandFactory.cpp

.PHONY : clean
clean :
	rm -f med tmed $(OBJS_MT) $(OBJS_REL) $(OBJS)

gtest:
	g++ -std=c++11 -I${GTEST_DIR}/include -L${GTEST_DIR}/lib CStorageHandlerTest.cpp CClock.h CClock.cpp CLogger.h CLogger.cpp CStorage.h CStorageHandler.h CInputHandler.h CInputHandler.cpp ICommand.h -o test -lgtest -lpthread 
