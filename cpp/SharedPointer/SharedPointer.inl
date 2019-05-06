#include <stdexcept>

namespace Utility
{
template<class T>
SharedPointer<T>::SharedPointer(T* ptr)
: data_{ptr}, counter_{new uint32_t(1U)}
{
}

template<class T>
SharedPointer<T>::~SharedPointer()
{
  release();
}

template<class T>
SharedPointer<T>::SharedPointer(const SharedPointer& other)
{
  *this = other;
}

template<class T>
auto SharedPointer<T>::operator=(const SharedPointer& other) -> SharedPointer&
{ 
  if(data_ != other.data_)
  {
    release();
    data_ = other.data_;
    counter_ = other.counter_;
    increment();
  }

  return *this;
}

template<class T>
SharedPointer<T>::SharedPointer(SharedPointer&& other) noexcept
{
  *this = std::move(other);
}

template<class T>
auto SharedPointer<T>::operator=(SharedPointer&& other) noexcept -> SharedPointer&
{ 
  if(data_ != other.data_)
  {
    release();
    data_ = other.data_;
    counter_ = other.counter_;
  }

  return *this;
}

template<class T>
T* SharedPointer<T>::get() const
{
  return data_;
}

template<class T>
T& SharedPointer<T>::operator*() const
{
  if(data_ == nullptr)
  {
    throw std::runtime_error("Invalid data!");
  }

  return *data_;
}

template<class T>
T* SharedPointer<T>::operator->() const
{
  if(data_ == nullptr)
  {
    throw std::runtime_error("Invalid data!");
  }

  return get();
}

template<class T>
uint32_t SharedPointer<T>::use_count() const
{
  if(counter_ == nullptr)
  {
    return 0U;
  }

  return *counter_; 
}

template<class T>
void SharedPointer<T>::release()
{
  if(counter_ != nullptr)
  {
    --(*counter_);
    if(*counter_ == 0U)
    {
      delete data_;
      delete counter_;  
    }
  }
}

template<class T>
void SharedPointer<T>::increment() const
{
  if(counter_ != nullptr)
  {
    ++(*counter_);
  }
}

template<class T, class... Args>
SharedPointer<T> make_shared(Args&&... args)
{
  return SharedPointer(new T(std::forward<Args>(args)...));
}
}
