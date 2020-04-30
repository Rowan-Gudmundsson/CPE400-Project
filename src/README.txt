//////////////////////////////////// README ////////////////////////////////////////
Author = Michael DesRoches
         Rowan Gundmundsson
         Emily Godby
Date = April 30, 2020
Project = UAV network to maximize throughput
Class = CPE 400 - Networks

##Table of Contents
1. [Project Topic]
2. [Assumption]
3. [Requirements/Constraints]
4. [General Framework]
5. [Running Instructions]

1. Project Topic
    
    Providing wireless coverage to ground mobile users in a region with a 
    self-reconfigurable UAV network to maximize throughput. Initial users’ 
    location should be unknown and the user mobility should be unpredictable.

2. Assumption
    
    A fixed cellular tower at the boundary of the region.

3. Requirements/Constraints

     Each UAV has a fixed serving capacity and limited battery power, and 
     some subareas in the region will be highly crowded (more than what a 
     single UAV can serve.) at unpredictable time durations.

4. General Framework 


///////////////////////////// 5. [RUNNING INSTRUCTIONS] ///////////////////////////////
First BUILD then RUN

BUILD: inside project directory
mkdir build
cd build
cmake ..
make -j4

RUN: inside build directory
./UAVNetwork

***Notes: Program pauses on each iteration, just press any key to inspect next iteration***
////////////////////////////////////////////////////////////////////////////////////////
