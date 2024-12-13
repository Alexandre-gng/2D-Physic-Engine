cmake_minimum_required(VERSION 3.28)
project(Clothes)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(Clothes
        main.cpp
        include/ClassParticle.hpp
        include/Objects/ClassCloth.hpp
        source/Cloth.cpp
        include/Objects/ClassObject.hpp
        include/ClassPhysic.hpp
        include/ClassPhysic.hpp
        include/Constraints/ClassConstraint.hpp
        include/Constraints/ClassStretchingConstraint.hpp
        include/ClassTriangle.hpp
        include/ClassJoint.hpp
        include/Common.h
        source/Physic.cpp
        source/Particle.cpp
        source/StretchingConstraint.cpp
        source/Joint.cpp
        source/Object.cpp
        include/Constraints/ClassRigidBodyColConstraint.hpp
        source/RigidBodyColConstraint.cpp
        include/Objects/ClassWall.hpp
)

target_link_libraries(Clothes sfml-graphics)