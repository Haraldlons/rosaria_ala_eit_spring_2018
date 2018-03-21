#include <iostream>
#include <stdio.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
using namespace std;

//this is just a try, and needs to be fixed

//mock function
double navigateToPoint(double fromx, double fromy, double tox, double toy){
        double r;
        r = fromx + fromy;
        return(r);
    }

int main () 
{
    //point positions
    double pos[] = {1, 2};
    
    //current position
    double current_pos[] = {1,0};
    
    /*void callback(const std_msgs::StringConstPtr& str){
        
    }
    ros::Subscriber sub = x.subscribe("", 1, callback);
    */
    
    
    int i = 0;
    //code to navigate to first position
    //like navigate_to_point(pos[i]) and currentpos is tracked
    
    if (current_pos[0] == pos[i] && current_pos[1] == pos[i+1])
    {
        double z;
        z=navigateToPoint (current_pos[0], pos[0], current_pos[1], pos[1]);
        current_pos[0]=pos[i];
        current_pos[1]=pos[i+1];
        cout << "The result is " << z;
        i++;
    }else{
        cout<<"Did not fint the point";
    
    
    /* testing to find difference in distance instead
    
    if (distance=<0.5)
    {
        i++;
        double z;
        z=navigateToPoint (current_pos[0], pos[i], current_pos[1], pos[i+1]);
        i++;
    }else{
        cout<<"Did not fint the point";
    }*/
    
}

 
//