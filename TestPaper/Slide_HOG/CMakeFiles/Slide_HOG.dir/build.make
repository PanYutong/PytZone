# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/panyutong/PytZone/TestPaper/Slide_HOG

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/panyutong/PytZone/TestPaper/Slide_HOG

# Include any dependencies generated for this target.
include CMakeFiles/Slide_HOG.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Slide_HOG.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Slide_HOG.dir/flags.make

CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.o: CMakeFiles/Slide_HOG.dir/flags.make
CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.o: Slide_HOG.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/panyutong/PytZone/TestPaper/Slide_HOG/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.o -c /home/panyutong/PytZone/TestPaper/Slide_HOG/Slide_HOG.cc

CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/panyutong/PytZone/TestPaper/Slide_HOG/Slide_HOG.cc > CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.i

CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/panyutong/PytZone/TestPaper/Slide_HOG/Slide_HOG.cc -o CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.s

CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.o.requires:
.PHONY : CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.o.requires

CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.o.provides: CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.o.requires
	$(MAKE) -f CMakeFiles/Slide_HOG.dir/build.make CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.o.provides.build
.PHONY : CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.o.provides

CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.o.provides.build: CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.o

# Object files for target Slide_HOG
Slide_HOG_OBJECTS = \
"CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.o"

# External object files for target Slide_HOG
Slide_HOG_EXTERNAL_OBJECTS =

Slide_HOG: CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.o
Slide_HOG: CMakeFiles/Slide_HOG.dir/build.make
Slide_HOG: /usr/local/lib/libopencv_videostab.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_video.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_ts.a
Slide_HOG: /usr/local/lib/libopencv_superres.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_stitching.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_photo.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_ocl.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_objdetect.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_nonfree.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_ml.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_legacy.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_imgproc.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_highgui.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_gpu.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_flann.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_features2d.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_core.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_contrib.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_calib3d.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_nonfree.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_ocl.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_gpu.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_photo.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_objdetect.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_legacy.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_video.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_ml.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_calib3d.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_features2d.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_highgui.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_imgproc.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_flann.so.2.4.12
Slide_HOG: /usr/local/lib/libopencv_core.so.2.4.12
Slide_HOG: CMakeFiles/Slide_HOG.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Slide_HOG"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Slide_HOG.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Slide_HOG.dir/build: Slide_HOG
.PHONY : CMakeFiles/Slide_HOG.dir/build

CMakeFiles/Slide_HOG.dir/requires: CMakeFiles/Slide_HOG.dir/Slide_HOG.cc.o.requires
.PHONY : CMakeFiles/Slide_HOG.dir/requires

CMakeFiles/Slide_HOG.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Slide_HOG.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Slide_HOG.dir/clean

CMakeFiles/Slide_HOG.dir/depend:
	cd /home/panyutong/PytZone/TestPaper/Slide_HOG && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/panyutong/PytZone/TestPaper/Slide_HOG /home/panyutong/PytZone/TestPaper/Slide_HOG /home/panyutong/PytZone/TestPaper/Slide_HOG /home/panyutong/PytZone/TestPaper/Slide_HOG /home/panyutong/PytZone/TestPaper/Slide_HOG/CMakeFiles/Slide_HOG.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Slide_HOG.dir/depend

