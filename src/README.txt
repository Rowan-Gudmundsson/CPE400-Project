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

    A general explanation for the project’s main functionality
    An Entity (see Common.cpp) is in a region in which it has a speed, position, 
    and can move freely (left, right, up, down). An Entity can be either a User 
    (User.cpp) or a UAV (UAV.cpp). A Region (Region.cpp) holds space for 60x60 nodes, 
    in which 1000 are spawned as users and 10 are spawned as UAVs. A Region updates 
    every frame, which will also update all of the entities’ in the region properties.
    The Region is discretized into 10 different regions where each has a value of the 
    coverage level needed in that region. According to those coverage levels, the UAVs 
    are dispatched to the region in which the most users are covered.


///////////////////////////// 5. [RUNNING INSTRUCTIONS] ///////////////////////////////
First BUILD then RUN

BUILD: inside project directory
mkdir build
cd build
cmake ..
make -j4

RUN: inside build directory
./UAVNetwork

***Notes: Program runs infinitely, spam <control + C> to end loop ***
////////////////////////////////////////////////////////////////////////////////////////
