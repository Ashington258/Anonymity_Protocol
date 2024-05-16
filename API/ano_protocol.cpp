#include "ano_protocol.h"
#include <stdio.h>

/// @brief 将data变量拼接成匿名自由帧协议发送出去
/// @param data 任意的需要分析的一个变量（这里是整形的int16变量）
void ANO_Convert_16(int16_t data)
{

    uint8_t sumcheck = 0;
    uint8_t addcheck = 0;

    uint8_t _index = 0;         // 设置索引，使需要更多格式的变量时方便更改
    ANO_FRAME[_index++] = 0xAA; // 自由帧的帧头
    ANO_FRAME[_index++] = 0xFF; // 自由帧的目标地址
    ANO_FRAME[_index++] = 0xF1; // 自由帧的功能码
    ANO_FRAME[_index++] = 2;    // 需要发送的变量字节数
    // CORE 此处变量发送使用小端模式，低字节在前，高字节在后。
    ANO_FRAME[_index++] = data & 0xFF;
    ANO_FRAME[_index++] = (data >> 8) & 0xFF;

    // 校验和的计算，此时只计算到ANO_FRAM的数据为的低位即可，上位机会验证以保证协议的安全性
    for (uint8_t i = 0; i < (ANO_FRAME[3] + 4); i++)
    {
        sumcheck += ANO_FRAME[i];
        addcheck += sumcheck;
    }

    ANO_FRAME[_index++] = sumcheck;
    ANO_FRAME[_index++] = addcheck;
    // CORE 此处增加发送函数，重定向到串口，发送到上位机
    // for (size_t i = 0; i < 8; i++)
    // {
    //     printf("%02x,", ANO_FRAME[i]);
    // }
}

void ANO_Convert_32(int32_t data)
{
    uint8_t sumcheck = 0;
    uint8_t addcheck = 0;

    uint8_t _index = 0;         // 设置索引，使需要更多格式的变量时方便更改
    ANO_FRAME[_index++] = 0xAA; // 自由帧的帧头
    ANO_FRAME[_index++] = 0xFF; // 自由帧的目标地址
    ANO_FRAME[_index++] = 0xF1; // 自由帧的功能码
    ANO_FRAME[_index++] = 4;    // 需要发送的变量字节数
    // CORE 此处变量发送使用小端模式，低字节在前，高字节在后。
    ANO_FRAME[_index++] = data & 0xFF;
    ANO_FRAME[_index++] = (data >> 8) & 0xFF;
    ANO_FRAME[_index++] = (data >> 16) & 0xFF;
    ANO_FRAME[_index++] = (data >> 24) & 0xFF;

    // 校验和的计算，此时只计算到ANO_FRAM的数据为的低位即可，上位机会验证以保证协议的安全性
    for (uint8_t i = 0; i < (ANO_FRAME[3] + 4); i++)
    {
        sumcheck += ANO_FRAME[i];
        addcheck += sumcheck;
    }

    ANO_FRAME[_index++] = sumcheck;
    ANO_FRAME[_index++] = addcheck;
    // CORE 此处增加发送函数，重定向到串口，发送到上位机
    // for (size_t i = 0; i < 10; i++)
    // {
    //     printf("%02x,", ANO_FRAME[i]);
    // }
}

void ANO_Conver_16_16_16(int16_t data_1, int16_t data_2, int16_t data_3)
{
    uint8_t sumcheck = 0;
    uint8_t addcheck = 0;

    uint8_t _index = 0;
    ANO_FRAME[_index++] = 0xAA; // 自由帧的帧头
    ANO_FRAME[_index++] = 0xFF; // 自由帧的目标地址
    ANO_FRAME[_index++] = 0xF1; // 自由帧的功能码
    ANO_FRAME[_index++] = 6;    // 需要发送的变量字节数
    // CORE 此处变量发送使用小端模式，低字节在前，高字节在后。

    write_int16_le(&ANO_FRAME[_index], data_1);
    _index += 2;
    write_int16_le(&ANO_FRAME[_index], data_2);
    _index += 2;
    write_int16_le(&ANO_FRAME[_index], data_3);
    _index += 2;

    // 校验和的计算，此时只计算到ANO_FRAM的数据为的低位即可，上位机会验证以保证协议的安全性
    for (uint8_t i = 0; i < (ANO_FRAME[3] + 4); i++)
    {
        sumcheck += ANO_FRAME[i];
        addcheck += sumcheck;
    }

    ANO_FRAME[_index++] = sumcheck;
    ANO_FRAME[_index++] = addcheck;
    // CORE 此处增加发送函数，重定向到串口，发送到上位机
    // for (size_t i = 0; i < 10; i++)
    // {
    //     printf("%02x,", ANO_FRAME[i]);
    // }
}

// 将 int16_t 数据按小端模式写入数组
void write_int16_le(uint8_t *buffer, int16_t data)
{
    buffer[0] = data & 0xFF;        // 写入低字节
    buffer[1] = (data >> 8) & 0xFF; // 写入高字节
}

void IMU_DATA(int16_t _accx, int16_t _accy, int16_t _accz, int16_t _gryx, int16_t _gyy, int16_t _gryz, uint8_t _sta)
{
    uint8_t imu_data[19];
    uint8_t _index = 0; // 设置索引，使需要更多格式的变量时方便更改

    uint8_t sumcheck = 0;
    uint8_t addcheck = 0;

    ANO_FRAME[_index++] = 0xAA; // 帧头
    ANO_FRAME[_index++] = 0xFF; // 目标地址
    ANO_FRAME[_index++] = 0x01; // 功能码
    ANO_FRAME[_index++] = 13;   // 数据长度为13Byte

    write_int16_le(&ANO_FRAME[_index], _accx);
    _index += 2; // 发送了两个Byte索引加2
    write_int16_le(&ANO_FRAME[_index], _accy);
    _index += 2; // 发送了两个Byte索引加2
    write_int16_le(&ANO_FRAME[_index], _accz);
    _index += 2; // 发送了两个Byte索引加2

    write_int16_le(&ANO_FRAME[_index], _gryx);
    _index += 2; // 发送了两个Byte索引加2
    write_int16_le(&ANO_FRAME[_index], _gyy);
    _index += 2; // 发送了两个Byte索引加2
    write_int16_le(&ANO_FRAME[_index], _gryz);
    _index += 2; // 发送了两个Byte索引加2

    ANO_FRAME[_index++] = _sta;

    for (uint8_t i = 0; i < (ANO_FRAME[3] + 4); i++)
    {
        sumcheck += ANO_FRAME[i];
        addcheck += sumcheck;
    }

    ANO_FRAME[_index++] = sumcheck;
    ANO_FRAME[_index++] = addcheck;
}