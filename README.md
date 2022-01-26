# Loop-Closure-Detection-with-DBoW2
Loop closure detection with DBoW2 using mez's monocular visual Odometry C++.

## Loop Closure Detection with ORB
Loop closure detection with [DBoW2](https://github.com/dorian3d/DBoW2) using [mez's monocular VO](https://github.com/mez/monocular-visual-odometry).<br>
The [original author](https://github.com/mez/monocular-visual-odometry) used the FAST algorithm, but I modified the code using ORB and DBoW2.<br><br>
Visual vocabulary is not generated simultaneously with mapping, and visual vocabulary is created first in the modified code. After that, the similarity between the images is estimated, and loop detection can be checked while mapping is performed.<br><br>
[Lee-JaeWon's GitBlog about Loop Detection and Bag of Words](https://lee-jaewon.github.io/slam/Loop_Detection/)<br>

### Code Overview
`main.cpp` : Main code containing visual odometry and loop detection processes.<br>
`using_DBoW.h` : Functions with DBoW2

### Build and Excute
1. git clone this repo
2. `mkdir build && cd build`<br>
3. `cmake ..`<br>
4. `make`<br>
5. `./mono_vo viz`<br>
