if(NOT TARGET PretzelGui)
    # Define ${PretzelGui_PROJECT_ROOT}. ${CMAKE_CURRENT_LIST_DIR} is just the current directory.
    get_filename_component(PretzelGui_PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)

    # Define ${CINDER_PATH} as usual.
    get_filename_component(CINDER_PATH "${PretzelGui_PROJECT_ROOT}/../.." ABSOLUTE)

    file(GLOB SOURCE_LIST CONFIGURE_DEPENDS
        "${PretzelGui_PROJECT_ROOT}/src/components/*.cpp"
        "${PretzelGui_PROJECT_ROOT}/src/modules/*.cpp"
        "${PretzelGui_PROJECT_ROOT}/src/pretzel/*.cpp"
    )

    # Translate the <sourcePattern> tag.
    add_library(PretzelGui ${SOURCE_LIST})

    # Compile this file as .mm for macosx.
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set_source_files_properties("${PretzelGui_PROJECT_ROOT}/src/pretzel/PretzelGlobal.cpp" PROPERTIES COMPILE_FLAGS "-x objective-c++")
    endif()

    # Translate <includePath> tag.
    target_include_directories(PretzelGui PUBLIC
        "${PretzelGui_PROJECT_ROOT}/src"
    )

    # Translate <headerPattern> tag.
    target_include_directories(PretzelGui PRIVATE
        "${PretzelGui_PROJECT_ROOT}/include/pretzel"
        "${PretzelGui_PROJECT_ROOT}/include/modules"
        "${PretzelGui_PROJECT_ROOT}/include/components"
    )

    # Translate the <resource> tag.
    get_filename_component(RESOURCES_DEST_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources" ABSOLUTE)
    file(COPY "${PretzelGui_PROJECT_ROOT}/resources" DESTINATION "${RESOURCES_DEST_PATH}")

    target_include_directories(PretzelGui SYSTEM BEFORE PUBLIC "${CINDER_PATH}/include" )

    if(NOT TARGET cinder)
        include("${CINDER_PATH}/proj/cmake/configure.cmake")
        find_package(cinder REQUIRED PATHS
                "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
                "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}")
    endif()
    target_link_libraries(PretzelGui PRIVATE cinder)
endif()