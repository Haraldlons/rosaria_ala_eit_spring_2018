1) Permission to open USB-port 
chmod 777 /dev/ttyUSB0
2) To start robot
2.1) roscore
2.2) rosrun rosaria RosAria
2.3) rosrun rosaria_client motor_controller

3) TODO:- Make rosparams for tunable parameters
	- Make PI-controller for speed
	

OR launch robot by doing following:
1) sudo chmod 777 /dev/ttyUSB0
2) roslaunch rosaria longitudinal_controller.launch


Launch Aria stuff directly
1)
```
cd /usr/local/Aria
```

# Run tests
```
cd ~/catkin_ws
catkin_make run_tests_rosaria_client
```

# How to launch arduino stuff
1: 
```
chmod 777 /dev/ttyACM0
rosrun rosserial_python serial_node.py _baud:=57600 _port:=/dev/ttyACM0
```

# How to run tests
## run helper_functions_test.cpp
```
cd ~/catkin_ws
catkin_make run_tests_rosaria_client
```
## run yaw_controller_test.test
```
