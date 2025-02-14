#include "client.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

std::random_device Node::rd;
std::mt19937 Node::generator(Node::rd());
std::uniform_real_distribution<double> Node::distribution(0.0, 1.0);

int Node::getId() const {
    return id;
}

void Node::setId(int id) {
    this->id = id;
}

std::mt19937& Node::getGenerator() {
    return generator;
}

void Node::setGenerator(const std::mt19937& gen) {
    generator = gen;
}

std::uniform_real_distribution<double>& Node::getDistribution() {
    return distribution;
}

void Node::setDistribution(const std::uniform_real_distribution<double>& dist) {
    distribution = dist;
}

void Node::receive(Packet packet)
{
    std::cout << "Node " << id << " received packet " << packet.id << " with data - " << packet.data << "\n";
}

void Node::send(Packet packet, Node& next_node, double loss_probability, int delay_ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));

    if (distribution(generator) > loss_probability)
    {
        next_node.receive(packet);
    }
    else
    {
        std::cout << "Packet " << packet.id << " lost in transmission\n";
    }
}