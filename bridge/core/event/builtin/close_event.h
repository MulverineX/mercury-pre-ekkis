/*
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */

#ifndef BRIDGE_CLOSE_EVENT_H
#define BRIDGE_CLOSE_EVENT_H

#include "bindings/qjs/dictionary_base.h"
#include "bindings/qjs/source_location.h"
#include "core/event/event.h"
#include "qjs_close_event_init.h"

namespace mercury {

struct NativeCloseEvent;

class CloseEvent : public Event {
  DEFINE_WRAPPERTYPEINFO();

 public:
  using ImplType = CloseEvent*;
  static CloseEvent* Create(ExecutingContext* context,
                            const AtomicString& type,
                            int32_t code,
                            const AtomicString& reason,
                            bool was_clean,
                            ExceptionState& exception_state);

  static CloseEvent* Create(ExecutingContext* context, const AtomicString& type, ExceptionState& exception_state);

  static CloseEvent* Create(ExecutingContext* context,
                            const AtomicString& type,
                            const std::shared_ptr<CloseEventInit>& initializer,
                            ExceptionState& exception_state);

  explicit CloseEvent(ExecutingContext* context, const AtomicString& type, ExceptionState& exception_state);
  explicit CloseEvent(ExecutingContext* context,
                      const AtomicString& type,
                      int32_t code,
                      const AtomicString& reason,
                      bool was_clean,
                      ExceptionState& exception_state);
  explicit CloseEvent(ExecutingContext* context,
                      const AtomicString& type,
                      const std::shared_ptr<CloseEventInit>& initializer,
                      ExceptionState& exception_state);
  explicit CloseEvent(ExecutingContext* context, const AtomicString& type, NativeCloseEvent* raw_event);

  bool IsCloseEvent() const override;

  int64_t code() const;
  const AtomicString& reason() const;
  bool wasClean() const;

 private:
  int64_t code_;
  AtomicString reason_;
  bool was_clean_;
};

}  // namespace mercury

#endif  // BRIDGE_CLOSE_EVENT_H
