#ifndef TRAB5_7_TIMER_H
#define TRAB5_7_TIMER_H

class Timer {
public:
    Timer();
    void Update(float dt);
    void Restart();
    float Get();

private:
    float time;
};

#endif //TRAB5_7_TIMER_H
