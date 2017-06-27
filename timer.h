#ifndef TIMER_H
#define TIMER_H

//CLASS
class Timer
{
  private:
    unsigned long startTime;
    unsigned long currentTime;
    const unsigned int duration;

  public:
    Timer(int maxTimer);
    void start_timer();
    void reset_timer();
    void increment_timer();
    bool is_timer_reached();
    bool is_timer_running();
};

#endif
