/*
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */

#ifndef MERCURY_DART_CONTEXT_H_
#define MERCURY_DART_CONTEXT_H_

#include <set>
#include "bindings/qjs/script_value.h"
#include "dart_context_data.h"
#include "dart_methods.h"

namespace mercury {

class MercuryIsolate;
class DartIsolateContext;

struct DartWireContext {
  ScriptValue jsObject;
};

void InitializeBuiltInStrings(JSContext* ctx);

void WatchDartWire(DartWireContext* wire);
bool IsDartWireAlive(DartWireContext* wire);
void DeleteDartWire(DartWireContext* wire);

// DartIsolateContext has a 1:1 correspondence with a dart isolates.
class DartIsolateContext {
 public:
  explicit DartIsolateContext(const uint64_t* dart_methods, int32_t dart_methods_length);

  FORCE_INLINE JSRuntime* runtime() { return runtime_; }
  FORCE_INLINE bool valid() { return is_valid_ && std::this_thread::get_id() == running_thread_; }
  FORCE_INLINE const std::unique_ptr<DartMethodPointer>& dartMethodPtr() const {
    assert(std::this_thread::get_id() == running_thread_);
    return dart_method_ptr_;
  }

  const std::unique_ptr<DartContextData>& EnsureData() const;

  void AddNewIsolate(std::unique_ptr<MercuryIsolate>&& new_isolate);
  void RemoveIsolate(const MercuryIsolate* isolate);

  ~DartIsolateContext();

 private:
  int is_valid_{false};
  std::set<std::unique_ptr<MercuryIsolate>> mercury_isolates_;
  std::thread::id running_thread_;
  mutable std::unique_ptr<DartContextData> data_;
  static thread_local JSRuntime* runtime_;
  // Dart methods ptr should keep alive when ExecutingContext is disposing.
  const std::unique_ptr<DartMethodPointer> dart_method_ptr_ = nullptr;
};

}  // namespace mercury

#endif
