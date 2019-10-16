// Submitted by: Justin Lee, Annshine Wu
// This program uses recursive concepts to display fractal images. The two fractals that are drawn in this program are the Sierpinski Triangle and a tree.

#include "fractals.h"
#include <math.h>
#include "error.h"
using namespace std;

void drawTreeHelper(GWindow&, GPoint, double, int, double);

// drawSierpinskiTriangle takes the coordinates of the top left corner
// it draws three triangles from it based on the size and order
// base case: order = 1, simply draw the three triangles
// recursive case: order > 1, call the recursive functions three more times with updated coordinates and one less order
void drawSierpinskiTriangle(GWindow& gw, double x, double y, double size, int order) {
    double height = sqrt(3)/2 * size;
    if(order == 1){
        gw.drawLine(x , y, x + size, y );
        gw.drawLine(x + size, y, x + (size/2), y + height);
        gw.drawLine(x + (size/2), y + height , x, y);
    } else if(order > 1){
        drawSierpinskiTriangle(gw, x , y, size/2, order-1);
        drawSierpinskiTriangle(gw, x + (size/2), y , size/2, order-1);
        drawSierpinskiTriangle(gw, x + (size/4), y + height/2, size/2, order-1);
    } else if (order < 0){
        throw "Order should not be negative";
    }
}

//This function recursively calls itself to draw the branches of the tree. There are five parameters, the first
//being a reference to the graphics window, the second being a point representing the endpoint of each branch. The
//third parameter is the length of each branch, and the fourth parameter is the order of the tree. The last parameter
//is a variable that offsets the angle of th polar lines being drawn, so the branches are angled correctly.
//The recursive case is within a for loop that loops through the angles 45 to 135. The angle in each iteration is
//changed by an offset. The function only runs if the function is greater than 1, meaning the base case is if the order is 0,
//the function returns.
void drawTreeHelper(GWindow& gw, GPoint point, double length, int order, double initial){
    if(order >= 1){
        if(order == 1){
            gw.setColor("#2e8b57");
        }
        int counter = 3;
        for(int i = 45; i <= 135; i+=15){
            GPoint point2 = gw.drawPolarLine(point, length, i - initial);
            drawTreeHelper(gw, point2, length/2, order - 1, initial + (15 * counter));
            counter--;
        }
        gw.setColor("#8b7765");
    }
}

//This function calls the recursive helper function. It first checks if the inputted information is valid, and throws an exception if
//the x, y, size, or order is less than 0. The function sets up the recursion by setting the appropriate colors and drawing the
//the trunk of the tree. It then gets the endpoint of the trunk, and passes it to the helper recursive function which draws the branches.
void drawTree(GWindow& gw, double x, double y, double size, int order) {
    if(x < 0 || y < 0 || size < 0 || order < 0){
        throw "illegal parameter";
    }
    if(order == 1){
        gw.setColor("#2e8b57");
    } else{
        gw.setColor("#8b7765");
    }
    gw.drawLine(x + (size/2), y + size, x + (size/2), y + (size/2));
    GPoint point(x + (size/2), y + (size/2));
    drawTreeHelper(gw, point, size/4, order - 1, 0);
}
