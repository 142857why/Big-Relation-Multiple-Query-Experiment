#include <iostream>
#include <vector>
#include "application/application.hpp"
std::vector<int> number_scan;
int number_view;
int number_lookup;
int number_ring_x_ring;
int number_v_x_ring;
int number_ring_plus_ring;
int number_lifting;

int main(int argc, char** argv) {
    
    int opt_num_runs = 1;
    bool opt_print_result = true;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--num-runs") == 0 || strcmp(argv[i], "-r") == 0) {
            opt_num_runs = atoi(argv[i + 1]);
        }
        opt_print_result = opt_print_result && (strcmp(argv[i], "--no-output") != 0);
    }

#ifndef __APPLE__
    cpu_set_t  mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
#endif
    // Init the statistics
    number_view = 0;
    number_scan = std::vector<int>(10000, 0); // 10000 is the default/max number of views
    number_lookup = 0;
    number_ring_x_ring = 0;
    number_v_x_ring = 0;
    number_ring_plus_ring = 0;
    number_lifting = 0;

    Application app;
    app.run(opt_num_runs, opt_print_result);

    // Output those statistics
    std::cout << "number of views: " << number_view << std::endl;
    for (int i = 0; i < number_view; i++)
        std::cout << "number of scans on view " << (i+1) << ": " << number_scan[i] << std::endl;
    std::cout << "number of lookups: " << number_lookup << std::endl;
    std::cout << "number of ring x ring: " << number_ring_x_ring << std::endl;
    std::cout << "number of v x ring: " << number_v_x_ring << std::endl;
    std::cout << "number of ring + ring: " << number_ring_plus_ring << std::endl;
    std::cout << "number of lifting: " << number_lifting << std::endl;

    return 0;
}