cmake_minimum_required(VERSION 3.16)
project(xrealOneDeviceKit C)

set(CMAKE_C_STANDARD 17)

if(NOT DEFINED XRDEVICEKIT_ROOT)
	set(XRDEVICEKIT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../xrDeviceKit")
endif()

if(NOT TARGET xrDeviceKit)
	add_subdirectory("${XRDEVICEKIT_ROOT}" xrDeviceKit)
endif()

set(XOD_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/modules/xreal_one_driver")
set(XOD_HAVE_HEADER OFF)
if(EXISTS "${XOD_ROOT}/include/xreal_one_driver.h")
	set(XOD_HAVE_HEADER ON)
endif()

if(NOT XOD_HAVE_HEADER)
	message(WARNING "xreal_one_driver submodule not available at ${XOD_ROOT}; skipping xrealOneDeviceKit")
	return()
endif()

add_library(
		xrealOneDeviceKit
		src/imu_protocol_xo.c
		src/xreal_one_devices.c
)

target_compile_options(xrealOneDeviceKit PRIVATE -fPIC)

target_include_directories(xrealOneDeviceKit
		BEFORE PUBLIC include
)

target_include_directories(xrealOneDeviceKit
		SYSTEM BEFORE PRIVATE "${XOD_ROOT}/include"
)

target_link_libraries(xrealOneDeviceKit
		PUBLIC xrDeviceKit
)

add_subdirectory("${XOD_ROOT}" "${CMAKE_CURRENT_BINARY_DIR}/xreal_one_driver")
target_link_libraries(xrealOneDeviceKit PRIVATE xreal_one_driver)

set(XREALONEDEVICEKIT_INCLUDE_DIR
		"${CMAKE_CURRENT_SOURCE_DIR}/include"
		"${XRDEVICEKIT_INCLUDE_DIR}"
		PARENT_SCOPE
)
set(XREALONEDEVICEKIT_LIBRARY xrealOneDeviceKit PARENT_SCOPE)
