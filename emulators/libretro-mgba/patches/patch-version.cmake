$NetBSD: patch-version.cmake,v 1.1 2018/08/12 14:25:09 nia Exp $

Avoid looking for git to determine the version string.

Correct version string.

--- version.cmake.orig	2018-04-14 20:49:19.000000000 +0000
+++ version.cmake
@@ -3,20 +3,11 @@ if(NOT PROJECT_NAME)
 endif()
 set(LIB_VERSION_MAJOR 0)
 set(LIB_VERSION_MINOR 6)
-set(LIB_VERSION_PATCH 1)
+set(LIB_VERSION_PATCH 3)
 set(LIB_VERSION_ABI 0.6)
 set(LIB_VERSION_STRING ${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR}.${LIB_VERSION_PATCH})
 set(SUMMARY "${PROJECT_NAME} Game Boy Advance Emulator")
 
-find_program(GIT git)
-if(GIT AND NOT SKIP_GIT)
-	execute_process(COMMAND ${GIT} describe --always --abbrev=40 --dirty WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" OUTPUT_VARIABLE GIT_COMMIT ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
-	execute_process(COMMAND ${GIT} describe --always --dirty WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" OUTPUT_VARIABLE GIT_COMMIT_SHORT ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
-	execute_process(COMMAND ${GIT} symbolic-ref --short HEAD WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" OUTPUT_VARIABLE GIT_BRANCH ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
-	execute_process(COMMAND ${GIT} rev-list HEAD --count WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" OUTPUT_VARIABLE GIT_REV ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
-	execute_process(COMMAND ${GIT} describe --tag --exact-match WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" OUTPUT_VARIABLE GIT_TAG ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
-endif()
-
 if(NOT GIT_REV)
 	set(GIT_REV -1)
 endif()
