# Civil Engineering Surveyor Robot (1st Place Mechatronic Project in Tehran State) - 2013

<p align="center">
<img src="/Robot_pictures/Robot.png" width="450" height="300" alt="robot image">
</p>

This Repo Showcases the Algorithm used for the Civil Engineering Robot. 

### Note: Because the Robot is needed to reproduce the things it did, the code is only added to show the unique algorithms used for the Robot. The code has been separated into different header files for readability but has not been tested after the separation. I wrote the code when I was 15 years old, so the documentation isn't top-notch. Feel free to contact me if you had questions about any parts of the code.
---
## The Project

The video below better illustrates the project, and I highly recommend you watch the video. The Readme will only give a summary of the project.

Drawing the lines to build walls on is a considerable challenge in construction, especially in tall-rise buildings. The acceptable margin of error is considered to be under 2 to 3 centimetres. To draw these precise lines, engineers need to put in about two days for each story of the buildings meaning that this long process must be repeated a lot of times and, therefore, it would take a lot of time and costs for the project managers to finish this process.

This is where the Robot comes to play. By specifying a few benchmarks in each story and their X and Y position, the Robot could quickly detect its position and find the positions it needs to draw the lines on. Finding the benchmarks' position is pretty easy because a few places in the building are already apparent such as the position of the columns and the corners of the building. Using the Robot the time required was cut from two days to an average of 3 hours for each story.

The project won 1st place in the State of Tehran in the Mechatronics section for people aged under 18. So this project was done when I was 15 years old. The project's most vital point was that it was one of the first projects that used the combination of laser and encoders to pinpoint the location.

The process was made up of few different parts
- Calculating the distance to each benchmark
- Based on the distances, use triangulation to find the position of the Robot
- Moving to the point that the point must be printed and tracking the change in position with Encoders
- Validating if the new position we are in is accurate by recalculating the position
- If not, do the process again, else try to fix the position until we are under the allowed margin of error.

Each of these parts was a huge challenge, especially the 1st and 2nd steps, where a lot of innovations were needed. Therefore each piece will be broken down.

### Calculating the distance to each benchmark: 
Different methods could be used to calculate distance. Using radio waves is one of those methods. But the problem is that low-cost equipment doesn't have the accuracy needed for the project. The ones with the necessary accuracy had a cost of over 50000$'s which was not affordable and also increased the cost of making the Robot.
To address this, a new method was used. Some Barcode signs were installed on the benchmarks. With a camera and laser, we detected those benchmarks with a camera and then used a laser to distance the benchmark. The code for this section is in Laser and Machine Vision header files. A picture of an example benchmark is shown below:

<p align="center">
<img src="/Robot_pictures/Benchmark.JPG" width="450" height="550" alt="benchmark picture">
</p>

### Calculating position with triangulation
We could use the distances to the benchmarks to calculate the position. This is the same method GPS systems used, but we would do it in 2 dimensions this time. We can't use some exact formulas that give us the position because the distances we have contain some errors; therefore, we iterate through all the possible positions that the Robot could have and choose the one that has the least error. The code for this section is in the triangulation header file.

### Rest of the parts.
The rest of the code is to interact with the Robot, both reading from the encoders and turning the motors on and off, calculate the necessary moves to go to the positions and checking the positions which could be seen in the rest of the header files. A interface of working with the robot is shown below:
---
## Video Links of the robot working
---
## Extra material

At the root of the project, a photos folder includes photos of the Robot in different stages and angles. Also, a PDF of the robot logic is added to the root. 
---
## Contact Me
If you have any questions about the project or want to discuss any subject, you could add me on LinkedIn or at kshahnazari@gmail.com.
