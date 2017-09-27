########################################
##
## Makefile
## LINUX compilation 
##
##############################################





#FLAGS
C++FLAG = -g -std=c++11 -Wall

#Math Library
MATH_LIBS = -lm
EXEC_DIR=.





#Rule for .cpp files
# .SUFFIXES : .cpp.o 

.cpp.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@




#Including
INCLUDES=  -I. 


LIBS_ALL =  -L/usr/lib -L/usr/local/lib $(MATH_LIBS) 


#ZEROTH PROGRAM
ALL_OBJ0=TestInsertAndSearch.o 
PROGRAM_0=TestInsertAndSearch
$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ1=TestInsertAndDelete.o 
PROGRAM_1=TestInsertAndDelete
$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)


#Compiling all

all: 	
		make $(PROGRAM_0)
		make $(PROGRAM_1)


Search5: 	
		./$(PROGRAM_0) 5_numbers.txt  100_test_search.txt

Search20: 	
		./$(PROGRAM_0) 20_numbers.txt 100_test_search.txt

Search100: 	
		./$(PROGRAM_0) 100_numbers.txt 100_test_search.txt

Search1000: 	
		./$(PROGRAM_0) 1000_numbers.txt 1000_test_search.txt

Delete100: 	
		./$(PROGRAM_1) 100_numbers.txt 100_test_deletion.txt

Delete1000: 	
		./$(PROGRAM_1) 1000_numbers.txt 1000_test_deletion.txt

Delete10000: 	
		./$(PROGRAM_1) 10000_numbers.txt 1000_test_deletion.txt

Delete5: 	
		./$(PROGRAM_1) 5_numbers.txt 100_test_deletion.txt



#Clean obj files

clean:
	(rm -f *.o; rm -f $(PROGRAM_0); rm -f $(PROGRAM_1))



(:
