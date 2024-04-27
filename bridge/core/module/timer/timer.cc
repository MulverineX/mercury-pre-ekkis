/*
 * Copyright (C) 2019-2022 The Kraken authors. All rights reserved.
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */
#include "timer.h"

#include <utility>
#include "bindings/qjs/cppgc/garbage_collected.h"
#include "bindings/qjs/qjs_engine_patch.h"
#include "core/executing_context.h"

#if UNIT_TEST
#include "mercury_test_env.h"
#endif

namespace mercury {

std::shared_ptr<Timer> Timer::create(ExecutingContext* context,
                                           const std::shared_ptr<QJSFunction>& callback,
                                           TimerKind timer_kind) {
  return std::make_shared<Timer>(context, callback, timer_kind);
}

Timer::Timer(ExecutingContext* context, std::shared_ptr<QJSFunction> callback, TimerKind timer_kind)
    : context_(context), callback_(std::move(callback)), status_(TimerStatus::kPending), kind_(timer_kind) {}

void Timer::Fire() {
  if (status_ == TimerStatus::kTerminated)
    return;

  if (!callback_->IsFunction(context_->ctx()))
    return;

  ScriptValue returnValue = callback_->Invoke(context_->ctx(), ScriptValue::Empty(context_->ctx()), 0, nullptr);

  if (returnValue.IsException()) {
    context_->HandleException(&returnValue);
  }
}

void Timer::Terminate() {
  callback_ = nullptr;
  status_ = TimerStatus::kTerminated;
}

void Timer::setTimerId(int32_t timerId) {
  timer_id_ = timerId;
}

}  // namespace mercury
