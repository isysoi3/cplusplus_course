project(${CMAKE_PROJECT_NAME}_lib)

set(HEADER_FILES
        JSON/JSON.h
        Reader/Reader.h
        )
set(SOURCE_FILES
        JSON/JSON.cpp
        Reader/Reader.cpp
        Utils/Helpers.cpp
        Reader/ReaderException.h
        JSON/JSONException.h
        )

#if (EXISTS ${SOURCE_FILES})
#    # The library contains header and source files.
#    add_library(${CMAKE_PROJECT_NAME}_lib STATIC
#            ${SOURCE_FILES}
#            ${HEADER_FILES}
#            )
#else()
#    # The library only contains header files.
#    add_library(${CMAKE_PROJECT_NAME}_lib INTERFACE)
#endif()

add_library(${CMAKE_PROJECT_NAME}_lib STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )