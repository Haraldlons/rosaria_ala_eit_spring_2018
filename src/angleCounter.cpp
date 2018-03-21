#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

double cal_angle ( double current_x , double current_y , double tar_x , double tar_y )
{
	return atan2(tar_y - current_y, tar_x - current_x);
}

int main()
{
    double x1 = 2.0;
	double y1 = -1;
	
	double x2 = 3.1;
	double y2 = 4.0;
    
    printf("%lf \n", cal_angle(x2 ,y2 , x1 , y1));
    
    double x3 = 0;
	double y3 = 0;
	
	double x4 = 0;
	double y4 = 0;
    
    printf("%lf \n", cal_angle(x3 ,y3 , x4 , y4));

    return 0;
}