#include <stdint.h>
#include <stdio.h>

#define FRAME_SIZE 19

uint8_t ANO_FRAME[FRAME_SIZE]; // 定义一个全局数组来存储帧数据

// 将 int16_t 数据按小端模式写入数组
void write_int16_le(uint8_t *buffer, int16_t data)
{
    buffer[0] = data & 0xFF;        // 写入低字节
    buffer[1] = (data >> 8) & 0xFF; // 写入高字节
}

void IMU_DATA(int16_t _accx, int16_t _accy, int16_t _accz, int16_t _gryx, int16_t _gyy, int16_t _gryz, uint8_t _sta)
{
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

int main()
{
    // 示例数据
    int16_t accx = 0x1234;
    int16_t accy = 0x5678;
    int16_t accz = 0x9ABC;
    int16_t gryx = 0xDEF0;
    int16_t gyy = 0x1234;
    int16_t gryz = 0x5678;
    uint8_t sta = 0x01;

    // 调用 IMU_DATA 函数
    IMU_DATA(accx, accy, accz, gryx, gyy, gryz, sta);

    // 打印生成的数据帧
    for (size_t i = 0; i < FRAME_SIZE; i++)
    {
        printf("%02X,", ANO_FRAME[i]);
    }
    printf("\n");

    return 0;
}
