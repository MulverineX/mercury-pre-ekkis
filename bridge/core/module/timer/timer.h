/*
 * Copyright (C) 2019-2022 The Kraken authors. All rights reserved.
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */
#ifndef BRIDGE_DOM_TIMER_H
#define BRIDGE_DOM_TIMER_H

#include "bindings/qjs/qjs_function.h"
#include "bindings/qjs/script_wrappable.h"
#include "timer_coordinator.h"

namespace mercury {

class Timer {
 public:
  enum TimerKind { kOnce, kMultiple };
  enum TimerStatus { kPending, kExecuting, kFinished, kCanceled, kTerminated };

  static std::shared_ptr<Timer> create(ExecutingContext* context,
                                          const std::shared_ptr<QJSFunction>& callback,
                                          TimerKind timer_kind);
  Timer(ExecutingContext* context, std::shared_ptr<QJSFunction> callback, TimerKind timer_kind);

  // Trigger timer callback.
  void Fire();

  // Mark this timer is terminated and free the underly callbacks.
  void Terminate();

  TimerKind kind() const { return kind_; }

  [[nodiscard]] int32_t timerId() const { return timer_id_; };
  void setTimerId(int32_t timerId);

  void SetStatus(TimerStatus status) { status_ = status; }
  [[nodiscard]] TimerStatus status() const { return status_; }

  ExecutingContext* context() { return context_; }

 private:
  TimerKind kind_;
  ExecutingContext* context_{nullptr};
  int32_t timer_id_{-1};
  TimerStatus status_;
  std::shared_ptr<QJSFunction> callback_;
};

}  // namespace mercury

#endif  // BRIDGE_DOM_TIMER_H
