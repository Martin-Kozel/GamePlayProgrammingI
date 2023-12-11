CXX				:= g++

BUILD_DIR		:= ./bin
SRC_DIR			:= ./src

MSG_START		:= "Build Started"
MSG_END			:= "Build Complete"
MSG_CLEAN		:= "Cleaning up"


ifeq ($(OS),Windows_NT)
    os  := Windows
	INCLUDES	:= -I. -I./include
	LIBS		:= -L.
	CXXFLAGS 	:= -std=c++11 -Wall -Wextra -Werror -g ${INCLUDES}
	LIBRARIES	:= -llibsfml-graphics -llibsfml-window -llibsfml-system
	TARGET		:= ${BUILD_DIR}/sampleapp.exe
else
    os := $(shell uname -s)
	INCLUDES	:= -I. -I./include
	LIBS		:= -L.
	CXXFLAGS 	:= -std=c++11 -Wall -Wextra -Werror -g ${INCLUDES}
	LIBRARIES	:= -lsfml-graphics -lsfml-window -lsfml-system
	TARGET		:= ${BUILD_DIR}/sampleapp.bin
endif

SRC				:=	$(wildcard ${SRC_DIR}/*.cpp) # List the CPP src files

all				:= build

build: $(SRC)

	@echo 		${MSG_START} ${os}

	@echo 		"***	C++ Compiler	***"
	@echo 		${CXX}
	@echo 		"*** C++ Flags		***"
	@echo 		${CXXFLAGS}
	@echo 		"*** LIBRARIES		***"
	@echo 		${LIBRARIES}
	@echo 		"*** SRC		***"
	@echo 		${SRC}
	@echo 		"*** LIBRARIES		***"
	@echo 		${TARGET}

	#remove directory if it exits and then create directory
	rm -rf 		${BUILD_DIR} 	|| 	true

	#create bin directory
	mkdir 		${BUILD_DIR}

	${CXX} ${CXXFLAGS} -o ${TARGET} $^ ${LIBS} ${LIBRARIES}
	
	@echo ${MSG_END}
	
	# Run TARGET
	./${TARGET}

.PHONY: clean

clean:
	@echo 		${MSG_CLEAN}
	rm -rf 		${BUILD_DIR} || true