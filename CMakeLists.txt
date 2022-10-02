cmake_minimum_required(VERSION 3.18.0)
project(ProjectName VERSION 0.1.0 LANGUAGES CXX)

#-----------------------------

add_executable(pomland)

target_compile_features(pomland PRIVATE cxx_std_20)
set_target_properties(pomland PROPERTIES CXX_EXTENSIONS off)

target_include_directories(pomland PRIVATE external)

add_subdirectory(source)

#-----------------------------
# Link any dependencies...

find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(pomland PRIVATE sfml-system sfml-window sfml-graphics sfml-audio OpenGL::GL)
# target_link_libraries(main PRIVATE X11 FLAC UDev OpenAL)
