#include <doyouknow_class.hpp>

class A
{
	public:
		A(void);
		~A(void);
		A(A const& rhs) : m_i(rhs.m_i)
		{
			// Non-compliant
			++m_static;
		}
	private:
		int32_t m_i;
		static int32_t m_static;
};

A::A(void)
{
	m_i = 0;
	m_static = 0;
	return;
}

A::~A(void)
{
	return;
}

int32_t A::m_static = 0;

A f(void)
{
	return A();
}

void b(void)
{
	A a = f();
	A b = a;
	return;
}

DOYOUKNOW_CLASS::DOYOUKNOW_CLASS(void)
{
	return;
}

DOYOUKNOW_CLASS::~DOYOUKNOW_CLASS(void)
{
	return;
}

void DOYOUKNOW_CLASS::std_class(void)
{
	try {
		b();
		return;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
}

void main(void)
{

	DOYOUKNOW_CLASS* do_you_know_ptr;
	do_you_know_ptr = new DOYOUKNOW_CLASS();

	do_you_know_ptr->std_class();

	delete do_you_know_ptr;
	do_you_know_ptr = nullptr;

	return;
}