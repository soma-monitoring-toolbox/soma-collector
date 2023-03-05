# Install script for directory: /users/dewiy/soma-collector/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/users/dewiy/soma-collector/build")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-admin.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-admin.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/users/dewiy/soma-collector/build/src/libsoma-admin.so.0.1.0"
    "/users/dewiy/soma-collector/build/src/libsoma-admin.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-admin.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-admin.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib::::::::::::::::::::::::::::::::::::::"
           NEW_RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-admin.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-admin.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-admin.so"
         RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/users/dewiy/soma-collector/build/src/libsoma-admin.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-admin.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-admin.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-admin.so"
         OLD_RPATH "/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib::::::::::::::::::::::::::::::::::::::"
         NEW_RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-admin.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-server.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-server.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-abt-io-0.5.1-djwn4yord5fdfz52nbqau57d2nliteor/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/users/dewiy/soma-collector/build/src/libsoma-server.so.0.1.0"
    "/users/dewiy/soma-collector/build/src/libsoma-server.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-server.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-server.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-abt-io-0.5.1-djwn4yord5fdfz52nbqau57d2nliteor/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib::::::::::::::::::::::::::::::::::::::"
           NEW_RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-abt-io-0.5.1-djwn4yord5fdfz52nbqau57d2nliteor/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-server.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-server.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-server.so"
         RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-abt-io-0.5.1-djwn4yord5fdfz52nbqau57d2nliteor/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/users/dewiy/soma-collector/build/src/libsoma-server.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-server.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-server.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-server.so"
         OLD_RPATH "/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-abt-io-0.5.1-djwn4yord5fdfz52nbqau57d2nliteor/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib::::::::::::::::::::::::::::::::::::::"
         NEW_RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-abt-io-0.5.1-djwn4yord5fdfz52nbqau57d2nliteor/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-server.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-client.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-client.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/users/dewiy/soma-collector/build/src/libsoma-client.so.0.1.0"
    "/users/dewiy/soma-collector/build/src/libsoma-client.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-client.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-client.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib::::::::::::::::::::::::::::::::::::::"
           NEW_RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-client.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-client.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-client.so"
         RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/users/dewiy/soma-collector/build/src/libsoma-client.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-client.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-client.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-client.so"
         OLD_RPATH "/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib::::::::::::::::::::::::::::::::::::::"
         NEW_RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-client.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-bedrock-module.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-bedrock-module.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-bedrock-0.5.2-cgcoh3m53hwgt4apy3z6s2dl5sulhnh2/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-abt-io-0.5.1-djwn4yord5fdfz52nbqau57d2nliteor/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-ssg-0.5.3-uq6meag5d2vcssu4idc66r6hnkg7wbsh/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/users/dewiy/soma-collector/build/src/libsoma-bedrock-module.so.0.1.0"
    "/users/dewiy/soma-collector/build/src/libsoma-bedrock-module.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-bedrock-module.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-bedrock-module.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/users/dewiy/soma-collector/build/src:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-bedrock-0.5.2-cgcoh3m53hwgt4apy3z6s2dl5sulhnh2/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-abt-io-0.5.1-djwn4yord5fdfz52nbqau57d2nliteor/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-ssg-0.5.3-uq6meag5d2vcssu4idc66r6hnkg7wbsh/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:"
           NEW_RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-bedrock-0.5.2-cgcoh3m53hwgt4apy3z6s2dl5sulhnh2/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-abt-io-0.5.1-djwn4yord5fdfz52nbqau57d2nliteor/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-ssg-0.5.3-uq6meag5d2vcssu4idc66r6hnkg7wbsh/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-bedrock-module.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-bedrock-module.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-bedrock-module.so"
         RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-bedrock-0.5.2-cgcoh3m53hwgt4apy3z6s2dl5sulhnh2/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-abt-io-0.5.1-djwn4yord5fdfz52nbqau57d2nliteor/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-ssg-0.5.3-uq6meag5d2vcssu4idc66r6hnkg7wbsh/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/users/dewiy/soma-collector/build/src/libsoma-bedrock-module.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-bedrock-module.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-bedrock-module.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-bedrock-module.so"
         OLD_RPATH "/users/dewiy/soma-collector/build/src:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-bedrock-0.5.2-cgcoh3m53hwgt4apy3z6s2dl5sulhnh2/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-abt-io-0.5.1-djwn4yord5fdfz52nbqau57d2nliteor/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-ssg-0.5.3-uq6meag5d2vcssu4idc66r6hnkg7wbsh/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64:"
         NEW_RPATH "/users/dewiy/soma-collector/build/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-bedrock-0.5.2-cgcoh3m53hwgt4apy3z6s2dl5sulhnh2/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/util-linux-uuid-2.38.1-usdk4g27eri3ysdir7tnqnfxhsqfc4vr/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-abt-io-0.5.1-djwn4yord5fdfz52nbqau57d2nliteor/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/spdlog-1.10.0-yr6ydbphupcz744qx74nfe26shaxlk22/lib64:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-ssg-0.5.3-uq6meag5d2vcssu4idc66r6hnkg7wbsh/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mochi-margo-0.13-i37lm4w3t5jpy7idn4bleuwvtcuirl3v/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/mercury-2.2.0-3et5wmnk4yzu3qpljm3tae3uu66plcge/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/argobots-1.1-lq6taxvvpykmu4iflcnozvz7vrbip3jd/lib:/projappl/project_2006549/spack/opt/spack/linux-rhel8-x86_64_v3/gcc-9.4.0/json-c-0.16-owq5i4v7tufvirroq6txoutz4at4hgrn/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsoma-bedrock-module.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/soma/soma-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/soma/soma-targets.cmake"
         "/users/dewiy/soma-collector/build/src/CMakeFiles/Export/f3579719506aebd0e7ed83cfe8a80a1d/soma-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/soma/soma-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/soma/soma-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/soma" TYPE FILE FILES "/users/dewiy/soma-collector/build/src/CMakeFiles/Export/f3579719506aebd0e7ed83cfe8a80a1d/soma-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/soma" TYPE FILE FILES "/users/dewiy/soma-collector/build/src/CMakeFiles/Export/f3579719506aebd0e7ed83cfe8a80a1d/soma-targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/soma" TYPE FILE FILES
    "/users/dewiy/soma-collector/build/src/soma-config.cmake"
    "/users/dewiy/soma-collector/build/src/soma-config-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/users/dewiy/soma-collector/src/../include/soma" FILES_MATCHING REGEX "/[^/]*\\.hpp$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES
    "/users/dewiy/soma-collector/build/src/soma-server.pc"
    "/users/dewiy/soma-collector/build/src/soma-client.pc"
    "/users/dewiy/soma-collector/build/src/soma-admin.pc"
    )
endif()

