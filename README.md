# aquarium
C++ project for educational purposes.  
Aquarium software modelizing project.  
The goal of the project is to emphasize use of relevant **Design Patterns** in the software structure.  

---

## Software specifications 
We are simulating an aquarium ecosystem with this software. 
The ecosystem is composed of multiple pieces.

### Creatures
- [ ] Drawable 
- [ ] Handles collision
    - [ ] Size
    - [ ] Elliptic hitbox
- [ ] Can move : 
    - [ ] Position
    - [ ] Speed 
- [ ] Birth
    - [ ] Can spontaneously clone itself
    - [ ] Can be instanciated by the environment
- [ ] Death
    - [ ] Can die of age
    - [ ] Can die from collisions
    - [ ] Can be killed by external factors
- [ ] Accessories
    - [ ] Can have none or many
    - [ ] Shell
        - [ ] Drawable
        - [ ] Changes probability of dying in a collision
    - [ ] Camo
        - [ ] Drawable
        - [ ] Lower chance of being detected
    - [ ] Fins
        - [ ] Drawable 
        - [ ] Swim faster
- [ ] Sensors 
    - [ ] Eyes
        - [ ] Detection zone
        - [ ] Detection coefficient
        - [ ] Drawable
    - [ ] Ears
        - [ ] Detection zone
        - [ ] Detection coefficient
        - [ ] Drawable
- [ ] Handle detection
- [ ] Handle behaviour
    - [ ] Gregarious
    - [ ] Fearful
    - [ ] Kamikaze
    - [ ] Planning
    - [ ] Multiple personalities

### Aquarium
- [ ] Handle simulation steps
- [ ] Returns Aquarium state at every step
- [ ] Drawable
- [ ] Can create creatures
- [ ] Can kill creatures
- [ ] Handle collisions 
- [ ] Handle detections
- [ ] Models environment
