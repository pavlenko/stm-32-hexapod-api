#ifndef PE_SERVO180V2_HPP
#define PE_SERVO180V2_HPP

class PE_Servo180_Motor {
private:
    uint8_t reverse: 1;
    uint8_t ID: 7;
    uint16_t ticks;
    uint16_t value;
    uint16_t speed;
    uint16_t calibMin;
    uint16_t calibMax;
    uint16_t limitMin;
    uint16_t limitMax;
    void updateMotor(uint16_t value, uint16_t time);
public:
    void setRadian(float value, uint16_t time);
    void setDegree(uint16_t value, uint16_t time);
    void setMicros(uint16_t value, uint16_t time);
};

#endif //PE_SERVO180V2_HPP
