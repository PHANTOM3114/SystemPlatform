#pragma once

#include <iostream>
#include <random>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <thread>

struct Packet {
    int id;
    std::string data;
};

class Node
{

private:

    int id;
    static std::random_device rd;
    static std::mt19937 generator;
    static std::uniform_real_distribution<double> distribution;

public:

    Node(int id) : id(id) {};

    int getId() const;
    void setId(int id);

    std::mt19937& getGenerator();
    void setGenerator(const std::mt19937& gen);

    std::uniform_real_distribution<double>& getDistribution();
    void setDistribution(const std::uniform_real_distribution<double>& dist);

    void receive(Packet packet);
    void send(Packet packet, Node& next_node, double loss_probability, int delay_ms);

};