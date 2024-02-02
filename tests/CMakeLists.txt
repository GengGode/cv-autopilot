add_executable(main_test main.cpp)
target_include_directories(main_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(main_test PRIVATE autopilot)
