# Loop-Closure-Detection-with-DBoW2
Loop closure detection with DBoW2 using mez's monocular visual Odometry C++.

## Loop Closure Detection with ORB
Loop closure detection with [DBoW2](https://github.com/dorian3d/DBoW2) using [mez's monocular VO](https://github.com/mez/monocular-visual-odometry).<br>
The [original author](https://github.com/mez/monocular-visual-odometry) used the FAST algorithm, but I modified the code using ORB and DBoW2.<br><br>
Visual vocabulary is not generated simultaneously with mapping, and visual vocabulary is created first in the modified code. After that, the similarity between the images is estimated, and loop detection can be checked while mapping is performed.
