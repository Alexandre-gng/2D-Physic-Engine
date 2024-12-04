cmake_minimum_required(VERSION 3.28)
project(Clothes)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(Clothes
        main.cpp
        ClassParticle.h
        ClassCloth.h
        FunctionsCloth.cpp
        ClassObject.h
        ClassPhysic.h
        ClassPhysic.h
        ClassConstraint.h
        ClassStretchingConstraint.h
        ClassTriangle.h
        ClassJoint.h
        FunctionsPhysic.cpp
        Common.h
        FunctionsParticle.cpp
        FunctionsStretchingConstraint.cpp
        FunctionsJoint.cpp
        FunctionsObject.cpp
)

target_link_libraries(Clothes sfml-graphics)