cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(bebarengan-sepur VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_FLAGS "-Wall -Werror -O3")
set(EXECUTABLE_OUTPUT_PATH ..)
add_executable(txtadventure Attack.cpp Character.cpp Detail.cpp Dialog.cpp Fight.cpp Game.cpp Item.cpp Person.cpp Player.cpp Room.cpp World.cpp func.cpp fuzzy.cpp Context.cpp WorldContext.cpp StandardContext.cpp FightContext.cpp DialogContext.cpp ChoiceContext.cpp main.cpp)
add_executable(unittest Attack.cpp Character.cpp Detail.cpp Dialog.cpp Fight.cpp Game.cpp Item.cpp Person.cpp Player.cpp Room.cpp World.cpp func.cpp fuzzy.cpp Context.cpp WorldContext.cpp StandardContext.cpp FightContext.cpp DialogContext.cpp ChoiceContext.cpp main.cpp)
if(MAKE_SERVER)
    target_compile_definitions(txtadventure PRIVATE _COMPILE_FOR_SERVER_=1)
endif()
target_compile_definitions(unittest PRIVATE _COMPILE_UNIT_TEST_=1)
target_link_libraries(unittest PRIVATE boost_system)
target_link_libraries(unittest PRIVATE pthread ssl crypto)

target_link_libraries(txtadventure PRIVATE boost_system)
target_link_libraries(txtadventure
	PRIVATE pthread ssl crypto
)
