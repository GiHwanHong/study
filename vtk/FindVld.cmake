## 
## Try to find Visual Leak Debugger library (VLD)
## See http://www.codeproject.com/tools/visualleakdetector.asp for details
##
## Once run this will define: 
## 
## VLD_FOUND
## VLD_INCLUDE_DIR 
##
## Jan Woetzel 08/2005
## www.mip.informatik.uni-kiel.de/~jw
##
## tested with vdl-1.0 on Windows with Visual Studio .Net 2003
##
## --------------------------------
set(VLD_FOUND FALSE)

if(MSVC)
  if(CMAKE_CL_64)
	set(VLD_LIB_SUBDIR "lib/Win64")
  else(CMAKE_CL_64)
	set(VLD_LIB_SUBDIR "lib/Win32")
  endif(CMAKE_CL_64)

  set(VLD_INSTALL_DIRS
	$ENV{VLD_DIR}
	"$ENV{ProgramFiles}/Visual Leak Detector"
	"$ENV{ProgramW6432}/Visual Leak Detector"
	c:/dev/sdk/vld
	# more candidate...
	)
  
  find_path(VLD_INCLUDE_DIR # look for the header file
	NAMES vld.h
	HINTS ${VLD_INSTALL_DIRS}
	PATH_SUFFIXES include
	)
  mark_as_advanced(VLD_INCLUDE_DIR)
  # message("VLD_INCLUDE_DIR = ${VLD_INCLUDE_DIR}")

  find_library(VLD_LIBRARY # look for the library
	NAMES vld.lib
	HINTS ${VLD_INSTALL_DIRS}
	PATH_SUFFIXES ${VLD_LIB_SUBDIR}
	)
  mark_as_advanced(VLD_LIBRARY)

  # handle the QUIETLY and REQUIRED arguments and set VLD_FOUND to TRUE if 
  # all listed variables are TRUE
  include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
  find_package_handle_standard_args(VLD DEFAULT_MSG VLD_LIBRARY VLD_INCLUDE_DIR)
  # message("vld include dirs=${VLD_INCLUDE_DIRS}")

  if(VLD_FOUND)
	set(VLD_LIBRARIES ${VLD_LIBRARY})
	set(VLD_INCLUDE_DIRS ${VLD_INCLUDE_DIR})
  endif(VLD_FOUND)
endif(MSVC)