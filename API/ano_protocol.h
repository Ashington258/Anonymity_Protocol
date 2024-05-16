#ifndef ANO_PROTOCOL_H
#define ANO_PROTOCOL_H

#include <stdint.h>
#include <stdbool.h>

#define ANO_FRAME_SIZE 50

uint8_t ANO_FRAME[ANO_FRAME_SIZE];

void write_int16_le(uint8_t *buffer, int16_t data);

void ANO_Convert_16(int16_t data);
void ANO_Convert_32(int32_t data);
void IMU_DATA(int16_t _accx, int16_t _accy, int16_t _accz, int16_t _gryx, int16_t _gyy, int16_t _gryz, uint8_t _sta);
void ANO_Conver_16_16_16(int16_t data_1, int16_t data_2, int16_t data_3);


#endif /* ANO_PROTOCOL_H */
