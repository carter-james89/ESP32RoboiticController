// GyroData.h
#ifndef GYRODATA_H
#define GYRODATA_H

class GyroData {
public:
    int16_t ax, ay, az;
    int16_t gx, gy, gz;

    GyroData(int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz)
        : ax(ax), ay(ay), az(az), gx(gx), gy(gy), gz(gz) {}
};

#endif // GYRODATA_H
