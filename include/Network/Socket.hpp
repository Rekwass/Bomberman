/*
** EPITECH PROJECT, 2022
** include
** File description:
** Socket
*/

#pragma once

// #if defined(_WIN32)
// #ifndef windows
// #define windows
// #endif
//
// #include <Winsock2.h>
// #pragma comment(lib, "ws2_32.lib")
//
// #elif defined(_WIN64)
// #ifndef windows
// #define windows
// #endif
//
// #include <Winsock2.h>
// #pragma comment(lib, "ws2_32.lib")
// #else
// #ifndef linux
// #define linux
// #endif
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
// #endif

#include <sys/fcntl.h>
