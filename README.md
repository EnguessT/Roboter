## Roboter

A lightweight, modular **2D robot simulator** built with **C++, SFML**, and **TGUI**.The simulator models a **differential‑drive robot** using real kinematic equations and provides a GUI for manual and trajectory‑based control.

 ![MainWindow](https://github.com/EnguessT/Roboter/blob/main/Docs/screenshots/mainwindow2.png)

## ✨ Key Features
- Differential‑drive kinematic model  
Uses standard robot motion equations to update pose $[x, y, \theta]$ in discrete time.

- Inverse kinematics  
Converts GUI velocity commands $(v,\omega)$ into wheel speeds $(v_l, v_r)$

- Real‑time SFML rendering  
Robot body drawn using custom shapes (including rounded rectangles).

- GUI control panel  
Sliders for linear and angular velocity.
Simulation menu for start/pause/reset.

## 🧠 Core Concepts

- Differential‑Drive Kinematics
- Inverse Kinematics
- Data recording


### 🔧 Build Instructions

#### Requirements
- c++20
- SFML 3.1
- TGUI 1.12
- Cmake >= 3.16

#### build
- Linux
    ``` 
        mkdir build
        cd build
        cmake ..
        ./bin/Linux64/Release/Roboter
    ```

- Windows
    ```

    ```

### 📡 Planned Features
- [] Odometry model
- [] Wheel encoder simulation
- [] Collision detection
- [] Lidar ray casting
- [] Path planning and motion trajectory
- [] Occupancy grid
- [] SLAM
- [] Data plotting

### 📜License
GNU GENERAL PUBLIC LICENSE

### 🤝 Contributions
Pull requests are welcome.
Feel free to open issues for feature requests or bug reports.