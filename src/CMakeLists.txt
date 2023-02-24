set(SOURCE_FILES
    main.cpp
    ChromosomePrinter.cpp)

add_executable(main ${SOURCE_FILES})
target_link_libraries(main
    ${EXTERNAL_LIBS}/libmysqlcppconn.so)
