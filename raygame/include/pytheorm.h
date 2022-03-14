#include <math.h>

float pythTheorm(float firstLeg, float secondLeg) {

    // get first leg of triangle from cmd line arguments
    float a = firstLeg; 

    // get second leg of triangle
    float b = secondLeg; 

    // find C
    float c = sqrt((pow(a, 2) + pow(b, 2))); 

    return c;
}