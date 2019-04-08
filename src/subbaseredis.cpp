#include "subbaseredis.h"

SubBaseRedis::SubBaseRedis() {}

SubBaseRedis::~SubBaseRedis() { freeContext(); }

bool SubBaseRedis::isValid() const { return m_context; }

std::string SubBaseRedis::errorStr() const
{
	assert(m_context);
	return std::string(m_context->errstr);
}

void SubBaseRedis::freeContext()
{
	if (m_context) redisFree(m_context);
	m_context = nullptr;
}

redisContext *SubBaseRedis::context() const { return m_context; }

SubRedisError SubBaseRedis::error() const
{
	assert(m_context);

	if (m_context->err == REDIS_OK)
		return NoError;
	else if (m_context->err == REDIS_ERR_EOF)
		return EOFError;
	else if (m_context->err == REDIS_ERR_IO)
		return IOError;
	else if (m_context->err == REDIS_ERR_OOM)
		return OutOfMemoryError;
	else if (m_context->err == REDIS_ERR_OTHER)
		return OtherError;
	else if (m_context->err == REDIS_ERR_PROTOCOL)
		return ProtocolError;

	return UnknownError;
}

SubRedisValue SubBaseRedis::replyToValue(redisReply *R)
{
	if (R->type == REDIS_REPLY_STATUS)
		return SubRedisValue(R->str, R->len, SubRedisValue::Status);
	else if (R->type == REDIS_REPLY_ERROR)
		return SubRedisValue(R->str, R->len, SubRedisValue::Error);
	else if (R->type == REDIS_REPLY_STRING)
		return SubRedisValue(R->str, R->len);
	else if (R->type == REDIS_REPLY_INTEGER)
		return SubRedisValue(R->integer);
	else if (R->type == REDIS_REPLY_NIL)
		return SubRedisValue();
	else if (R->type == REDIS_REPLY_ARRAY)
	{
		std::vector<SubRedisValue> V(R->elements);

		for (size_t i = 0; i < R->elements; ++i)
			V[i] = replyToValue(R->element[i]);

		return SubRedisValue(V);
	}

	SubRedisValue V;
	V.setInvalid();
	return V;
}

SubRedisValue SubBaseRedis::processReply(void *reply)
{
	if (reply == nullptr)
	{
		SubRedisValue V;
		V.setInvalid();
		return V;
	}

	auto R = static_cast<redisReply *>(reply);
	auto V = replyToValue(R);
	freeReplyObject(reply);
	return V;
}

bool SubBaseRedis::connect(const std::string &path)
{
	if (m_context)
		redisReconnect(m_context);
	else
		m_context = redisConnectUnix(path.c_str());

	return !(m_context == nullptr || m_context->err);
}

void SubBaseRedis::disconnect()
{
	assert(m_context);
	freeContext();
}

bool SubBaseRedis::connect(const std::string &ip, int port)
{
	if (m_context)
		redisReconnect(m_context);
	else
		m_context = redisConnect(ip.c_str(), port);

	return !(m_context == nullptr || m_context->err);
}

SubRedisValue SubBaseRedis::getReply()
{
	assert(m_context);
	void *R = nullptr;
	redisGetReply(m_context, &R);
	return processReply(R);
}

SubRedisValue SubBaseRedis::command(const std::vector<std::string> &stringList)
{
	std::vector<const char *> argv;
	std::vector<size_t> argvSize;

	for (const auto &S : stringList)
	{
		argv.push_back(S.c_str());
		argvSize.push_back(S.size());
	}

	assert(m_context);
	auto reply =
		redisCommandArgv(m_context, argv.size(), argv.data(), argvSize.data());
	return processReply(reply);
}

void SubBaseRedis::append(const std::vector<std::string> &stringList)
{
	std::vector<const char *> argv;
	std::vector<size_t> argvSize;

	for (const auto &S : stringList)
	{
		argv.push_back(S.c_str());
		argvSize.push_back(S.size());
	}

	assert(m_context);
	redisAppendCommandArgv(m_context, argv.size(), argv.data(),
						   argvSize.data());
}
