Link for the VM : https://vdi.imt-atlantique.fr/ovirt-engine/web-ui/?locale=fr_FR
# aquarium
C++ project for educational purposes.  
Aquarium software modelizing project.  
The goal of the project is to emphasize use of relevant **Design Patterns** in the software structure.  

---

## Software specifications 
We are simulating an aquarium ecosystem with this software. 
The ecosystem is composed of multiple pieces.

### Creatures
- [x] Drawable 
- [ ] Handles collision
    - [x] Size
    - [ ] Elliptic hitbox
- [x] Can move : 
    - [x] Position
    - [x] Speed 
- [ ] Birth
    - [ ] Can spontaneously clone itself
    - [x] Can be instanciated by the environment
- [ ] Death
    - [x] Can die of age
    - [ ] Can die from collisions
    - [ ] Can be killed by external factors
- [ ] Accessories
    - [x] Can have none or many
    - [ ] Shell
        - [ ] Drawable
        - [x] Changes probability of dying in a collision
    - [ ] Camo
        - [ ] Drawable
        - [x] Lower chance of being detected
    - [x] Fins
        - [ ] Drawable 
        - [x] Swim faster
- [ ] Sensors 
    - [ ] Eyes
        - [x] Detection zone
        - [x] Detection coefficient
        - [ ] Drawable
    - [ ] Ears
        - [x] Detection zone
        - [x] Detection coefficient
        - [ ] Drawable
- [x] Handle detection
- [ ] Handle behaviour
    - [x] Gregarious
    - [x] Fearful
    - [x] Kamikaze
    - [ ] Planning
    - [x] Multiple personalities

### Aquarium
- [ ] Handle simulation steps
- [ ] Returns Aquarium state at every step
- [x] Drawable
- [x] Can create creatures
- [ ] Can kill creatures
- [ ] Handle collisions 
- [ ] Handle detections
- [ ] Models environment
