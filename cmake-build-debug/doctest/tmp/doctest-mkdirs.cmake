# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "S:/Downloads/AISnake/cmake-build-debug/doctest/src/doctest"
  "S:/Downloads/AISnake/cmake-build-debug/doctest/src/doctest-build"
  "S:/Downloads/AISnake/cmake-build-debug/doctest"
  "S:/Downloads/AISnake/cmake-build-debug/doctest/tmp"
  "S:/Downloads/AISnake/cmake-build-debug/doctest/src/doctest-stamp"
  "S:/Downloads/AISnake/cmake-build-debug/doctest/src"
  "S:/Downloads/AISnake/cmake-build-debug/doctest/src/doctest-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "S:/Downloads/AISnake/cmake-build-debug/doctest/src/doctest-stamp/${subDir}")
endforeach()
