// Date: 2013
// Created by: Kevin Shahnazari

#include "ContactWithRobot.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cmath>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

using namespace std;

#define ImageRange 20
#define RedExistRange 50
#define Colorlenght 10

#define PI 3.14159265359

ContactWithRobot::ContactWithRobot()
{
    output_value = 0;
    Positionn = 0;
    HINSTANCE hDMTDll = LoadLibraryA("DMT");
    RequestData = (int(WINAPI *)(int, int, int, int, const unsigned char *, int))GetProcAddress(hDMTDll, "RequestData");
    ResponseData = (int(WINAPI *)(int, int, int *, int *, unsigned char *))GetProcAddress(hDMTDll, "ResponseData");
    OpenModbusSerial = (int(WINAPI *)(int, int, int, char, int, int))GetProcAddress(hDMTDll, "OpenModbusSerial");
    CloseSerial = (void(WINAPI *)(int))GetProcAddress(hDMTDll, "CloseSerial");
    GetLastSerialErr = (int(WINAPI *)())GetProcAddress(hDMTDll, "GetLastSerialErr");
    ResetSerialErr = (void(WINAPI *)())GetProcAddress(hDMTDll, "ResetSerialErr");
    OpenModbusTCPSocket = (int(WINAPI *)(int, int))GetProcAddress(hDMTDll, "OpenModbusTCPSocket");
    CloseSocket = (void(WINAPI *)(int))GetProcAddress(hDMTDll, "CloseSocket");
    GetLastSocketErr = (int(WINAPI *)())GetProcAddress(hDMTDll, "GetLastSocketErr");
    ResetSocketErr = (void(WINAPI *)())GetProcAddress(hDMTDll, "ResetSocketErr");
    ReadSelect = (int(WINAPI *)(int, int))GetProcAddress(hDMTDll, "ReadSelect");
    DevToAddrA = (int(WINAPI *)(const char *, const char *, int))GetProcAddress(hDMTDll, "DevToAddrA");
    ReadCoilsA = (int(WINAPI *)(int, int, int, int, int, unsigned int *, char *, char *))GetProcAddress(hDMTDll, "ReadCoilsA");
    ReadInputsA = (int(WINAPI *)(int, int, int, int, int, unsigned int *, char *, char *))GetProcAddress(hDMTDll, "ReadInputsA");
    ReadHoldRegsA = (int(WINAPI *)(int, int, int, int, int, unsigned int *, char *, char *))GetProcAddress(hDMTDll, "ReadHoldRegsA");
    ReadHoldRegs32A = (int(WINAPI *)(int, int, int, int, int, unsigned int *, char *, char *))GetProcAddress(hDMTDll, "ReadHoldRegs32A");
    ReadInputRegsA = (int(WINAPI *)(int, int, int, int, int, unsigned int *, char *, char *))GetProcAddress(hDMTDll, "ReadInputRegsA");
    WriteSingleCoilA = (int(WINAPI *)(int, int, int, int, unsigned int, char *, char *))GetProcAddress(hDMTDll, "WriteSingleCoilA");
    WriteSingleRegA = (int(WINAPI *)(int, int, int, int, unsigned int, char *, char *))GetProcAddress(hDMTDll, "WriteSingleRegA");
    WriteSingleReg32A = (int(WINAPI *)(int, int, int, int, unsigned int, char *, char *))GetProcAddress(hDMTDll, "WriteSingleReg32A");
    WriteMultiCoilsA = (int(WINAPI *)(int, int, int, int, int, const unsigned int *, char *, char *))GetProcAddress(hDMTDll, "WriteMultiCoilsA");
    WriteMultiRegsA = (int(WINAPI *)(int, int, int, int, int, const unsigned int *, char *, char *))GetProcAddress(hDMTDll, "WriteMultiRegsA");
    WriteMultiRegs32A = (int(WINAPI *)(int, int, int, int, int, const unsigned int *, char *, char *))GetProcAddress(hDMTDll, "WriteMultiRegs32A");

    conn_num = 3;
    int baud_rate = 9600;
    int data_len = 7;
    char parity = 'E';
    int stop = 1;
    int modbus_mode = 1; // 1:ASCII , 2:RTU
    int comm_type = 0;   // 0:RS-232 , 1:Ethernet
    data_len = 7;
    parity = 'E';
    modbus_mode = 1;
    int success = OpenModbusSerial(conn_num, 9600, 7, parity, 1, 1);
}

void ContactWithRobot::MoveBackwardOn()
{
    unsigned int *data = new unsigned int(4);
    data[0] = 1;
    data[1] = 0;
    data[2] = 0;
    data[3] = 1;
    WriteMultiCoilsA(0, conn_num, 1, 1280, 4, data, req, res);
}

void ContactWithRobot::MoveBackwardOff()
{
    unsigned int *data = new unsigned int(4);
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    WriteMultiCoilsA(0, conn_num, 1, 1280, 4, data, req, res);
}

void ContactWithRobot::MoveForwardOn()
{
    unsigned int *data = new unsigned int(4);
    data[0] = 0;
    data[1] = 1;
    data[2] = 1;
    data[3] = 0;
    WriteMultiCoilsA(0, conn_num, 1, 1280, 4, data, req, res);
}

void ContactWithRobot::MoveForwardOff()
{
    unsigned int *data = new unsigned int(4);
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    WriteMultiCoilsA(0, conn_num, 1, 1280, 4, data, req, res);
}

void ContactWithRobot::RotateRightOn()
{
    unsigned int *data = new unsigned int(4);
    data[0] = 0;
    data[1] = 1;
    data[2] = 0;
    data[3] = 1;
    WriteMultiCoilsA(0, conn_num, 1, 1280, 4, data, req, res);
}

void ContactWithRobot::RotateRightOff()
{
    unsigned int *data = new unsigned int(4);
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    WriteMultiCoilsA(0, conn_num, 1, 1280, 4, data, req, res);
}

void ContactWithRobot::RotateLeftOn()
{
    unsigned int *data = new unsigned int(4);
    data[0] = 1;
    data[1] = 0;
    data[2] = 1;
    data[3] = 0;
    WriteMultiCoilsA(0, conn_num, 1, 1280, 4, data, req, res);
}

void ContactWithRobot::RotateLeftOff()
{
    unsigned int *data = new unsigned int(4);
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    WriteMultiCoilsA(0, conn_num, 1, 1280, 4, data, req, res);
}

void ContactWithRobot::TowerAntiClockwiseOn()
{
    WriteSingleCoilA(0, conn_num, 0, 1284, 1, req, res);
}

void ContactWithRobot::TowerAntiClockwiseOff()
{
    WriteSingleCoilA(0, conn_num, 0, 1284, 0, req, res);
}

void ContactWithRobot::TowerClockwiseOn()
{
    WriteSingleCoilA(0, conn_num, 0, 1285, 1, req, res);
}

void ContactWithRobot::TowerClockwiseOff()
{
    WriteSingleCoilA(0, conn_num, 0, 1285, 0, req, res);
}

void ContactWithRobot::resetmotorencoders()
{
    WriteSingleReg32A(0, conn_num, 1, 3836, 0, req, res);
    WriteSingleReg32A(0, conn_num, 1, 3835, 0, req, res);
}

void ContactWithRobot::resetTowerencoder()
{
    WriteSingleReg32A(0, conn_num, 1, 3837, 0, req, res);
}

int ContactWithRobot::leftsideencoder()
{
    unsigned int datatodev;
    output_value = ReadHoldRegs32A(0, conn_num, 1, 3836, 1, &datatodev, req, res);
    output_value = datatodev;
    return output_value;
}

int ContactWithRobot::rightsideencoder()
{
    unsigned int datatodev;
    output_value = ReadHoldRegs32A(0, conn_num, 1, 3835, 1, &datatodev, req, res);
    output_value = datatodev;
    return output_value;
}

int ContactWithRobot::toptowerencoder()
{
    unsigned int datatodev;
    output_value = ReadHoldRegs32A(0, conn_num, 1, 3837, 1, &datatodev, req, res);
    output_value = datatodev;
    return output_value;
}

void ContactWithRobot::TurnOnBrush()
{
    WriteSingleCoilA(0, conn_num, 0, 1286, 1, req, res);
}

void ContactWithRobot::TurnoffBrush()
{
    WriteSingleCoilA(0, conn_num, 0, 1286, 0, req, res);
}