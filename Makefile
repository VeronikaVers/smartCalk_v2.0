CPP=g++ -std=c++17
TEST_LIBS=-lgtest -lgmock -pthread
GCOVFLAGS= -fprofile-arcs -ftest-coverage
SOURCES=model/tests.cc model/calculatormodel.cc
ARCHIVE = Archive_SmartCalc_v2.0


all: clean tests

tests:
	@$(CPP) $(SOURCES) $(TEST_SOURCES) -o test $(TEST_LIBS)
	@./test

install: clean uninstall
	@mkdir build
	@cd View && qmake && make && make clean && rm Makefile && cd ../ && mv View/View.app build/SmartCalc_v2_0.app

uninstall:
	@rm -rf build

dist:
	@rm -rf $(ARCHIVE)/
	@mkdir $(ARCHIVE)/
	@mkdir $(ARCHIVE)/src
	@cp -r Makefile View Model Controller Dvi $(ARCHIVE)/src
	@tar cvzf $(ARCHIVE).tgz $(ARCHIVE)/
	@# mv $(ARCHIVE).tgz $(HOME)/Desktop/
	@rm -rf $(ARCHIVE)/

dvi_:
	open Dvi/dvi.html


clean:
	@rm -rf test 
	@cd View
	@rm -rf *.o *.a *.out 
	@rm -rf *.gcda *.gcno *.info *.gch
	@ rm -rf test report


clang:
	@clang-format -style=Google -n Controller/*.h Controller/*.cc Model/*.h Model/*.cc View/*.h View/*.cc

clang_correct:
	@clang-format -style=Google -i Controller/*.h Controller/*.cc Model/*.h Model/*.cc View/*.h View/*.cc