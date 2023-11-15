CXX				:= g++

BUILD_DIR		:= ./bin
SRC_DIR			:= ./src

MSG_START		:= "Build Started"
MSG_END			:= "Build Complete"
MSG_CLEAN		:= "Cleaning up"


ifeq ($(OS),Windows_NT)
    os  := Windows
	# Make sure your Env Variable is set to SFML
	# Tested with SFML 2.5.1 GCC 7.3.0 MinGW (SEH) - 64-bit
	# Convert Windows directory path to UNIX Path
	SDK			:=${MYSYS2}
	SDK_PATH	:=$(subst \,/,$(subst C:\,/c/,$(SDK)))
	INCLUDES	:= -I${SDK_PATH}/include -I.
	LIBS		:= -L${SDK_PATH}/lib
	CXXFLAGS 	:= -std=c++11 -Wall -Wextra -g ${INCLUDES}
	LIBRARIES	:= -llibsfml-graphics -llibsfml-window -llibsfml-system
	TARGET		:= ${BUILD_DIR}/sampleapp.exe
else
    os := $(shell uname -s)
	INCLUDES	:= -I.
	LIBS		:= -L.
	CXXFLAGS 	:= -std=c++11 -Wall -Wextra -g ${INCLUDES}
	LIBRARIES	:= -lsfml-graphics -lsfml-window -lsfml-system
	TARGET		:= ${BUILD_DIR}/sampleapp.bin
endif

SRC				:= ${SRC_DIR}/main.cpp ${SRC_DIR}/Game.cpp ${SRC_DIR}/Player.cpp ${SRC_DIR}/NPC.cpp ${SRC_DIR}/GameObject.cpp ${INCLUDES}/cute_c2.h

all				:= build

build:
	@echo 	${MSG_START} ${os}

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

	${CXX} ${CXXFLAGS} -o ${TARGET} ${SRC} ${LIBS} ${LIBRARIES}
	
	@echo ${MSG_END}
	
	# Run TARGET
	./${TARGET}

.PHONY: clean

clean:
	@echo 		${MSG_CLEAN}
	rm -rf 		${BUILD_DIR} || true