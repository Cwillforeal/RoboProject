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

CPP_FLAGS = -static $(INC_PATHS) $(WARNINGS) -O0 -g3 -std=c++11 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"

#Set include paths and files
INC_PATHS = -I./inc -I./external_libs/BME280_driver

BUILD_NAME = ROBO

#Get the source cpp files listed for building
SRC_CPP = \
    src/BusDevice.cpp \
    src/distance.cpp \
    src/I2CDevice.cpp \
    src/main.cpp \
    src/orientation.cpp

SRC_C = \
    external_libs/BME280_driver/bme280.c

OBJ_C := $(patsubst %.c, %.o, $(SRC_C)) 
DEP_C := $(patsubst %.c, %.d, $(SRC_C))
OBJ_CPP := $(patsubst %.cpp, %.o, $(SRC_CPP))
DEP_CPP := $(patsubst %.cpp, %.d, $(SRC_CPP))
#Now we add the two together to simplify
OBJ_CPP += $(OBJ_C)
DEP_C += $(DEP_C)

#List where the object files should be placed/ are placed
OBJ_LOCATION := $(patsubst %.o, $(OBJ_DIR)/%.o, $(notdir $(OBJ_CPP)))

DEPENDENCIES := $(patsubst %.cpp, $(OBJ_DIR)/%.d, $(notdir $(SRC_CPP)))

#Tell make where to look for source files
vpath %.cpp ./src/
vpath %.c ./external_libs/BME280_driver/ 

all:
	$(MAKE) $(BUILD_NAME)

#Build the executable
$(BUILD_NAME): $(OBJ_LOCATION)
	@echo 'Building: $@'
	$(CCpp) -static $(LIB_PATHS) -o "DEBUG/$(BUILD_NAME)" $(OBJ_LOCATION) $(LIBS)
	@echo 'Finished Building $@'

#Build the cpp sources
$(OBJ_DIR)/%.o: %.cpp 
	@echo 'Building: $@'
	$(CCpp) $(CPP_FLAGS) -Dcpp -c $< -o $(OBJ_DIR)/$(notdir $@)
	@echo 'Finished Building $@'

#Build the c sources
$(OBJ_DIR)/%.o: %.c
	@echo 'Building: $@'
	$(CCpp) $(CPP_FLAGS) -Dcpp -c $< -o $(OBJ_DIR)/$(notdir $@)
	@echo 'Finished Building $@'
    
clean:
	-$(CLEAN) $(OBJ_LOCATION) $(DEPENDENCIES) DEBUG/$(BUILD_NAME)

run:
	$(OBJ_DIR)/$(BUILD_NAME).exe

-include $(DEPENDENCIES)
