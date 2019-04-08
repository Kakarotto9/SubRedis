#ifndef SUBSAFEREDIS_H
#define SUBSAFEREDIS_H

#include "subbaseredis.h"

#include <mutex>

struct SubRedisErrorStruct
{
public:
	SubRedisError error;
	std::string errorStr;
};

//线程安全版本的redis

class SubSafeRedis
{
private:
	std::mutex m_mutex;
	SubBaseRedis m_redis;

public:
	SubSafeRedis();

	bool isValid();

	bool connect(const std::string &ip, int port,
				 SubRedisErrorStruct *errStruct = nullptr);

	bool connect(const std::string &path,
				 SubRedisErrorStruct *errStruct = nullptr);

	void disconnect();

	template <typename... Values>
	SubRedisValue command(const std::string &cmd, Values &&... values);


	template <typename... Values>
	SubRedisValue command(SubRedisErrorStruct *errStruct,
						  const std::string &cmd, Values &&... values);

	SubRedisValue command(const std::vector<std::string> &stringList,
						  SubRedisErrorStruct *errStruct = nullptr);
};

template <typename... Values>
SubRedisValue SubSafeRedis::command(const std::string &cmd, Values &&... values)
{
	m_mutex.lock();
	auto value = m_redis.command(cmd, values...);
	m_mutex.unlock();
	return value;
}

template <typename... Values>
SubRedisValue SubSafeRedis::command(SubRedisErrorStruct *errStruct,
									const std::string &cmd, Values &&... values)
{
	m_mutex.lock();
	auto value = m_redis.command(cmd, values...);

	if (errStruct)
	{
		errStruct->error = m_redis.error();
		errStruct->errorStr = m_redis.errorStr();
	}

	m_mutex.unlock();
	return value;
}

#endif  // SUBSAFEREDIS_H
