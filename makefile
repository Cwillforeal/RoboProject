#*************************************************************************************************/
#*-------------------------------------------PROLOGUE--------------------------------------------*/
#*
#* Makefile: For monitor_dxe Unit Testing
#*


#*************************************************************************************************/
#*-------------------------------------------INCLUDES--------------------------------------------*/

#*************************************************************************************************/
#*------------------------------------------VARIABLES--------------------------------------------*/
#Compiler defines
CCpp = arm-linux-gnueabihf-g++

CLEAN := rm -rf

#Location for created files
OBJ_DIR = ./DEBUG/obj
#Create the output directories in case they don't exist
$(shell mkdir -p $(OBJ_DIR))

#Libraries and Paths
LIB_PATHS =
LIBS      =

#Set the Warnings level
WARNINGS = -Wall

#-MMD: Create a .d file and strip away all the directory information
#-MP: Create phony header files in case one has been removed and the makefile doesn't match yet

CPP_FLAGS = $(INC_PATHS) $(WARNINGS) -O0 -g3 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"

#Set include paths and files
INC_PATHS = -I"./inc"

BUILD_NAME = ROBO

#Get the source cpp files listed for building
SRC_CPP := $(wildcard ./src/*.cpp)
OBJ_CPP := $(patsubst %.cpp, %.o, $(SRC_CPP))
DEP_CPP := $(patsubst %.cpp, %.d, $(SRC_CPP))

#List where the object files should be placed/ are placed
OBJ_LOCATION := $(patsubst %.o, $(OBJ_DIR)/%.o, $(notdir $(OBJ_CPP)))

DEPENDENCIES := $(patsubst %.cpp, $(OBJ_DIR)/%.d, $(notdir $(SRC_CPP)))

#Tell make where to look for source files
vpath %.cpp ./src/


all:
	$(MAKE) $(BUILD_NAME)

#Build the executable
$(BUILD_NAME): $(OBJ_LOCATION)
	@echo 'Building: $@'
	$(CCpp) $(LIB_PATHS) -o "DEBUG/$(BUILD_NAME)" $(OBJ_LOCATION) $(LIBS)
	@echo 'Finished Building $@'

#Build the cpp sources
$(OBJ_DIR)/%.o: %.cpp
	@echo 'Building: $@'
	$(CCpp) $(CPP_FLAGS) -Dcpp -c $< -o $(OBJ_DIR)/$(notdir $@)
	@echo 'Finished Building $@'

clean:
	-$(CLEAN) $(OBJ_LOCATION) $(BUILD_NAME) $(DEPENDENCIES)

run:
	$(OBJ_DIR)/$(BUILD_NAME).exe

-include $(DEPENDENCIES)