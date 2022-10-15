project(BC)

set(CMAKE_BUILD_TYPE "Debug")


add_executable(bc betterCalculator.cpp cal.hpp Math.cpp
addOrSub.cpp add.cpp sub.cpp mul.cpp div.cpp pow.cpp divLeft.cpp)