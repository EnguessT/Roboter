/**
 * @file id_generator.hpp
 * @brief a class to automatically generally id 
 * for each created robot
 * ---
 * @author EnguessT
 * @date June 30, 2026
 */

 #include <atomic>

 class IDGenerator {
    static std::size_t next() {
        static std::atomic<std::size_t> counter{0};
        return counter++;
    }
 };