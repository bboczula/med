OBJS = CClock.o CLogger.o CInputHandler.o CParser.o CCommandFactory.o
OBJS_REL = main.o
OBJS_MT = tmain.o
OBJS_UT = CParserTest.o

### This is the rule for making release binary
med : $(OBJS_REL) $(OBJS)
	g++ -std=c++11 -o med $(OBJS_REL) $(OBJS)

### This is the rule for making binary for module test
tmed : $(OBJS_MT) $(OBJS)
	g++ -std=c++11 -o tmed $(OBJS_MT) $(OBJS)

### This is the rule for making unit tests
gtest : $(OBJS_UT) $(OBJS)
	g++ -std=c++11 -I${GTEST_DIR}/include -L${GTEST_DIR}/lib -o test $(OBJS_UT) $(OBJS) -lgtest -lpthread

CInputHandler.o : CInputHandler.h CInputHandler.cpp CStorageHandler.h CLogger.h CCommandFactory.h ICommand.h CExceptions.h CParser.h
	g++ -std=c++11 -c CInputHandler.cpp

main.o : main.cpp CStorageHandler.h CCommandFactory.h CInputHandler.h CLogger.h
	g++ -std=c++11 -c main.cpp

tmain.o : tmain.cpp CStorageHandler.h CCommandFactory.h CInputHandler.h CLogger.h
	g++ -std=c++11 -c tmain.cpp

CCommandFactory.o : CCommandFactory.h CCommandFactory.cpp ICommand.h SCommonStructures.h
	g++ -std=c++11 -c CCommandFactory.cpp

CParser.o : CParser.cpp CParser.h SCommonStructures.h
	g++ -std=c++11 -c CParser.cpp

CParserTest.o : CParserTest.cpp CParser.h
	g++ -std=c++11 -c CParserTest.cpp

CClock.o : CClock.h CClock.cpp
	g++ -std=c++11 -c CClock.cpp

CLogger.o : CLogger.h CLogger.cpp
	g++ -std=c++11 -c CLogger.cpp

.PHONY : clean
clean :
	rm -f test med tmed $(OBJS_UT) $(OBJS_MT) $(OBJS_REL) $(OBJS)
