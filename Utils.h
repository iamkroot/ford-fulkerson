#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <vector>

/**
 * @brief Read graph information from a csv file
 * @param path Path to file containing graph info
 * @return Edge List
 */
std::vector<std::pair<int, int>> readEdgeList(const std::string &path);

/**
 * @brief Stopwatch to measure algorithm runtimes
 */
template<typename TimeT = std::chrono::microseconds,
        typename ClockT = std::chrono::high_resolution_clock,
        typename DurationT = uint64_t>
class Stopwatch {
private:
    std::chrono::time_point<ClockT> _start, _end;
public:
    /**
     * @brief Initialize Stopwatch
     */
    Stopwatch() {
        start();
    }

    /**
     * @brief Start Timer
     */
    void start() {
        _start = _end = ClockT::now();
    }
    
    /**
     * @brief Stop Timer
     * @return Stop Time
     */
    DurationT stop() {
        _end = ClockT::now();
        return elapsed();
    }

    /**
     * @brief Count Elapsed Time
     * @return Elapsed duration
     */
    DurationT elapsed() {
        auto delta = std::chrono::duration_cast<TimeT>(_end - _start);
        return delta.count();
    }

};

#endif //UTILS_H
