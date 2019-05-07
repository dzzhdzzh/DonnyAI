#pragma once

#include <cstdint>

namespace Utility
{
/// @brief An implmentation of shared pointer.  
template<class T>
class SharedPointer
{
public:
/// @brief Defulat constructor.
SharedPointer() = default;

/// @brief Default deconstructor.
~SharedPointer();

/// @brief Construct with raw pointer.
explicit SharedPointer(T* ptr);

/// @brief Copy constructor.
SharedPointer(const SharedPointer& other);

/// @brief Copy assignment.
SharedPointer& operator=(const SharedPointer& other);

/// @brief Move constructor.
SharedPointer(SharedPointer&& other) noexcept;

/// @brief Mover assignment.
SharedPointer& operator=(SharedPointer&& other) noexcept;

/// @brief Get stored raw pointer.
/// @return Stored raw pointer.
T* get() const;

/// @brief Dereference stored pointer.
/// @return Reference to the object.
/// @throw Throw if data is invalid.
T& operator*() const;

/// @brief Dereference object member.
/// @return Pointer to access object member.
/// @throw Throw if data is invalid.
T* operator->() const;

/// @brief Get counter of object been shared.
/// @return Shared counter. 
uint32_t use_count() const;

private:
/// @brief Update counter and release object if needs.
void release();

/// @brief increment the counter;
void increment() const;

/// @brief Data raw pointer.
T* data_{nullptr};

/// @breif Reference counter.
uint32_t* counter_{nullptr};
};

/// Factory function creating a shared pointer pointing to the object T.
template<class T, class... Args>
SharedPointer<T> make_shared(Args&&... args);
}

#include "SharedPointer.inl"
