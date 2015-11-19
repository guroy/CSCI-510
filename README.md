CSCI-510 - Intro to Computer Graphics
--------

##### Rochester Institute of Technology
SFML & OpenGL Practical Homeworks developed on C++ using Visual Studio 2013 IDE.

* **Course Title:** CSCI-510 Introduction to Computer Graphics
* **Instructor:** Reynold Bailey
* **Year:** 2015
* **Contributors:**
  * <a href="https://github.com/guroy">Guillaume Roy</a>, Computer Science and Software Engineering student - INSA Rennes

Labs
----
##### <a href="https://github.com/guroy/CSCI-510/tree/master/Lab%201%20-%20Line%20Drawing">Lab 1: Line Drawing</a>
* Implementation of the Midpoint Line Drawing algorithm. Providing source code of a drawLine() method whose prototype is:
```void drawLine( int x0, int y0, int x1, int y1, simpleCanvas &C );```

![alt_tag](http://nodim.fr/host/course/cg/lab1.png)

##### <a href="https://github.com/guroy/CSCI-510/tree/master/Lab%202%20-%20Polygon%20Fill">Lab 2: Polygon Fill</a>
* Implementation of the scanline polygon fill algorithm. Providing source code of a drawPolygon() method whose prototype is:
```void drawPolygon( int n, int x[], int y[], simpleCanvas &C );```

![alt_tag](http://nodim.fr/host/course/cg/lab2.png)

##### <a href="https://github.com/guroy/CSCI-510/tree/master/Lab%203%20-%20Clipping">Lab 3: Clipping</a>
* Implementation of the Sutherland-Hodgman Polygon Clipper algorithm. Providing source code of a clipPolygon() method whose prototype is:
```int clipPolygon( int in, const float inx[], const float iny[], float outx[], float outy[], float x0, float y0, float x1, float y1 );```

![alt_tag](http://nodim.fr/host/course/cg/lab3.png)

##### <a href="https://github.com/guroy/CSCI-510/tree/master/Project%201%20Midterm">Project 1 Midterm</a>
* Implementation of the complete 2D pipeline as presented in class using routines written for previous assignments. This project is in lieu of a traditional midterm exam. 

![alt_tag](http://nodim.fr/host/course/cg/midterm.gif)

##### <a href="https://github.com/guroy/CSCI-510/tree/master/Hello,%20OpenGL!">Hello, OpenGL!</a>
* Just a test program to setup OpenGL on Visual Studio. 

![alt_tag](http://nodim.fr/host/course/cg/hello.png)

##### <a href="https://github.com/guroy/CSCI-510/tree/master/Lab%204%20-%20Tesselation">Lab 4 - Tessellation</a>
*  Creating tessellations of four basic shapes. Supplying implementations for four functions: ```makeCube()```, ```makeCylinder()```, ```makeCone()```, and ```makeSphere()```. 

![alt_tag](http://nodim.fr/host/course/cg/lab4.gif)

##### <a href="https://github.com/guroy/CSCI-510/tree/master/Lab%205%20-%203D%20Transformations">Lab 5 - 3D Transformations</a>
*  In this assignment, we work with OpenGL and GLSL to implement 3D transformations; more specifically, ```Model transformation``` Take vertices from model to world coordinates ```View transformation``` Take vertices from world to camera coordinates ```Projection transformation``` Take vertices from camera to clip coordinates.

![alt_tag](http://nodim.fr/host/course/cg/lab5.gif)

##### <a href="https://github.com/guroy/CSCI-510/tree/master/Lab%206%20-%20Tesselation">Lab 6 - Tessellation</a>
*  In this assignment, we will work with OpenGL and GLSL to implement lighting, materials, and shading. We will be producing flat shaded, Gouraud shaded, and Phong shaded shapes using the Phong Illumination Model. 

![alt_tag](http://nodim.fr/host/course/cg/lab6.gif)
