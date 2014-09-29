all:
	g++ -std=c++11 main.cpp CClock.h CClock.cpp CLogger.h CLogger.cpp CStorage.h CStorageHandler.h CInputHandler.h CInputHandler.cpp ICommand.h -o med

test:
	g++ -std=c++11 -I${GTEST_DIR}/include -L${GTEST_DIR}/lib CStorageHandlerTest.cpp CClock.h CClock.cpp CLogger.h CLogger.cpp CStorage.h CStorageHandler.h CInputHandler.h CInputHandler.cpp ICommand.h -o test -lgtest -lpthread 
