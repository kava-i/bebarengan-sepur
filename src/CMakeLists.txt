cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(bebarengan-sepur VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_FLAGS "-Wall -Werror -O3")
set(EXECUTABLE_OUTPUT_PATH ..)
if(MAKE_SERVER)
    add_definitions( -D_COMPILE_FOR_SERVER_=1)
endif()
if(MAKE_DEBUG)
    add_definitions( -D_COMPILE_DEBUG_=1)
endif()

add_executable(txtadventure Attack.cpp Character.cpp Detail.cpp Dialog.cpp Fight.cpp Game.cpp Item.cpp Person.cpp Player.cpp Room.cpp World.cpp func.cpp fuzzy.cpp Context.cpp WorldContext.cpp StandardContext.cpp FightContext.cpp DialogContext.cpp ChoiceContext.cpp main.cpp)
target_link_libraries(txtadventure PRIVATE boost_system)
target_link_libraries(txtadventure
	PRIVATE pthread ssl crypto
)
