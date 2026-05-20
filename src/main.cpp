#include <iostream>
#include <chrono>
#include <filesystem>
#include "../include/differential_drive.hpp"
#include "../include/simulator.hpp"
#include "../include/logger.hpp"
#include "../include/recorder.hpp"



int main() {

    // Created a simulator object
    Simulator sim;

    // create logger and recorder
    
    std::string log_file{"../../../log/record.log"};
    Recorder rec(sim.bus(), log_file);
    Logger logger(sim.bus());

    // staart the simulation
    sim.bus().subscribe<messages::SimulationStarted>([] (const auto&) {
        std::cout << "Simulation started\n";
    });

    // Create a robot
    std::string name {"Rover"};
    sim.addRobot(std::make_unique<DifferentialDriveRobot>(name, 0.3, sim.bus()));

    sim.start(0.1); // 10hz

    //publish velocity commands
    sim.bus().publish(messages::VelocityCommand{"Rover", 0.5, 0.3});
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // stop the simulation
    sim.stop();
    sim.bus().flush();

    auto& hist = sim.bus().getHistory<messages::Odometry>();
    for(auto& h: hist) {
        std::cout << "hist Odometry: " << std::any_cast<messages::Odometry>(h) << '\n';
    }
    

    return 0;
}