//
//  main.cpp
//  ProviderSimulation
//
//  Created by Mykhailo Khymochko on 18.01.2025.
//

#include "../includes/BaseStation.h"
#include "../includes/CentralNode.h"
#include <iostream>

int main(int argc, const char * argv[]) {

    CentralNode main_node;

    main_node.show_station_list();

    return 0;
}
