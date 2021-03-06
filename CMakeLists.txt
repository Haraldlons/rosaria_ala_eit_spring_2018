cmake_minimum_required(VERSION 2.8.3)
project(rosaria_client)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  rostest
  std_msgs
  geometry_msgs
  nav_msgs
  rosaria
  tf
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependencies might have been
##     pulled in transitively but can be declared for certainty nonetheless:
##     * add a build_depend tag for "message_generation"
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES turtle_test
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
# include_directories(
#   ${catkin_INCLUDE_DIRS}
# )

# Harald think the following should be correct
include_directories(
  include
    ${catkin_INCLUDE_DIRS}
)
link_directories(${catkin_LIBRARY_DIRS})

## Declare a cpp library
# add_library(turtle_test
#   src/${PROJECT_NAME}/turtle_test.cpp
# )

## Declare a cpp executable
add_executable(go_three_second src/go_three_second.cpp)
add_executable(spin_counterclockwise src/spin_counterclockwise.cpp)
add_executable(spin_clockwise src/spin_clockwise.cpp)
add_executable(teleop src/teleop.cpp)
add_executable(print_state src/print_state.cpp)
add_executable(interface src/interface.cpp)
add_executable(enable_motors src/enable_motors.cpp)

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(turtle_test_node turtle_test_generate_messages_cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(go_three_second 
   ${catkin_LIBRARIES}
)

target_link_libraries(spin_counterclockwise 
   ${catkin_LIBRARIES}
)

target_link_libraries(spin_clockwise 
   ${catkin_LIBRARIES}
)

target_link_libraries(teleop 
   ${catkin_LIBRARIES}
)

target_link_libraries(print_state
  ${catkin_LIBRARIES}
)

target_link_libraries(interface
  ${catkin_LIBRARIES}
  )

target_link_libraries(enable_motors
  ${catkin_LIBRARIES}
  )

# Our own developed yaw_controller
add_executable(yaw_controller src/yaw_controller.cpp)
target_link_libraries(yaw_controller ${catkin_LIBRARIES})

# Our own developed longitudinal controller
add_executable(longitudinal_controller src/longitudinal_controller.cpp)
target_link_libraries(longitudinal_controller ${catkin_LIBRARIES})

# Our own developed motor controller
add_executable(motor_controller src/motor_controller.cpp)
target_link_libraries(motor_controller ${catkin_LIBRARIES})

# Our own developed master controller
add_executable(master_controller src/master_controller.cpp)
target_link_libraries(master_controller ${catkin_LIBRARIES})

# Our own developed light logger
add_executable(light_logger src/light_logger.cpp)
target_link_libraries(light_logger ${catkin_LIBRARIES})
add_dependencies(light_logger ${catkin_EXPORTED_TARGETS})


#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS turtle_test turtle_test_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
catkin_add_gtest(ustest test/helper_functions_test.cpp)
# if(TARGET utest)
#   target_link_libraries(utest ${PROJECT_NAME})
# endif() 

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)

# add_rostest_gtest(click_transformer_test
#   test/click_transformer.test
#   test/click_transformer_test.cpp
# )
# target_link_libraries(click_transformer_test ${catkin_LIBRARIES})

add_rostest_gtest(yaw_controller_test
  test/yaw_controller_test.test
  test/yaw_controller_test.cpp
)
target_link_libraries(yaw_controller_test ${catkin_LIBRARIES})
add_dependencies(yaw_controller_test $(catkin_EXPORTED_TARGETS))

#############
# QTCREATOR #
#############
FILE(GLOB_RECURSE LibFiles "include/*")
add_custom_target(headers SOURCES ${LibFiles})