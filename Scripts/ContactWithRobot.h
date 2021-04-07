// Date: 2013
// Created by: Kevin Shahnazari

class ContactWithRobot
{
private:
    long long int output_value;
    int conn_num;
    int Positionn;
    char req[1024], res[1024];

    // Define Some ports to connect with the PLC of the Robot
    int(WINAPI *RequestData)(int comm_type, int conn_num, int slave_addr, int func_code, const unsigned char *sendbuf, int sendlen);
    int(WINAPI *ResponseData)(int comm_type, int conn_num, int *slave_addr, int *func_code, unsigned char *recvbuf);
    int(WINAPI *OpenModbusSerial)(int conn_num, int baud_rate, int data_len, char parity, int stop_bits, int modbus_mode);
    void(WINAPI *CloseSerial)(int conn_num);
    int(WINAPI *GetLastSerialErr)();
    void(WINAPI *ResetSerialErr)();
    int(WINAPI *OpenModbusTCPSocket)(int conn_num, int ipaddr);
    void(WINAPI *CloseSocket)(int conn_num);
    int(WINAPI *GetLastSocketErr)();
    void(WINAPI *ResetSocketErr)();
    int(WINAPI *ReadSelect)(int conn_num, int SelectTime_msec);
    int(WINAPI *DevToAddrA)(const char *series, const char *device, int qty);
    int(WINAPI *ReadCoilsA)(int comm_type, int conn_num, int slave_addr, int dev_addr, int qty, unsigned int *data_r, char *req, char *res);
    int(WINAPI *ReadInputsA)(int comm_type, int conn_num, int slave_addr, int dev_addr, int qty, unsigned int *data_r, char *req, char *res);
    int(WINAPI *ReadHoldRegsA)(int comm_type, int conn_num, int slave_addr, int dev_addr, int qty, unsigned int *data_r, char *req, char *res);
    int(WINAPI *ReadHoldRegs32A)(int comm_type, int conn_num, int slave_addr, int dev_addr, int qty, unsigned int *data_r, char *req, char *res);
    int(WINAPI *ReadInputRegsA)(int comm_type, int conn_num, int slave_addr, int dev_addr, int qty, unsigned int *data_r, char *req, char *res);
    int(WINAPI *WriteSingleCoilA)(int comm_type, int conn_num, int slave_addr, int dev_addr, unsigned int data_w, char *req, char *res);
    int(WINAPI *WriteSingleRegA)(int comm_type, int conn_num, int slave_addr, int dev_addr, unsigned int data_w, char *req, char *res);
    int(WINAPI *WriteSingleReg32A)(int comm_type, int conn_num, int slave_addr, int dev_saddr, unsigned int data_w, char *req, char *res);
    int(WINAPI *WriteMultiCoilsA)(int comm_type, int conn_num, int slave_addr, int dev_addr, int qty, const unsigned int *data_w, char *req, char *res);
    int(WINAPI *WriteMultiRegsA)(int comm_type, int conn_num, int slave_addr, int dev_addr, int qty, const unsigned int *data_w, char *req, char *res);
    int(WINAPI *WriteMultiRegs32A)(int comm_type, int conn_num, int slave_addr, int dev_addr, int qty, const unsigned int *data_w, char *req, char *res);

public:
    ContactWithRobot();

    void MoveBackwardOn();
    void MoveBackwardOff();
    void MoveForwardOn();
    void MoveForwardOff();
    void RotateRightOn();
    void RotateRightOff();
    void RotateLeftOn();
    void RotateLeftOff();
    void TowerAntiClockwiseOn();
    void TowerAntiClockwiseOff();
    void TowerClockwiseOn();
    void TowerClockwiseOff();
    void resetmotorencoders();
    void resetTowerencoder();
    int leftsideencoder();
    int rightsideencoder();
    int toptowerencoder();
    void TurnOnBrush();
    void TurnoffBrush();
};
