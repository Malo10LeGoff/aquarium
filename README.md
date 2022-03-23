Link for the VM : https://vdi.imt-atlantique.fr/ovirt-engine/web-ui/?locale=fr_FR
# aquarium
C++ project for educational purposes.  
Aquarium software modelizing project.  
The goal of the project is to emphasize use of relevant **Design Patterns** in the software structure.  

---

# How to run the project :
- sudo apt-get install cmake
- mkdir build
- cd build
- cmake ..
- make
- ./src/main

## Software specifications 
We are simulating an aquarium ecosystem with this software. 
The ecosystem is composed of multiple pieces.

### Creatures
- [x] Drawable 
- [x] Handles handleCreatureCollision
    - [x] Size
    - [ ] Elliptic hitbox
- [x] Can move : 
    - [x] Position
    - [x] Speed 
- [ ] Birth
    - [ ] Can spontaneously clone itself
    - [x] Can be instanciated by the environment
- [x] Death
    - [x] Can die of age
    - [x] Can die from collisions
    - [x] Can be killed by external factors
- [x] Accessories
    - [x] Can have none or many
    - [x] Shell
        - [x] Drawable
        - [x] Changes probability of dying in a handleCreatureCollision
    - [x] Camo
        - [x] Drawable
        - [x] Lower chance of being detected
    - [x] Fins
        - [x] Drawable 
        - [x] Swim faster
- [x] Sensors 
    - [x] Eyes
        - [x] Detection zone
        - [x] Detection coefficient
        - [x] Drawable
    - [x] Ears
        - [x] Detection zone
        - [x] Detection coefficient
        - [x] Drawable
- [x] Handle detection
- [x] Handle behaviour
    - [x] Gregarious
    - [x] Fearful
    - [x] Kamikaze
    - [ ] Planning
    - [x] Multiple personalities

### Aquarium
- [x] Handle simulation steps
- [x] Returns Aquarium state at every step
- [x] Drawable
- [x] Can create creatures
- [x] Can kill creatures
- [x] Handle collisions 
- [x] Handle detections
- [x] Models environment
