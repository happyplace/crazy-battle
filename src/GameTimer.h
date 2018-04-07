#pragma once

#include <chrono>

typedef double DeltaTimeType;

class GameTimer
{
public:
    GameTimer();
    ~GameTimer();

    DeltaTimeType TotalTime() const;
    DeltaTimeType DeltaTime() const { return mDeltaTime; }
    uint64_t FrameCount() const { return m_frameCount; }

    void Reset();
    void Start();
    void Stop();
    void Tick();
    
private:
    typedef std::chrono::milliseconds::rep TimePoint;

    const DeltaTimeType mMilliToSec;
    bool mStopped;
    DeltaTimeType mDeltaTime;
    TimePoint mBaseTime;
    TimePoint mPausedTime;
    TimePoint mStopTime;
    TimePoint mPrevTime;
    TimePoint mCurrTime;
    uint64_t m_frameCount;
};
