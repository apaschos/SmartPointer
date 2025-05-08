#pragma once

#include <iostream>
#include <stdexcept>
#include <cassert>

template <typename T>
class SharedPointer
{
public:
	enum TYPE
	{
		DEFAULT,
		COPY_CONSTR,
		MOVE_CONSTR,
	};


	SharedPointer(T* p)
		: p_(p)
		, type_(DEFAULT)
	{
		std::cout << "SharedPointer()" << std::endl;
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
		, type_(COPY_CONSTR)
	{
		std::cout << "SharedPointer(&)" << std::endl;
		inc();
	}

	SharedPointer(SharedPointer&& other)
		: p_(other.p_)
		, ref_(other.ref_)
		, type_(MOVE_CONSTR)
	{
		std::cout << "SharedPointer(&&)" << std::endl;

		other.p_ = nullptr;
		other.ref_ = nullptr;
	}

	~SharedPointer()
	{
		std::cout << "~SharedPointer (" << type() << ")" << std::endl;
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

	std::string type() const
	{
		if (type_ == DEFAULT)
		{
			return "default";
		}
		else if (type_ == COPY_CONSTR)
		{
			return "copy constructor";
		}
		else if (type_ == MOVE_CONSTR)
		{
			return "move constructor";
		}
		else
		{
			return "unknown";
		}
	}


private:
	void dec()
	{
		if (ref_ == nullptr)
		{
			std::cout << "already deleted" << std::endl;
			return;
		}

		std::cout << "dec: " << (*ref_) << "->";
		--(*ref_);
		std::cout << (*ref_) << std::endl;

		if (*ref_ == 0)
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

		std::cout << "inc: " << (*ref_) << "->";
		++(*ref_);
		std::cout << (*ref_) << std::endl;
	}

	T* p_;
	int* ref_;
	TYPE type_;
};
