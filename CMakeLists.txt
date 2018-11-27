cmake_minimum_required(VERSION 3.9)
project(qwertyattack)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-release/)

set(SOURCE_FILES
		common.hpp
		BasicKeyNote.hpp
		BasicKeyNote.cpp
		JudgementTally.hpp
		JudgementTally.cpp
		KeyChart.hpp
		KeyChart.cpp
		KeyNote.hpp
		SongRun.hpp
		SongRun.cpp)

set(TEST_SOURCE_FILES
		tests/catch.hpp
		tests/test_KeyChart.cpp)



if(1)
	add_executable(qwertyattack main.cpp ${SOURCE_FILES})
	add_executable(test_qwertyattack tests/test_main.cpp ${SOURCE_FILES} ${TEST_SOURCE_FILES})

	find_package(Threads)
	include_directories("/usr/local/include")
	link_directories("/usr/lib")
	target_link_libraries(qwertyattack ${CMAKE_THREAD_LIBS_INIT})
	target_link_libraries(qwertyattack "/usr/local/lib/libsfml-audio.so")
	target_link_libraries(qwertyattack "/usr/local/lib/libsfml-graphics.so")
	target_link_libraries(qwertyattack "/usr/local/lib/libsfml-system.so")
	target_link_libraries(qwertyattack "/usr/local/lib/libsfml-window.so")
	target_link_libraries(test_qwertyattack "/usr/local/lib/libsfml-audio.so")
	target_link_libraries(test_qwertyattack "/usr/local/lib/libsfml-graphics.so")
	target_link_libraries(test_qwertyattack "/usr/local/lib/libsfml-system.so")
	target_link_libraries(test_qwertyattack "/usr/local/lib/libsfml-window.so")
endif(1)



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