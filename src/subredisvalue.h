#ifndef SUBREDISVALUE_H
#define SUBREDISVALUE_H

#include <assert.h>
#include <string>
#include <vector>

// / @brief此类保存来自服务器的回复数据。
// 
//redis回复数据可以有不同的类型。它可以是一个字符串或一个
//整数或值数组，也可以为null。该类保存数据和它的类型。
//请注意，当回复是字符串类型时，它可以是状态回复或错误回复或普通字符串值。

class SubRedisValue
{
public:
	/// This enumaration holds the type of possible values that this class can hold
	enum Type
	{
		Invalid,
		Status,
		Error,
		Integer,
		Null,
		String,
		Array,
	};

private:
	union Value
	{
		long long i;
		std::string *s;
		std::vector<SubRedisValue> *a;
	};

	Type m_type;

	Value m_value;

	void deleteIfAllocated();
	void copy(const SubRedisValue &other);

public:
	SubRedisValue();
	~SubRedisValue();

	SubRedisValue(SubRedisValue &&other);

	SubRedisValue(const SubRedisValue &other);

	/// Same as setInteger()
	SubRedisValue(const long long &i);

	SubRedisValue(const std::vector<SubRedisValue> &a);

	SubRedisValue(const std::string &s, const Type &t = String);

	/// Same as SubRedisValue(const std::string &s, const Type &t) setString()  or setError() or setStatus()
	SubRedisValue(const char *s, const size_t &length, const Type &t = String);

	void setInvalid();

	void setNull();

	void setInteger(long long i);

	void setString(const std::string &s);

	void setStatus(const std::string &s);

	void setError(const std::string &s);

	void setArray(const std::vector<SubRedisValue> &a);

	inline bool isInvalid() const { return m_type == Invalid; }

	inline bool isNull() const { return m_type == Null; }

	inline bool isInteger() const { return m_type == Integer; }

	inline bool isString() const { return m_type == String; }

	inline bool isArray() const { return m_type == Array; }

	inline bool isError() const { return m_type == Error; }

	inline bool isStatus() const { return m_type == Status; }

	/// This function returns the type of the value
	inline Type type() const { return m_type; }

	/// This function returns the name of type of the value
	std::string typeName() const;

	/// If this class holds an integer, the value is returned. otherwise the application crashes
	long long integer() const;

	std::string string() const;

	std::vector<SubRedisValue> array() const;

	std::string error() const;

	std::string status() const;

	SubRedisValue &operator=(const SubRedisValue &V);
};

std::ostream &operator<<(std::ostream &os, const SubRedisValue &V);

#endif  // SUBREDISVALUE_H
