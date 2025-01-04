# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/f4deb/esp/v5.3.2/esp-idf/components/bootloader/subproject"
  "/home/f4deb/Rotor_Azimut_V1/build/bootloader"
  "/home/f4deb/Rotor_Azimut_V1/build/bootloader-prefix"
  "/home/f4deb/Rotor_Azimut_V1/build/bootloader-prefix/tmp"
  "/home/f4deb/Rotor_Azimut_V1/build/bootloader-prefix/src/bootloader-stamp"
  "/home/f4deb/Rotor_Azimut_V1/build/bootloader-prefix/src"
  "/home/f4deb/Rotor_Azimut_V1/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/f4deb/Rotor_Azimut_V1/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/f4deb/Rotor_Azimut_V1/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
