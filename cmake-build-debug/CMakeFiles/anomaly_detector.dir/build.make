# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\micha\CLionProjects\anomaly_detector

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\micha\CLionProjects\anomaly_detector\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\anomaly_detector.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\anomaly_detector.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\anomaly_detector.dir\flags.make

CMakeFiles\anomaly_detector.dir\anomaly_detection_util.cpp.obj: CMakeFiles\anomaly_detector.dir\flags.make
CMakeFiles\anomaly_detector.dir\anomaly_detection_util.cpp.obj: ..\anomaly_detection_util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\micha\CLionProjects\anomaly_detector\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/anomaly_detector.dir/anomaly_detection_util.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\anomaly_detector.dir\anomaly_detection_util.cpp.obj /FdCMakeFiles\anomaly_detector.dir\ /FS -c C:\Users\micha\CLionProjects\anomaly_detector\anomaly_detection_util.cpp
<<

CMakeFiles\anomaly_detector.dir\anomaly_detection_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anomaly_detector.dir/anomaly_detection_util.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe > CMakeFiles\anomaly_detector.dir\anomaly_detection_util.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\micha\CLionProjects\anomaly_detector\anomaly_detection_util.cpp
<<

CMakeFiles\anomaly_detector.dir\anomaly_detection_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anomaly_detector.dir/anomaly_detection_util.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\anomaly_detector.dir\anomaly_detection_util.cpp.s /c C:\Users\micha\CLionProjects\anomaly_detector\anomaly_detection_util.cpp
<<

CMakeFiles\anomaly_detector.dir\timeseries.cpp.obj: CMakeFiles\anomaly_detector.dir\flags.make
CMakeFiles\anomaly_detector.dir\timeseries.cpp.obj: ..\timeseries.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\micha\CLionProjects\anomaly_detector\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/anomaly_detector.dir/timeseries.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\anomaly_detector.dir\timeseries.cpp.obj /FdCMakeFiles\anomaly_detector.dir\ /FS -c C:\Users\micha\CLionProjects\anomaly_detector\timeseries.cpp
<<

CMakeFiles\anomaly_detector.dir\timeseries.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anomaly_detector.dir/timeseries.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe > CMakeFiles\anomaly_detector.dir\timeseries.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\micha\CLionProjects\anomaly_detector\timeseries.cpp
<<

CMakeFiles\anomaly_detector.dir\timeseries.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anomaly_detector.dir/timeseries.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\anomaly_detector.dir\timeseries.cpp.s /c C:\Users\micha\CLionProjects\anomaly_detector\timeseries.cpp
<<

CMakeFiles\anomaly_detector.dir\main.cpp.obj: CMakeFiles\anomaly_detector.dir\flags.make
CMakeFiles\anomaly_detector.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\micha\CLionProjects\anomaly_detector\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/anomaly_detector.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\anomaly_detector.dir\main.cpp.obj /FdCMakeFiles\anomaly_detector.dir\ /FS -c C:\Users\micha\CLionProjects\anomaly_detector\main.cpp
<<

CMakeFiles\anomaly_detector.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anomaly_detector.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe > CMakeFiles\anomaly_detector.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\micha\CLionProjects\anomaly_detector\main.cpp
<<

CMakeFiles\anomaly_detector.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anomaly_detector.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\anomaly_detector.dir\main.cpp.s /c C:\Users\micha\CLionProjects\anomaly_detector\main.cpp
<<

# Object files for target anomaly_detector
anomaly_detector_OBJECTS = \
"CMakeFiles\anomaly_detector.dir\anomaly_detection_util.cpp.obj" \
"CMakeFiles\anomaly_detector.dir\timeseries.cpp.obj" \
"CMakeFiles\anomaly_detector.dir\main.cpp.obj"

# External object files for target anomaly_detector
anomaly_detector_EXTERNAL_OBJECTS =

anomaly_detector.exe: CMakeFiles\anomaly_detector.dir\anomaly_detection_util.cpp.obj
anomaly_detector.exe: CMakeFiles\anomaly_detector.dir\timeseries.cpp.obj
anomaly_detector.exe: CMakeFiles\anomaly_detector.dir\main.cpp.obj
anomaly_detector.exe: CMakeFiles\anomaly_detector.dir\build.make
anomaly_detector.exe: CMakeFiles\anomaly_detector.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\micha\CLionProjects\anomaly_detector\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable anomaly_detector.exe"
	"C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\anomaly_detector.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\anomaly_detector.dir\objects1.rsp @<<
 /out:anomaly_detector.exe /implib:anomaly_detector.lib /pdb:C:\Users\micha\CLionProjects\anomaly_detector\cmake-build-debug\anomaly_detector.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\anomaly_detector.dir\build: anomaly_detector.exe

.PHONY : CMakeFiles\anomaly_detector.dir\build

CMakeFiles\anomaly_detector.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\anomaly_detector.dir\cmake_clean.cmake
.PHONY : CMakeFiles\anomaly_detector.dir\clean

CMakeFiles\anomaly_detector.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\micha\CLionProjects\anomaly_detector C:\Users\micha\CLionProjects\anomaly_detector C:\Users\micha\CLionProjects\anomaly_detector\cmake-build-debug C:\Users\micha\CLionProjects\anomaly_detector\cmake-build-debug C:\Users\micha\CLionProjects\anomaly_detector\cmake-build-debug\CMakeFiles\anomaly_detector.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\anomaly_detector.dir\depend

