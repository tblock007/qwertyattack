cmake_minimum_required(VERSION 3.9)
project(qwertyattack)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-release/)

set(SOURCE_FILES
		constants.hpp
		DataKeyNotes.hpp
		DataKeyNotes.cpp
		Judgements.hpp
		Judgements.cpp
		JudgementTally.hpp
		JudgementTally.cpp
		KeyChart.hpp
		KeyChart.cpp
		KeyPresses.hpp 
		KeyPresses.cpp
		SongRun.hpp
		SongRun.cpp
		TextNote.hpp
		TextNote.cpp
        utility.hpp)

set(TEST_SOURCE_FILES
		tests/catch.hpp
		tests/test_JudgementTally.cpp
		tests/test_KeyChart.cpp)


if(LINUX)
	add_executable(qwertyattack main.cpp ${SOURCE_FILES})
	add_executable(test_qwertyattack tests/test_main.cpp ${SOURCE_FILES} ${TEST_SOURCE_FILES})

	find_package(Threads)
	include_directories("/usr/include")
	target_link_libraries(qwertyattack ${CMAKE_THREAD_LIBS_INIT})
	target_link_libraries(qwertyattack "/usr/lib/SFML/libsfml-audio.so")
	target_link_libraries(qwertyattack "/usr/lib/SFML/libsfml-graphics.so")
	target_link_libraries(qwertyattack "/usr/lib/SFML/libsfml-window.so")
	target_link_libraries(qwertyattack "/usr/lib/SFML/libsfml-system.so")
	target_link_libraries(test_qwertyattack "/usr/lib/SFML/libsfml-audio.so")
	target_link_libraries(test_qwertyattack "/usr/lib/SFML/libsfml-graphics.so")
	target_link_libraries(test_qwertyattack "/usr/lib/SFML/libsfml-window.so")
	target_link_libraries(test_qwertyattack "/usr/lib/SFML/libsfml-system.so")
endif(LINUX)



if(WIN32)
	add_executable(qwertyattack main.cpp ${SOURCE_FILES})
	add_executable(test_qwertyattack tests/test_main.cpp ${SOURCE_FILES} ${TEST_SOURCE_FILES})

	include_directories("C:\\Program Files (x86)\\Microsoft Visual Studio\\Shared\\include")
	link_directories("C:\\Program Files (x86)\\Microsoft Visual Studio\\Shared\\lib")
	target_link_libraries(qwertyattack "C:\\Program Files (x86)\\Microsoft Visual Studio\\Shared\\lib\\SFML\\sfml-audio.lib")
	target_link_libraries(qwertyattack "C:\\Program Files (x86)\\Microsoft Visual Studio\\Shared\\lib\\SFML\\sfml-graphics.lib")
	target_link_libraries(qwertyattack "C:\\Program Files (x86)\\Microsoft Visual Studio\\Shared\\lib\\SFML\\sfml-system.lib")
	target_link_libraries(qwertyattack "C:\\Program Files (x86)\\Microsoft Visual Studio\\Shared\\lib\\SFML\\sfml-window.lib")
	target_link_libraries(test_qwertyattack "C:\\Program Files (x86)\\Microsoft Visual Studio\\Shared\\lib\\SFML\\sfml-audio.lib")
	target_link_libraries(test_qwertyattack "C:\\Program Files (x86)\\Microsoft Visual Studio\\Shared\\lib\\SFML\\sfml-graphics.lib")
	target_link_libraries(test_qwertyattack "C:\\Program Files (x86)\\Microsoft Visual Studio\\Shared\\lib\\SFML\\sfml-system.lib")
	target_link_libraries(test_qwertyattack "C:\\Program Files (x86)\\Microsoft Visual Studio\\Shared\\lib\\SFML\\sfml-window.lib")
endif(WIN32)