#ifndef SUBBASEREDIS_H
#define SUBBASEREDIS_H

#include "subredisvalue.h"

#include <hiredis/hiredis.h>
#include <iostream>
#include <map>

//此枚举包含连接期间可能发生的错误或执行命令。
//你可以使用error（）函数获取最后一个错误。
enum SubRedisError
{
	NoError,
	IOError,
	EOFError,
	ProtocolError,
	OutOfMemoryError,
	OtherError,
	UnknownError,
};

// 这个类封装了一个Redis上下文，它可以连接到Redis server并执行命令
// 此类不是抽象类，也没有虚函数 我分离了主要的功能和辅助功能,将主函数放在此处，将辅助函数放在SubRedis类中。
// 所以不要直接使用这个类。请改用SubRedis。

class SubBaseRedis
{
	/// need use processReply() function
	friend class SubAsyncRedis;

private:

	redisContext *m_context = nullptr;

	// /此函数接受hiredis回复并将其数据读入 CxxRedisValue并释放给定的回复。
	static SubRedisValue processReply(void *reply);

	/// 内部使用 processReply() 去读redivalue
	static SubRedisValue replyToValue(redisReply *R);

	// 释放redisContext
	void freeContext();

public:
	SubBaseRedis();
	~SubBaseRedis();


	bool isValid() const;


	SubRedisError error() const;

	// /此函数返回描述错误内容的最后一个错误字符串。
	// / @returns包含decription的std :: string
	std::string errorStr() const;

	// 此函数返回封装的RedisonText,通常时候不要调用这个函数
	redisContext *context() const;

	// /此函数用于使用ip 和port 连接Redis服务器。如果这个功能 返回false你可以看到error（）和errorStr（）显式的错误
	bool connect(const std::string &ip, int port);

	bool connect(const std::string &path);

	void disconnect();

	// /此函数用于命令服务器。在这个版本的命令中 需要传递一个命令以及格式化所需的其他参数
	/// For Example:
	/// @code
	/// R.command("SET %s %s", "foo", "bar");
	/// @endcode
	/// @see command(const std::vector<std::string> &stringList), append()
	template <typename... Values>
	SubRedisValue command(const std::string &cmd, Values &&... values);

	// /此函数用于命令服务器。在这个版本的命令中 需要传递字符串
	/// @code
	/// R.command({"SET", "foo", "bar"});
	/// @endcode
	/// @see command(), append()
	SubRedisValue command(const std::vector<std::string> &stringList);

	// 作用和command相同 ，主要用于 pipelining操作
	template <typename... Values>
	void append(const std::string &cmd, Values &&... values);

	void append(const std::vector<std::string> &stringList);

	//这个函数首先检查是否有未回复的回复
	//如果是，则返回一个。否则，它会将输出缓冲区刷新到套接字并读取直到它有回复
	SubRedisValue getReply();
};

template <typename... Values>
SubRedisValue SubBaseRedis::command(const std::string &cmd, Values &&... values)
{
	assert(m_context);
	auto reply =
		redisCommand(m_context, cmd.c_str(), std::forward<Values>(values)...);
	return processReply(reply);
}

template <typename... Values>
void SubBaseRedis::append(const std::string &cmd, Values &&... values)
{
	assert(m_context);
	redisAppendCommand(m_context, cmd.c_str(), std::forward<Values>(values)...);
}

#endif  // SUBBASEREDIS_H
