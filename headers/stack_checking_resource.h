#include <memory_resource>
#include <exception>
#include <iostream>
#include <cstdint>
#include <pthread.h>
#include <string>
#include <array>
#include <type_traits>
template <std::size_t Size> 
class stack_checking_resource final : public std::pmr::memory_resource {
public:

  auto do_allocate(std::size_t bytes, [[maybe_unused]] std::size_t alignment) -> void* override {
    if(bytes > Size) throw std::bad_alloc();
    auto ret = reinterpret_cast<void*>(m_buffer + this->bytes_allocated);
    std::size_t act_size = Size - this->bytes_allocated;
    ret = std::align(alignment,bytes,ret,act_size);
    if(ret == nullptr) throw std::bad_alloc();
    bytes_allocated += bytes;
    if(bytes_allocated > Size) throw std::bad_alloc();
    return ret;
  }

  [[maybe_unused]]
  auto do_deallocate(
      [[maybe_unused]] void* begin_ptr, 
      [[maybe_unused]] std::size_t bytes,
      [[maybe_unused]] std::size_t alignment) -> void {      
  }
  void reset(){
    bytes_allocated = 0;
  }

  auto do_is_equal(const std::pmr::memory_resource& other) const noexcept -> bool override {
    try {
      [[maybe_unused]]
      const auto& _ = dynamic_cast<decltype(*this)&>(other);
      return true;
    } catch(const std::bad_cast&) {
      return false;
    }
  }

private:
  std::aligned_storage_t<sizeof(std::byte), alignof(std::byte)> m_buffer[Size];
  inline static std::size_t bytes_allocated = 0;
};

/*ToDo*/
/* Change m_buffer to std::aligned_store */