cmake_minimum_required(VERSION 3.10)
find_package(Boost REQUIRED)

# set the project name and version
project(bebarengan-sepur VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH ..)

add_executable(txtadventure Attack.cpp Character.cpp CommandParser.cpp Detail.cpp Dialog.cpp Fight.cpp Game.cpp Item.cpp Person.cpp Player.cpp Room.cpp World.cpp func.cpp fuzzy.cpp main.cpp)
target_link_libraries(txtadventure ${Boost_LIBRARIES})
target_link_libraries(txtadventure
	PRIVATE pthread
)
