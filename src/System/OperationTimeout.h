/*
 * Copyright (c) 2018, The bitcoin2network developers.
 * Portions Copyright (c) 2012-2017, The CryptoNote Developers, The Bytecoin Developers.
 *
 * This file is part of bitcoin2network.
 *
 * This file is subject to the terms and conditions defined in the
 * file 'LICENSE', which is part of this source code package.
 */

#pragma once

#include <System/ContextGroup.h>
#include <System/Dispatcher.h>
#include <System/Timer.h>

namespace System {

template<typename T> class OperationTimeout {
public:
  OperationTimeout(Dispatcher& dispatcher, T& object, std::chrono::nanoseconds timeout) :
    object(object), timerContext(dispatcher), timeoutTimer(dispatcher) {
    timerContext.spawn([this, timeout]() {
      try {
        timeoutTimer.sleep(timeout);
        timerContext.interrupt();
      } catch (...) {
      }
    });
  }

  ~OperationTimeout() {
    timerContext.interrupt();
    timerContext.wait();
  }

private:
  T& object;
  ContextGroup timerContext;
  Timer timeoutTimer;
};

}
