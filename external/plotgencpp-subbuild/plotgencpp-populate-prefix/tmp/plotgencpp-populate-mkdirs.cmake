# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/thierry/Desktop/Github_projects/Roboter/external/plotgencpp-src")
  file(MAKE_DIRECTORY "/home/thierry/Desktop/Github_projects/Roboter/external/plotgencpp-src")
endif()
file(MAKE_DIRECTORY
  "/home/thierry/Desktop/Github_projects/Roboter/external/plotgencpp-build"
  "/home/thierry/Desktop/Github_projects/Roboter/external/plotgencpp-subbuild/plotgencpp-populate-prefix"
  "/home/thierry/Desktop/Github_projects/Roboter/external/plotgencpp-subbuild/plotgencpp-populate-prefix/tmp"
  "/home/thierry/Desktop/Github_projects/Roboter/external/plotgencpp-subbuild/plotgencpp-populate-prefix/src/plotgencpp-populate-stamp"
  "/home/thierry/Desktop/Github_projects/Roboter/external/plotgencpp-subbuild/plotgencpp-populate-prefix/src"
  "/home/thierry/Desktop/Github_projects/Roboter/external/plotgencpp-subbuild/plotgencpp-populate-prefix/src/plotgencpp-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/thierry/Desktop/Github_projects/Roboter/external/plotgencpp-subbuild/plotgencpp-populate-prefix/src/plotgencpp-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/thierry/Desktop/Github_projects/Roboter/external/plotgencpp-subbuild/plotgencpp-populate-prefix/src/plotgencpp-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
