#project( SCWS )
#cmake_minimum_required( VERSION 2.6 )

# set compile argument
set( CMAKE_CXX_FLAGS "-g -O2 -s -pipe -fomit-frame-pointer -Wunused -Wall" )
add_definitions( )

# set directory
set( COMMONLIB_DIR ../../commonlib/ )
IF ( CMAKE_SIZEOF_VOID_P  EQUAL 8 )
	set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${COMMONLIB_DIR}/lib64 )
ELSE()
	set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${COMMONLIB_DIR}/lib )
ENDIF()
set( CMAKE_INSTALL_PREFIX ${COMMONLIB_DIR} )

# set liberary link argument
set( LIB_NAME scws)
aux_source_directory( . SCWS_DIR )
add_library( ${LIB_NAME} SHARED ${SCWS_DIR} )

#set_target_properties( ${LIB_NAME} PROPERTIES VERSION 1.0 SOVERSION 1 )

#INSTALL ( FILES scws.h rule.h xdict.h scws_version.h xtree.h pool.h
#    DESTINATION include/scws )
