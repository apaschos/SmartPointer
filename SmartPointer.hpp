#pragma once

#include <stdexcept>
#include <cassert>

template <typename T>
class SharedPointer
{
public:
	SharedPointer(T* p)
		: p_(p)
	{
		if (p_ == nullptr)
		{
			throw std::invalid_argument("Nullptr not allowed");
		}
		ref_ = new int(0);
		inc();
	}

	SharedPointer(const SharedPointer& other)
		: p_(other.p_)
		, ref_(other.ref_)
	{
		inc();
	}

	SharedPointer(SharedPointer&& other)
		: p_(other.p_)
		, ref_(other.ref_)
	{

		other.p_ = nullptr;
		other.ref_ = nullptr;
	}

	~SharedPointer()
	{
		dec();
	}

	SharedPointer& operator=(const SharedPointer& other)
	{
		if (other == *this)
		{
			return this;
		}

		dec();

		p_ = other.p_;
		ref_ = other.ref_;

		return this;
	}

	SharedPointer& operator=(const SharedPointer&& other)
	{
		dec();

		p_ = other.p_;
		ref_ = other.ref_;

		other.p_ = nullptr;
		other.ref_ = nullptr;

		return this;
	}

	operator bool() const
	{
		return p_ != nullptr;
	}

	T operator*() const
	{
		return *data();
	}

	T val() const
	{
		assert(p_ != nullptr);
		return *p_;
	}

	T* data() const
	{
		return p_;
	}


private:
	void dec()
	{
		if (ref_ == nullptr)
		{
			return;
		}

		if (--(*ref_) == 0)
		{
			delete ref_;
			delete p_;
		}
	}

	void inc()
	{
		if (ref_ == nullptr)
		{
			return;
		}

		++(*ref_);
	}

	T* p_;
	int* ref_;
};
