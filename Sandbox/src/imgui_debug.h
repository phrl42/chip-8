#pragma once


struct Stats
{
  static inline int clock_rate = 1;
  static inline float color[4] = {1, 1, 1, 1};
  
private:
  inline Stats() {}
  inline ~Stats() {}
};
