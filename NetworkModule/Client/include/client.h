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

class Client
{
public:
    Client();
    int read_port();
    void run();
};