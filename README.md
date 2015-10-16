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
