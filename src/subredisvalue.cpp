#include "subredisvalue.h"

#include <iostream>

void SubRedisValue::deleteIfAllocated()
{
	if (m_type == Status || m_type == Error || m_type == String)
		delete m_value.s;
	else if (m_type == Array)
		delete m_value.a;
}

void SubRedisValue::copy(const SubRedisValue &other)
{
	auto type = other.m_type;
	m_type = type;

	if (type == String || type == Error || type == Status)
		m_value.s = new std::string(*other.m_value.s);
	else if (type == Array)
		m_value.a = new std::vector<SubRedisValue>(*other.m_value.a);
	else
		m_value = other.m_value;
}

SubRedisValue::SubRedisValue() { m_type = Null; }

SubRedisValue::~SubRedisValue() { deleteIfAllocated(); }

SubRedisValue::SubRedisValue(const SubRedisValue &other) { copy(other); }

SubRedisValue::SubRedisValue(SubRedisValue &&other)
{
	m_type = other.m_type;
	m_value = other.m_value;
	other.m_type = Null;
}

SubRedisValue::SubRedisValue(const long long &i)
{
	m_type = Integer;
	m_value.i = i;
}

SubRedisValue::SubRedisValue(const std::string &s, const SubRedisValue::Type &t)
{
	assert(t == Status || t == Error || t == String);
	m_type = t;
	m_value.s = new std::string(s);
}

SubRedisValue::SubRedisValue(const char *s, const size_t &length,
							 const SubRedisValue::Type &t)
{
	assert(t == Status || t == Error || t == String);
	m_type = t;
	m_value.s = new std::string(s, length);
}

void SubRedisValue::setInvalid()
{
	deleteIfAllocated();
	m_type = Invalid;
}

void SubRedisValue::setNull()
{
	deleteIfAllocated();
	m_type = Null;
}

void SubRedisValue::setInteger(long long i)
{
	deleteIfAllocated();
	m_type = Integer;
	m_value.i = i;
}

void SubRedisValue::setString(const std::string &s)
{
	deleteIfAllocated();
	m_type = String;
	m_value.s = new std::string(s);
}

void SubRedisValue::setStatus(const std::string &s)
{
	deleteIfAllocated();
	m_type = Status;
	m_value.s = new std::string(s);
}

void SubRedisValue::setError(const std::string &s)
{
	deleteIfAllocated();
	m_type = Error;
	m_value.s = new std::string(s);
}

void SubRedisValue::setArray(const std::vector<SubRedisValue> &a)
{
	deleteIfAllocated();
	m_type = Array;
	m_value.a = new std::vector<SubRedisValue>(a);
}

SubRedisValue::SubRedisValue(const std::vector<SubRedisValue> &a)
{
	m_type = Array;
	m_value.a = new std::vector<SubRedisValue>(a);
}

std::string SubRedisValue::typeName() const
{
	if (m_type == Invalid)
		return "invalid";
	else if (m_type == Null)
		return "null";
	else if (m_type == Integer)
		return "interger";
	else if (m_type == String)
		return "string";
	else if (m_type == Error)
		return "error";
	else if (m_type == Status)
		return "status";
	else if (m_type == Array)
		return "array";

	return "";
}

long long SubRedisValue::integer() const
{
	assert(m_type == Integer);
	return m_value.i;
}

std::string SubRedisValue::string() const
{
	assert(m_type == String);
	return *m_value.s;
}

std::vector<SubRedisValue> SubRedisValue::array() const
{
	assert(m_type == Array);
	return *m_value.a;
}

std::string SubRedisValue::error() const
{
	assert(m_type == Error);
	return *m_value.s;
}

std::string SubRedisValue::status() const
{
	assert(m_type == Status);
	return *m_value.s;
}

SubRedisValue &SubRedisValue::operator=(const SubRedisValue &V)
{
	deleteIfAllocated();
	copy(V);
	return *this;
}

std::ostream &operator<<(std::ostream &os, const SubRedisValue &V)
{
	auto name = V.typeName();
	name[0] = char(std::toupper(name[0]));
	os << "SubRedisValue<" << name << ">(";

	if (V.type() == SubRedisValue::Integer)
		os << V.integer();
	else if (V.type() == SubRedisValue::String)
		os << V.string();
	else if (V.type() == SubRedisValue::Error)
		os << V.error();
	else if (V.type() == SubRedisValue::Status)
		os << V.status();
	else if (V.type() == SubRedisValue::Array)
	{
		const auto &A = V.array();

		for (size_t i = 0; i < A.size(); ++i)
		{
			os << A[i];
			if (i < A.size() - 1) os << ", ";
		}
	}

	os << ")";
	return os;
}
