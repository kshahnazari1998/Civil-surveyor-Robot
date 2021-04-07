# Civil Engineering Surveyor Robot (1st Place Mechatronic Project in Tehran State) - 2013

This Repo Showcases the Algorithm used for the Civil Engineering Robot. 

### Note: Because the Robot is needed to reproduce the things it did, the code is only added to show the unique algorithms used for the robot. For readability, the code has been separated into different header files but has not been tested after the separation. I wrote the code when I was 15 years old so the documentation isn't top notch. Feel free to contact me if you had questions about any parts of the code.
---
## The Project

The Video below better illustrates the project, and I highly recommend you watch the Video. The Readme will only give a summary of the project.

Drawing the lines to build walls on is a considerable challenge in construction, especially in tall-rise buildings. The acceptable margin of error is considered to be under 2 to 3 centimetres. To draw these precise lines, engineers need to put in about two days for each story of the buildings meaning that this long process must be repeated a lot of times and, therefore, it would take a lot of time and costs for the project managers to finish this process.

This is where the Robot comes to play. By specifying a few benchmarks in each story and their X and Y position, the Robot could quickly detect its position and find the positions it needs to draw the lines on. Finding the position of the benchmarks is pretty easy because a few places in the building are already apparent such as the position of the columns and the corners of the building. By using the robot the time required was cut from two days to an average of 3 hours for each story.

The project won the 1st place in the State of Tehran in the Mechatronics section for people aged under 18. So this project was done when I was 15 years old. The strongest point of the project was that it was one of the first projects that used the combination of laser and encoders to pinpoint the location.

The process was made up of few different parts
- Calculating the distance to each benchmark
- Based on the distances using triangulation finding the position of the robot
- Moving to the point that the point must be printed and tracking the change in position with Encoders
- Validating if the new position we are in is accurate by recalculating position
- If not do the process again else try to fix the position until we are under the allowed margin of error.

Each one of this parts was a huge challenge especially the 1st and 2nd steps were alot of inovations were needed. Therefore each part will be broken down.

## Calculating the distance to each benchmark: 
Different methods could be used to calculate distance. Using radiowaves, is one of those methods. But the problem is that low cost equipment don't have the accuracy needed for the project and the ones with the accuracy needed had a cost of over 50000$'s which was not affordable and also increases the cost of making the robot.
To Address this a new method was used. Some 
