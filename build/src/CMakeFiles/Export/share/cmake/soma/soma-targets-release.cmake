#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "soma-admin" for configuration "Release"
set_property(TARGET soma-admin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(soma-admin PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsoma-admin.so.0.1.0"
  IMPORTED_SONAME_RELEASE "libsoma-admin.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS soma-admin )
list(APPEND _IMPORT_CHECK_FILES_FOR_soma-admin "${_IMPORT_PREFIX}/lib/libsoma-admin.so.0.1.0" )

# Import target "soma-server" for configuration "Release"
set_property(TARGET soma-server APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(soma-server PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsoma-server.so.0.1.0"
  IMPORTED_SONAME_RELEASE "libsoma-server.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS soma-server )
list(APPEND _IMPORT_CHECK_FILES_FOR_soma-server "${_IMPORT_PREFIX}/lib/libsoma-server.so.0.1.0" )

# Import target "soma-client" for configuration "Release"
set_property(TARGET soma-client APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(soma-client PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsoma-client.so.0.1.0"
  IMPORTED_SONAME_RELEASE "libsoma-client.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS soma-client )
list(APPEND _IMPORT_CHECK_FILES_FOR_soma-client "${_IMPORT_PREFIX}/lib/libsoma-client.so.0.1.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
