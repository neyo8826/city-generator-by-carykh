cmake_minimum_required(VERSION 3.5)
cmake_policy(VERSION 3.5)
project(city-generator-by-carykh)

set(SOURCE_FILES
  main
  lang
  Camera
  House
  Scene
  Window
)

set(CMAKE_CXX_STANDARD 14)

if(MSVC)
  set(COMMON_MSVC_FLAGS "/MP /Qpar /EHsc /bigobj /W3 /wd4250 /wd4996 /wd4503")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_MSVC_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_MSVC_FLAGS}")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL /Gy")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG /OPT:REF,ICF")
  add_definitions(-DBOOST_ALL_NO_LIB)
else()
  #set(SAN "-fsanitize=memory -fsanitize-memory-use-after-dtor -fsanitize-memory-track-origins=1")
  #set(SAN "-fsanitize=undefined -fsanitize=integer")
  #set(SAN "-fsanitize=address -fno-omit-frame-pointer")
  #set(SAN "-fsanitize=thread")

  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CLANG_FLAGS "-Weverything -Wno-deprecated -Wno-shadow-field-in-constructor -Wno-padded -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-reserved-id-macro -Wno-weak-vtables -Wno-documentation -Wno-documentation-unknown-command -Wno-extended-offsetof -Wno-global-constructors -Wno-exit-time-destructors -Wno-disabled-macro-expansion -Wno-old-style-cast -Wno-undef -Wno-undefined-func-template -Wno-covered-switch-default -Wno-dollar-in-identifier-extension -Wno-comma -Wno-double-promotion -Wno-switch-enum")
  endif()

  set(COMMON_GCC_FLAGS "-fpic -fmessage-length=0 -pedantic -Wall -Wextra -Winit-self -Wsequence-point -Wconversion -Wsign-conversion -Wfloat-conversion -Wfloat-equal -Wshadow")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wstrict-prototypes ${COMMON_GCC_FLAGS}")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG -g3 -flto")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -DDEBUG -g3 ${SAN}")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-declarations ${COMMON_GCC_FLAGS} ${CLANG_FLAGS}")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG -g3 -flto")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -DDEBUG -g3 ${SAN}")

  set(COMMON_LINKER_FLAGS "-rdynamic -Wl,--no-undefined,--unresolved-symbols=report-all ${SAN}")
  set(CMAKE_EXE_LINKER_FLAGS "${COMMON_LINKER_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS "${COMMON_LINKER_FLAGS} -Wl,-Bsymbolic")
endif()

find_package(assimp REQUIRED)
if(NOT assimp)
  add_library(assimp INTERFACE IMPORTED)
  set_target_properties(assimp PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${FREETYPE_INCLUDE_DIRS}"
    INTERFACE_LINK_LIBRARIES "${FREETYPE_LIBRARIES}"
  )
endif()
find_package(Freetype REQUIRED)
if(NOT Freetype)
  add_library(Freetype INTERFACE IMPORTED)
  set_target_properties(Freetype PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${ASSIMP_INCLUDE_DIRS}"
    INTERFACE_LINK_LIBRARIES "${ASSIMP_LIBRARIES}"
  )
endif()
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
if(NOT OpenGL::GL)
  add_library(OpenGL::GL INTERFACE IMPORTED)
  set_target_properties(OpenGL::GL PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${OPENGL_INCLUDE_DIR}"
    INTERFACE_LINK_LIBRARIES "${OPENGL_gl_LIBRARY}"
  )
endif()
find_package(GLEW REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
target_link_libraries(${PROJECT_NAME} assimp Freetype glm glfw OpenGL::GL GLEW::GLEW)
