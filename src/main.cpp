#include <iostream>
#include <chrono>
#include "../include/differential_drive.hpp"
#include "../include/simulator.hpp"



int main() {

    // Created a simulator object
    Simulator sim;

    // staart the simulation
    sim.bus().subscribe<messages::SimulationStarted>([] (const auto&) {
        std::cout << "Simulation started\n";
    });

    // Create a robot
    std::string name {"Rover"};
    sim.addRobot(std::make_unique<DifferentialDriveRobot>(name, 0.3, sim.bus()));

    sim.start(0.1); // 10hz

    sim.bus().subscribe<messages::SimulationTick>([](const messages::SimulationTick& t) {
        std::cout << "Time: " << t.time << '\n';
    });
    
    sim.bus().subscribe<messages::VelocityCommand>([](const messages::VelocityCommand& v) {
        std::cout << v.target << " Velocity: " 
        << "left : " << v.left 
        <<" right: " << v.right << '\n';
    });
        
    sim.bus().subscribe<messages::Odometry>([](const messages::Odometry& o) {
            std::cout << o.name << "ODOM: " 
            << "x = " << o.x 
            << "y = " << o.y 
            << "theta = " << o.theta << '\n';
    });

    for (int i = 0; i < 10 ; i++) {
        //sim.update(0.1);
        sim.printAll();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    

    //publish velocity commands
    //sim.bus().publish(messages::VelocityCommand{"Rover", 0.5, 0.3});

    // stop the simulation
    sim.stop();
    sim.bus().flush();
    

    return 0;
}