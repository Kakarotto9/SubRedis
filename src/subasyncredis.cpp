#include "subasyncredis.h"

void SubAsyncRedis::ConnectCallBack(const redisAsyncContext *C, int status)
{
	auto *R = static_cast<SubAsyncRedis *>(C->data);
	if (R->m_connectCallBack) R->m_connectCallBack(status == REDIS_OK);
}

void SubAsyncRedis::DisconnectCallBack(const redisAsyncContext *C, int status)
{
	auto *R = static_cast<SubAsyncRedis *>(C->data);
	if (R->m_disconnectCallBack) R->m_disconnectCallBack(status == REDIS_OK);
}

void SubAsyncRedis::CallBack(redisAsyncContext *C, void *R, void *data)
{
	(void)C;
	auto F = static_cast<FunctionCallBack *>(data);
	(*F)(SubBaseRedis::processReply(R));
	delete F;
}

SubAsyncRedis::SubAsyncRedis() {}

SubAsyncRedis::~SubAsyncRedis()
{
	if (m_context) redisAsyncFree(m_context);
}

bool SubAsyncRedis::isValid() const { return m_context; }

void SubAsyncRedis::disconnect()
{
	assert(m_context);

	redisAsyncSetDisconnectCallback(m_context,
									&SubAsyncRedis::DisconnectCallBack);
	redisAsyncDisconnect(m_context);
	m_context = nullptr;
}

bool SubAsyncRedis::connect(const std::string &ip, int port)
{
	if (m_context)
		redisAsyncFree(m_context);
	else
		m_context = redisAsyncConnect(ip.c_str(), port);

	if (m_context)
		redisAsyncSetConnectCallback(m_context,
									 &SubAsyncRedis::ConnectCallBack);

	if (m_context) m_context->data = this;
	return !(m_context == nullptr || m_context->err);
}

bool SubAsyncRedis::connect(const std::string &path)
{
	if (m_context)
		redisAsyncFree(m_context);
	else
		m_context = redisAsyncConnectUnix(path.c_str());

	if (m_context)
		redisAsyncSetConnectCallback(m_context,
									 &SubAsyncRedis::ConnectCallBack);

	if (m_context) m_context->data = this;
	return !(m_context == nullptr || m_context->err);
}

bool SubAsyncRedis::command(const SubAsyncRedis::FunctionCallBack &F,
							const std::vector<std::string> &stringList)
{
	assert(m_context);

	std::vector<const char *> argv;
	std::vector<size_t> argvSize;

	for (const auto &S : stringList)
	{
		argv.push_back(S.c_str());
		argvSize.push_back(S.size());
	}

	auto R = redisAsyncCommandArgv(m_context, &SubAsyncRedis::CallBack,
								   new FunctionCallBack(F), argv.size(),
								   argv.data(), argvSize.data());

	return R == REDIS_OK;
}

SubRedisError SubAsyncRedis::error() const
{
	assert(m_context);

	if (m_context->err == REDIS_OK)
		return SubRedisError::NoError;
	else if (m_context->err == REDIS_ERR_EOF)
		return SubRedisError::EOFError;
	else if (m_context->err == REDIS_ERR_IO)
		return SubRedisError::IOError;
	else if (m_context->err == REDIS_ERR_OOM)
		return SubRedisError::OutOfMemoryError;
	else if (m_context->err == REDIS_ERR_OTHER)
		return SubRedisError::OtherError;
	else if (m_context->err == REDIS_ERR_PROTOCOL)
		return SubRedisError::ProtocolError;

	return SubRedisError::UnknownError;
}

std::string SubAsyncRedis::errorStr() const
{
	assert(m_context);
	return std::string(m_context->errstr);
}

redisAsyncContext *SubAsyncRedis::context() const { return m_context; }

void SubAsyncRedis::setConnectCallBack(const FunctionConnectCB &connectCallBack)
{
	m_connectCallBack = connectCallBack;
}

void SubAsyncRedis::setDisconnectCallBack(
	const FunctionDisconnectCB &disconnectCallBack)
{
	m_disconnectCallBack = disconnectCallBack;
}
