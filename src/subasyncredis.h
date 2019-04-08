#ifndef SUBASYNCREDIS_H
#define SUBASYNCREDIS_H

#include "subbaseredis.h"

#include <hiredis/async.h>
#include <functional>
#include <iostream>
#include <vector>

//这个类是redis客户端的异步api。要看同步api访问CxxRedis类。
// 请注意，此类必须与事件库一起使用

class SubAsyncRedis
{
	//连接的回调函数
	using FunctionConnectCB = std::function<void(bool)>;

	using FunctionDisconnectCB = std::function<void(bool)>;

	using FunctionCallBack = std::function<void(const SubRedisValue &)>;

private:

	FunctionConnectCB m_connectCallBack = nullptr;

	FunctionDisconnectCB m_disconnectCallBack = nullptr;

	/// This is a redis async context provided by hiredis
	redisAsyncContext *m_context = nullptr;

	/// This function gets called
	static void ConnectCallBack(const redisAsyncContext *C, int status);
	static void DisconnectCallBack(const redisAsyncContext *C, int status);
	static void CallBack(redisAsyncContext *C, void *R, void *data);

public:
	SubAsyncRedis();
	~SubAsyncRedis();

	
	bool isValid() const;


	SubRedisError error() const;

	
	std::string errorStr() const;

	
	redisAsyncContext *context() const;


	void disconnect();

	bool connect(const std::string &ip, int port);

	
	bool connect(const std::string &path);

	// 异步调用commadn, 参数F 在 reply返回时触发
	bool command(const FunctionCallBack &F,
				 const std::vector<std::string> &stringList);


	template <typename... Values>
	bool command(const FunctionCallBack &F, const std::string &cmd,
				 Values &&... values);

	void setConnectCallBack(const FunctionConnectCB &connectCallBack);


	void setDisconnectCallBack(const FunctionDisconnectCB &disconnectCallBack);
};

template <typename... Values>
bool SubAsyncRedis::command(const FunctionCallBack &F, const std::string &cmd,
							Values &&... values)
{
	assert(m_context);

	auto R = redisAsyncCommand(m_context, &SubAsyncRedis::CallBack,
							   new FunctionCallBack(F), cmd.c_str(),
							   std::forward<Values>(values)...);

	return R == REDIS_OK;
}

#endif  // SUBASYNCREDIS_H
