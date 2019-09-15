project(RemotefNIRS)
set(CMAKE_CXX_STANDARD 14)
cmake_minimum_required(VERSION 3.14)
## Find Packages
find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)
##############
# Include Directories
include_directories($(PROJECT_SOURCE_DIR)/include/cmos_camera)
include_directories($(PROJECT_SOURCE_DIR)/include/constants)
include_directories($(PROJECT_SOURCE_DIR)/include/structure_camera)
include_directories($(PROJECT_SOURCE_DIR)/include/beer_lamberts_law)
###############
# Include CPP Source Files

##########
#### Include Subdirectories
include(test/CMakeLists.txt)
############
# Add Executables
add_executable(remote_fnirs main.cpp
        src/structure_camera/get_depth_frame_Structure.cpp
        src/beer_lamberts_law/calculate_baseline.cpp
        src/beer_lamberts_law/get_hbb_hbo.cpp
        )
target_link_libraries(remote_fnirs ${PCL_LIBRARIES} Structure)
