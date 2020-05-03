// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: serviceMethod.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_serviceMethod_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_serviceMethod_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3011000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3011002 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_serviceMethod_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_serviceMethod_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_serviceMethod_2eproto;
class serviceMethod;
class serviceMethodDefaultTypeInternal;
extern serviceMethodDefaultTypeInternal _serviceMethod_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::serviceMethod* Arena::CreateMaybeMessage<::serviceMethod>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class serviceMethod :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:serviceMethod) */ {
 public:
  serviceMethod();
  virtual ~serviceMethod();

  serviceMethod(const serviceMethod& from);
  serviceMethod(serviceMethod&& from) noexcept
    : serviceMethod() {
    *this = ::std::move(from);
  }

  inline serviceMethod& operator=(const serviceMethod& from) {
    CopyFrom(from);
    return *this;
  }
  inline serviceMethod& operator=(serviceMethod&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const serviceMethod& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const serviceMethod* internal_default_instance() {
    return reinterpret_cast<const serviceMethod*>(
               &_serviceMethod_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(serviceMethod& a, serviceMethod& b) {
    a.Swap(&b);
  }
  inline void Swap(serviceMethod* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline serviceMethod* New() const final {
    return CreateMaybeMessage<serviceMethod>(nullptr);
  }

  serviceMethod* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<serviceMethod>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const serviceMethod& from);
  void MergeFrom(const serviceMethod& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(serviceMethod* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "serviceMethod";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_serviceMethod_2eproto);
    return ::descriptor_table_serviceMethod_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kServiceNameFieldNumber = 1,
    kMethodNameFieldNumber = 2,
  };
  // string service_name = 1;
  void clear_service_name();
  const std::string& service_name() const;
  void set_service_name(const std::string& value);
  void set_service_name(std::string&& value);
  void set_service_name(const char* value);
  void set_service_name(const char* value, size_t size);
  std::string* mutable_service_name();
  std::string* release_service_name();
  void set_allocated_service_name(std::string* service_name);
  private:
  const std::string& _internal_service_name() const;
  void _internal_set_service_name(const std::string& value);
  std::string* _internal_mutable_service_name();
  public:

  // string method_name = 2;
  void clear_method_name();
  const std::string& method_name() const;
  void set_method_name(const std::string& value);
  void set_method_name(std::string&& value);
  void set_method_name(const char* value);
  void set_method_name(const char* value, size_t size);
  std::string* mutable_method_name();
  std::string* release_method_name();
  void set_allocated_method_name(std::string* method_name);
  private:
  const std::string& _internal_method_name() const;
  void _internal_set_method_name(const std::string& value);
  std::string* _internal_mutable_method_name();
  public:

  // @@protoc_insertion_point(class_scope:serviceMethod)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr service_name_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr method_name_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_serviceMethod_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// serviceMethod

// string service_name = 1;
inline void serviceMethod::clear_service_name() {
  service_name_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& serviceMethod::service_name() const {
  // @@protoc_insertion_point(field_get:serviceMethod.service_name)
  return _internal_service_name();
}
inline void serviceMethod::set_service_name(const std::string& value) {
  _internal_set_service_name(value);
  // @@protoc_insertion_point(field_set:serviceMethod.service_name)
}
inline std::string* serviceMethod::mutable_service_name() {
  // @@protoc_insertion_point(field_mutable:serviceMethod.service_name)
  return _internal_mutable_service_name();
}
inline const std::string& serviceMethod::_internal_service_name() const {
  return service_name_.GetNoArena();
}
inline void serviceMethod::_internal_set_service_name(const std::string& value) {
  
  service_name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void serviceMethod::set_service_name(std::string&& value) {
  
  service_name_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:serviceMethod.service_name)
}
inline void serviceMethod::set_service_name(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  service_name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:serviceMethod.service_name)
}
inline void serviceMethod::set_service_name(const char* value, size_t size) {
  
  service_name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:serviceMethod.service_name)
}
inline std::string* serviceMethod::_internal_mutable_service_name() {
  
  return service_name_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* serviceMethod::release_service_name() {
  // @@protoc_insertion_point(field_release:serviceMethod.service_name)
  
  return service_name_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void serviceMethod::set_allocated_service_name(std::string* service_name) {
  if (service_name != nullptr) {
    
  } else {
    
  }
  service_name_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), service_name);
  // @@protoc_insertion_point(field_set_allocated:serviceMethod.service_name)
}

// string method_name = 2;
inline void serviceMethod::clear_method_name() {
  method_name_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& serviceMethod::method_name() const {
  // @@protoc_insertion_point(field_get:serviceMethod.method_name)
  return _internal_method_name();
}
inline void serviceMethod::set_method_name(const std::string& value) {
  _internal_set_method_name(value);
  // @@protoc_insertion_point(field_set:serviceMethod.method_name)
}
inline std::string* serviceMethod::mutable_method_name() {
  // @@protoc_insertion_point(field_mutable:serviceMethod.method_name)
  return _internal_mutable_method_name();
}
inline const std::string& serviceMethod::_internal_method_name() const {
  return method_name_.GetNoArena();
}
inline void serviceMethod::_internal_set_method_name(const std::string& value) {
  
  method_name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void serviceMethod::set_method_name(std::string&& value) {
  
  method_name_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:serviceMethod.method_name)
}
inline void serviceMethod::set_method_name(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  method_name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:serviceMethod.method_name)
}
inline void serviceMethod::set_method_name(const char* value, size_t size) {
  
  method_name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:serviceMethod.method_name)
}
inline std::string* serviceMethod::_internal_mutable_method_name() {
  
  return method_name_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* serviceMethod::release_method_name() {
  // @@protoc_insertion_point(field_release:serviceMethod.method_name)
  
  return method_name_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void serviceMethod::set_allocated_method_name(std::string* method_name) {
  if (method_name != nullptr) {
    
  } else {
    
  }
  method_name_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), method_name);
  // @@protoc_insertion_point(field_set_allocated:serviceMethod.method_name)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_serviceMethod_2eproto
