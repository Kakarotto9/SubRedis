#include "subsaferedis.h"

SubSafeRedis::SubSafeRedis() {}

bool SubSafeRedis::isValid()
{
	m_mutex.lock();
	auto value = m_redis.isValid();
	m_mutex.unlock();
	return value;
}

bool SubSafeRedis::connect(const std::string &ip, int port,
						   SubRedisErrorStruct *errStruct)
{
	m_mutex.lock();
	auto value = m_redis.connect(ip, port);

	if (errStruct)
	{
		errStruct->error = m_redis.error();
		errStruct->errorStr = m_redis.errorStr();
	}

	m_mutex.unlock();
	return value;
}

bool SubSafeRedis::connect(const std::string &path,
						   SubRedisErrorStruct *errStruct)
{
	m_mutex.lock();
	auto value = m_redis.connect(path);

	if (errStruct)
	{
		errStruct->error = m_redis.error();
		errStruct->errorStr = m_redis.errorStr();
	}

	m_mutex.unlock();
	return value;
}

void SubSafeRedis::disconnect()
{
	m_mutex.lock();
	m_redis.disconnect();
	m_mutex.unlock();
}

SubRedisValue SubSafeRedis::command(const std::vector<std::string> &stringList,
									SubRedisErrorStruct *errStruct)
{
	m_mutex.lock();
	auto value = m_redis.command(stringList);

	if (errStruct)
	{
		errStruct->error = m_redis.error();
		errStruct->errorStr = m_redis.errorStr();
	}

	m_mutex.unlock();
	return value;
}
