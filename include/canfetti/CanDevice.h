#pragma once
#include <functional>
#include <type_traits>
#include "Types.h"

namespace canfetti {

class CanDevice {
 public:
  struct Stats {
    size_t droppedPrioTx = 0;
    size_t droppedTx     = 0;
    size_t droppedRx     = 0;
    size_t overruns      = 0;
  };

  CanDevice();

  template <size_t N>
  Error write(uint16_t cobid, uint8_t (&payload)[N], bool prio = false)
  {
    canfetti::Msg msg = {
        .id   = cobid,
        .rtr  = false,
        .len  = N,
        .data = payload,
    };
    return prio ? writePriority(msg) : write(msg);
  }

  virtual Error write(const Msg &msg) = 0;
  virtual Error writePriority(const Msg &msg) { return write(msg); }

  Stats stats;
};

}  // namespace canfetti