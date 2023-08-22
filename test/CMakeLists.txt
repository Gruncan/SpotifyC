
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)


add_executable(${PROJECT_TARGET_EXE} "main.c")
target_link_libraries(${PROJECT_TARGET_EXE} PUBLIC ${PROJECT_TARGET_LIB}
                                Threads::Threads)