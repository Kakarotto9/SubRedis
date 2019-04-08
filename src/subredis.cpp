#include "subredis.h"

SubRedisValue SubRedis::ifCommandGetReply()
{
	if (m_mode == ModeCommand)
		return getReply();
	else
	{
		SubRedisValue V;
		V.setInvalid();
		return V;
	}
}

void SubRedis::appendMap(const std::vector<std::string> &strs,
						 const std::map<std::string, std::string> &stringMap)
{
	std::vector<const char *> argv;
	std::vector<size_t> argvSize;

	for (const auto &S : strs)
	{
		argv.push_back(S.c_str());
		argvSize.push_back(S.size());
	}

	for (const auto &P : stringMap)
	{
		argv.push_back(P.first.c_str());
		argvSize.push_back(P.first.size());

		argv.push_back(P.second.c_str());
		argvSize.push_back(P.second.size());
	}

	assert(context());
	redisAppendCommandArgv(context(), argv.size(), argv.data(),
						   argvSize.data());
}

SubRedis::Mode SubRedis::mode() const { return m_mode; }

void SubRedis::setMode(const Mode &mode) { m_mode = mode; }

SubRedisValue SubRedis::AUTH(const std::string &password)
{
	append("AUTH %s", password.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ECHO(const std::string &message)
{
	append("ECHO %s", message.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PING()
{
	append("PING");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PING(const std::string &message)
{
	append("PING %s", message.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::QUIT()
{
	append("QUIT");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SELECT(long index)
{
	append("SELECT %ld", index);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SWAPDB(long db1, long db2)
{
	append("SWAPDB %ld %ld", db1, db2);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::DEL(const std::string &key)
{
	append("DEL %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::DEL(std::vector<std::string> keys)
{
	keys.insert(keys.begin(), "DEL");
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::DUMP(const std::string &key)
{
	append("DUMP %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::EXISTS(const std::string &key)
{
	append("EXISTS %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::EXISTS(const std::initializer_list<std::string> &keys)
{
	return EXISTS(std::vector<std::string>(keys));
}

SubRedisValue SubRedis::EXISTS(std::vector<std::string> keys)
{
	keys.insert(keys.begin(), "EXISTS");
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::EXPIRE(const std::string &key, long seconds)
{
	append("EXPIRE %s %ld", key.c_str(), seconds);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::EXPIREAT(const std::string &key, long timestamp)
{
	append("EXPIREAT %s %ld", key.c_str(), timestamp);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::KEYS(const std::string &pattern)
{
	append("KEYS %s", pattern.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MOVE(const std::string &key, long db)
{
	append("MOVE %s %ld", key.c_str(), db);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::OBJECT(const std::string &subcommand)
{
	append("OBJECT %s", subcommand.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::OBJECT(const std::string &subcommand,
							   const std::string &arguement)
{
	append("OBJECT %s %s", subcommand.c_str(), arguement.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::OBJECT(
	const std::string &subcommand,
	const std::initializer_list<std::string> &arguements)
{
	return OBJECT(subcommand, std::vector<std::string>(arguements));
}

SubRedisValue SubRedis::OBJECT(const std::string &subcommand,
							   std::vector<std::string> arguements)
{
	arguements.insert(arguements.begin(), subcommand);
	arguements.insert(arguements.begin(), "OBJECT");
	append(arguements);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PERSIST(const std::string &key)
{
	append("PERSIST %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PEXPIRE(const std::string &key, long milliseconds)
{
	append("PEXPIRE %s %ld", key.c_str(), milliseconds);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PEXPIREAT(const std::string &key,
								  long milliseconds_timestamp)
{
	append("PEXPIREAT %s %ld", key.c_str(), milliseconds_timestamp);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PTTL(const std::string &key)
{
	append("PTTL %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::RANDOMKEY()
{
	append("RANDOMKEY");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::RENAME(const std::string &key,
							   const std::string &newkey)
{
	append("RENAME %s %s", key.c_str(), newkey.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::RENAMENX(const std::string &key,
								 const std::string &newkey)
{
	append("RENAMENX %s %s", key.c_str(), newkey.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::RESTORE(const std::string &key, long ttl,
								const std::string &serialized_value)
{
	append("RESTORE %s %ld %b", key.c_str(), ttl, serialized_value.c_str(),
		   serialized_value.size());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::RESTORE_REPLACE(const std::string &key, long ttl,
										const std::string &serialized_value)
{
	append("RESTORE %s %ld %s REPLACE", key.c_str(), ttl,
		   serialized_value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::TOUCH(const std::string &key)
{
	append("TOUCH %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::TOUCH(const std::initializer_list<std::string> &keys)
{
	return TOUCH(std::vector<std::string>(keys));
}

SubRedisValue SubRedis::TOUCH(std::vector<std::string> keys)
{
	keys.insert(keys.begin(), "TOUCH");
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::TTL(const std::string &key)
{
	append("TTL %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::TYPE(const std::string &key)
{
	append("TYPE %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::UNLINK(const std::string &key)
{
	append("UNLINK %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::UNLINK(const std::initializer_list<std::string> &keys)
{
	return UNLINK(std::vector<std::string>(keys));
}

SubRedisValue SubRedis::UNLINK(std::vector<std::string> keys)
{
	keys.insert(keys.begin(), "UNLINK");
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::WAIT(long numreplicas, long timeout)
{
	append("WAIT %ld %ld", numreplicas, timeout);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SCAN(long cursor)
{
	append("SCAN %ld", cursor);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SCAN(long cursor, const std::string &pattern)
{
	append("SCAN %ld MATCH %s", cursor, pattern.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SCAN(long cursor, long count)
{
	append("SCAN %ld COUNT %ld", cursor, count);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SCAN(long cursor, const std::string &pattern,
							 long count)
{
	append("SCAN %ld MATCH %s COUNT %ld", cursor, pattern.c_str(), count);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BLPOP(const std::string &key, long timeout)
{
	append("BLPOP %s %ld", key.c_str(), timeout);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BLPOP(const std::initializer_list<std::string> &keys,
							  long timeout)
{
	return BLPOP(std::vector<std::string>(keys), timeout);
}

SubRedisValue SubRedis::BLPOP(std::vector<std::string> keys, long timeout)
{
	keys.insert(keys.begin(), "BLPOP");
	keys.push_back(std::to_string(timeout));
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BRPOP(const std::string &key, long timeout)
{
	append("BRPOP %s %ld", key.c_str(), timeout);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BRPOP(const std::initializer_list<std::string> &keys,
							  long timeout)
{
	return BRPOP(std::vector<std::string>(keys), timeout);
}

SubRedisValue SubRedis::BRPOP(std::vector<std::string> keys, long timeout)
{
	keys.insert(keys.begin(), "BRPOP");
	keys.push_back(std::to_string(timeout));
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BRPOPLPUSH(const std::string source,
								   const std::string &destination, long timeout)
{
	append("BRPOPLPUSH %s %s %ld", source.c_str(), destination.c_str(),
		   timeout);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::LINDEX(const std::string &key, long index)
{
	append("LINDEX %s %ld", key.c_str(), index);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::LINSERT(const std::string &key, bool before,
								const std::string &pivot,
								const std::string &value)
{
	auto cmd =
		std::string("LINSERT %s ") + (before ? "BEFORE" : "AFTER") + " %s %s";
	append(cmd.c_str(), key.c_str(), pivot.c_str(), value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::LLEN(const std::string &key)
{
	append("LLEN %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::LPOP(const std::string &key)
{
	append("LPOP %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::LPUSH(const std::string &key, const std::string &value)
{
	append("LPUSH %s %s", key.c_str(), value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::LPUSH(const std::string &key,
							  const std::initializer_list<std::string> &values)
{
	return LPUSH(key, std::vector<std::string>(values));
}

SubRedisValue SubRedis::LPUSH(const std::string &key,
							  std::vector<std::string> values)
{
	values.insert(values.begin(), key);
	values.insert(values.begin(), "LPUSH");
	append(values);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::LPUSHX(const std::string &key, const std::string &value)
{
	append("LPUSHX %s %s", key.c_str(), value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::LRANGE(const std::string &key, long start, long stop)
{
	append("LRANGE %s %ld %ld", key.c_str(), start, stop);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::LREM(const std::string &key, long count,
							 const std::string &value)
{
	append("LREM %s %ld %s", key.c_str(), count, value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::LSET(const std::string &key, long index,
							 const std::string &value)
{
	append("LSET %s %ld %s", key.c_str(), index, value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::LTRIM(const std::string &key, long start, long stop)
{
	append("LTRIM %s %ld %ld", key.c_str(), start, stop);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::RPOP(const std::string &key)
{
	append("RPOP %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::RPOPLPUSH(const std::string &source,
								  const std::string &destination)
{
	append("RPOPLPUSH %s %s", source.c_str(), destination.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::RPUSH(const std::string &key, const std::string &value)
{
	append("RPUSH %s %s", key.c_str(), value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::RPUSH(const std::string &key,
							  const std::initializer_list<std::string> &values)
{
	return RPUSH(key, std::vector<std::string>(values));
}

SubRedisValue SubRedis::RPUSH(const std::string &key,
							  std::vector<std::string> values)
{
	values.insert(values.begin(), key);
	values.insert(values.begin(), "RPUSH");
	append(values);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::RPUSHX(const std::string &key, const std::string &value)
{
	append("RPUSHX %s %s", key.c_str(), value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PSUBSCRIBE(const std::string &pattern)
{
	append("PSUBSCRIBE %s", pattern.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PSUBSCRIBE(
	const std::initializer_list<std::string> &patterns)
{
	return PSUBSCRIBE(std::vector<std::string>(patterns));
}

SubRedisValue SubRedis::PSUBSCRIBE(std::vector<std::string> patterns)
{
	patterns.insert(patterns.begin(), "PSUBSCRIBE");
	append(patterns);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PUBSUB(const std::string &subcommand)
{
	append("PUBSUB %s", subcommand.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PUBSUB(const std::string &subcommand,
							   const std::string &arguement)
{
	append("PUBSUB %s %s", subcommand.c_str(), arguement.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PUBSUB(
	const std::string &subcommand,
	const std::initializer_list<std::string> &arguements)
{
	return PUBSUB(subcommand, std::vector<std::string>(arguements));
}

SubRedisValue SubRedis::PUBSUB(const std::string &subcommand,
							   std::vector<std::string> arguements)
{
	arguements.insert(arguements.begin(), subcommand);
	arguements.insert(arguements.begin(), "PUBSUB");
	append(arguements);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PUBLISH(const std::string &channel,
								const std::string &message)
{
	append("PUBLISH %s %s", channel.c_str(), message.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PUNSUBSCRIBE()
{
	append("PUNSUBSCRIBE");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PUNSUBSCRIBE(const std::string &pattern)
{
	append("PUNSUBSCRIBE %s", pattern.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PUNSUBSCRIBE(
	const std::initializer_list<std::string> &patterns)
{
	return PUNSUBSCRIBE(std::vector<std::string>(patterns));
}

SubRedisValue SubRedis::PUNSUBSCRIBE(std::vector<std::string> patterns)
{
	patterns.insert(patterns.begin(), "PUNSUBSCRIBE");
	append(patterns);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SUBSCRIBE(const std::string &channel)
{
	append("SUBSCRIBE %s", channel.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SUBSCRIBE(
	const std::initializer_list<std::string> &channels)
{
	return SUBSCRIBE(std::vector<std::string>(channels));
}

SubRedisValue SubRedis::SUBSCRIBE(std::vector<std::string> channels)
{
	channels.insert(channels.begin(), "SUBSCRIBE");
	append(channels);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::UNSUBSCRIBE()
{
	append("UNSUBSCRIBE");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::UNSUBSCRIBE(const std::string &channel)
{
	append("UNSUBSCRIBE %s", channel);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::UNSUBSCRIBE(
	const std::initializer_list<std::string> &channels)
{
	return UNSUBSCRIBE(std::vector<std::string>(channels));
}

SubRedisValue SubRedis::UNSUBSCRIBE(std::vector<std::string> channels)
{
	channels.insert(channels.begin(), "UNSUBSCRIBE");
	append(channels);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SADD(const std::string &key, const std::string &member)
{
	append("SADD %s %s", key.c_str(), member.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SADD(const std::string &key,
							 const std::initializer_list<std::string> &members)
{
	return SADD(key, std::vector<std::string>(members));
}

SubRedisValue SubRedis::SADD(const std::string &key,
							 std::vector<std::string> members)
{
	members.insert(members.begin(), key);
	members.insert(members.begin(), "SADD");
	append(members);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SCARD(const std::string &key)
{
	append("SCARD %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SDIFF(const std::string &key)
{
	append("SDIFF %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SDIFF(const std::initializer_list<std::string> &keys)
{
	return SDIFF(std::vector<std::string>(keys));
}

SubRedisValue SubRedis::SDIFF(std::vector<std::string> keys)
{
	keys.insert(keys.begin(), "SDIFF");
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SDIFFSTORE(const std::string &destination,
								   const std::string &key)
{
	append("SDIFFSTORE %s %s", destination.c_str(), key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SDIFFSTORE(
	const std::string &destination,
	const std::initializer_list<std::string> &keys)
{
	return SDIFFSTORE(destination, std::vector<std::string>(keys));
}

SubRedisValue SubRedis::SDIFFSTORE(const std::string &destination,
								   std::vector<std::string> keys)
{
	keys.insert(keys.begin(), destination);
	keys.insert(keys.begin(), "SDIFFSTORE");
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SINTER(const std::string &key)
{
	append("SINTER %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SINTER(const std::initializer_list<std::string> &keys)
{
	return SINTER(std::vector<std::string>(keys));
}

SubRedisValue SubRedis::SINTER(std::vector<std::string> keys)
{
	keys.insert(keys.begin(), "SINTER");
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SINTERSTORE(const std::string &destination,
									const std::string &key)
{
	append("SINTERSTORE %s %s", destination.c_str(), key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SINTERSTORE(
	const std::string &destination,
	const std::initializer_list<std::string> &keys)
{
	return SINTERSTORE(destination, std::vector<std::string>(keys));
}

SubRedisValue SubRedis::SINTERSTORE(const std::string &destination,
									std::vector<std::string> keys)
{
	keys.insert(keys.begin(), destination);
	keys.insert(keys.begin(), "SINTERSTORE");
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SISMEMBER(const std::string &key,
								  const std::string &member)
{
	append("SISMEMBER %s %s", key.c_str(), member.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SMEMBERS(const std::string &key)
{
	append("SMEMBERS %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SMOVE(const std::string &source,
							  const std::string &destination,
							  const std::string &member)
{
	append("SMOVE %s %s %s", source.c_str(), destination.c_str(),
		   member.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SPOP(const std::string &key)
{
	append("SPOP %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SPOP(const std::string &key, long count)
{
	append("SPOP %s %ld", key.c_str(), count);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SRANDMEMBER(const std::string &key)
{
	append("SRANDMEMBER %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SRANDMEMBER(const std::string &key, long count)
{
	append("SRANDMEMBER %s %ld", key.c_str(), count);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SREM(const std::string &key, const std::string &member)
{
	append("SREM %s %s", key.c_str(), member.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SREM(const std::string &key,
							 const std::initializer_list<std::string> &members)
{
	return SREM(key, std::vector<std::string>(members));
}

SubRedisValue SubRedis::SREM(const std::string &key,
							 std::vector<std::string> members)
{
	members.insert(members.begin(), key);
	members.insert(members.begin(), "SREM");
	append(members);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SUNION(const std::string &key)
{
	append("SUNION %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SUNION(const std::initializer_list<std::string> &keys)
{
	return SUNION(std::vector<std::string>(keys));
}

SubRedisValue SubRedis::SUNION(std::vector<std::string> keys)
{
	keys.insert(keys.begin(), "SUNION");
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SUNIONSTORE(const std::string &destination,
									const std::string &key)
{
	append("SUNIONSTORE %s %s", destination.c_str(), key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SUNIONSTORE(
	const std::string &destination,
	const std::initializer_list<std::string> &keys)
{
	return SUNIONSTORE(destination, std::vector<std::string>(keys));
}

SubRedisValue SubRedis::SUNIONSTORE(const std::string &destination,
									std::vector<std::string> keys)
{
	keys.insert(keys.begin(), destination);
	keys.insert(keys.begin(), "SUNIONSTORE");
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SSCAN(const std::string &key, long cursor)
{
	append("SSCAN %s %ld", key.c_str(), cursor);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SSCAN(const std::string &key, long cursor,
							  const std::string &pattern)
{
	append("SSCAN %s %ld MATCH %s", key.c_str(), cursor, pattern.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SSCAN(const std::string &key, long cursor, long count)
{
	append("SSCAN %s %ld COUNT %ld", key.c_str(), cursor, count);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SSCAN(const std::string &key, long cursor,
							  const std::string &pattern, long count)
{
	append("SSCAN %s %ld MATCH %s COUNT %ld", key.c_str(), cursor,
		   pattern.c_str(), count);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::DISCARD()
{
	append("DISCARD");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::EXEC()
{
	append("EXEC");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MULTI()
{
	append("MULTI");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::UNWATCH()
{
	append("UNWATCH");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::WATCH(const std::string &key)
{
	append("WATCH %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::WATCH(const std::initializer_list<std::string> &keys)
{
	return WATCH(std::vector<std::string>(keys));
}

SubRedisValue SubRedis::WATCH(std::vector<std::string> keys)
{
	keys.insert(keys.begin(), "WATCH");
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::APPEND(const std::string &key, const std::string &value)
{
	append("APPEND %s %s", key.c_str(), value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BITCOUNT(const std::string &key)
{
	append("BITCOUNT %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BITCOUNT(const std::string &key, long start, long end)
{
	append("BITCOUNT %s %ld %ld", key.c_str(), start, end);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BITOP(const std::string &operation,
							  const std::string &destkey,
							  const std::string &key)
{
	append("BITOP %s %s %s", operation.c_str(), destkey.c_str(), key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BITOP(const std::string &operation,
							  const std::string &destkey,
							  const std::initializer_list<std::string> &keys)
{
	return BITOP(operation, destkey, std::vector<std::string>(keys));
}

SubRedisValue SubRedis::BITOP(const std::string &operation,
							  const std::string &destkey,
							  std::vector<std::string> keys)
{
	keys.insert(keys.begin(), destkey);
	keys.insert(keys.begin(), operation);
	keys.insert(keys.begin(), "BITOP");
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BITPOS(const std::string &key, long bit)
{
	append("BITPOS %s %ld", key.c_str(), bit);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BITPOS(const std::string &key, long bit, long start)
{
	append("BITPOS %s %ld %ld", key.c_str(), bit, start);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BITPOS(const std::string &key, long bit, long start,
							   long end)
{
	append("BITPOS %s %ld %ld %ld", key.c_str(), bit, start, end);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::DECR(const std::string &key)
{
	append("DECR %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::DECRBY(const std::string &key, long decrement)
{
	append("DECRBY %s %ld", key.c_str(), decrement);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::GET(const std::string &key)
{
	append("GET %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::GETBIT(const std::string &key, long offset)
{
	append("GETBIT %s %ld", key.c_str(), offset);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::GETRANGE(const std::string &key, long start, long end)
{
	append("GETRANGE %s %ld %ld", key.c_str(), start, end);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::GETSET(const std::string &key, const std::string &value)
{
	append("GETSET %s %s", key.c_str(), value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::INCR(const std::string &key)
{
	append("INCR %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::INCRBY(const std::string &key, long increment)
{
	append("INCRBY %s %ld", key.c_str(), increment);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::INCRBYFLOAT(const std::string &key, double increment)
{
	append("INCRBYFLOAT %s %f", key.c_str(), increment);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MGET(const std::string &key)
{
	append("MGET %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MGET(const std::initializer_list<std::string> &keys)
{
	return MGET(std::vector<std::string>(keys));
}

SubRedisValue SubRedis::MGET(std::vector<std::string> keys)
{
	keys.insert(keys.begin(), "MGET");
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MSET(const std::string &key, const std::string &value)
{
	append("MSET %s %s", key.c_str(), value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MSET(const std::map<std::string, std::string> &map)
{
	appendMap({"MSET"}, map);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MSETNX(const std::string &key, const std::string &value)
{
	append("MSETNX %s %s", key.c_str(), value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MSETNX(const std::map<std::string, std::string> &map)
{
	appendMap({"MSETNX"}, map);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PSETEX(const std::string &key, long milliseconds,
							   const std::string &value)
{
	append("PSETEX %s %ld %s", key.c_str(), milliseconds, value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SET(const std::string &key, const std::string &value)
{
	append("SET %s %s", key.c_str(), value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SETBIT(const std::string &key, long offset, bool value)
{
	append("SETBIT %s %ld %ld", key.c_str(), offset, value);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SETEX(const std::string &key, long seconds,
							  const std::string &value)
{
	append("SETEX %s %ld %s", key.c_str(), seconds, value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SETNX(const std::string &key, const std::string &value)
{
	append("SETNX %s %s", key.c_str(), value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SETRANGE(const std::string &key, long offset,
								 const std::string &value)
{
	append("SETRANGE %s %ld %s", key.c_str(), offset, value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::STRLEN(const std::string &key)
{
	append("STRLEN %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PFADD(const std::string &key,
							  const std::string &element)
{
	append("PFADD %s %s", key.c_str(), element.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PFADD(
	const std::string &key, const std::initializer_list<std::string> &elements)
{
	return PFADD(key, std::vector<std::string>(elements));
}

SubRedisValue SubRedis::PFADD(const std::string &key,
							  std::vector<std::string> elements)
{
	elements.insert(elements.begin(), key);
	elements.insert(elements.begin(), "PFADD");
	append(elements);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PFCOUNT(const std::string &key)
{
	append("PFCOUNT %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PFCOUNT(const std::initializer_list<std::string> &keys)
{
	return PFCOUNT(std::vector<std::string>(keys));
}

SubRedisValue SubRedis::PFCOUNT(std::vector<std::string> keys)
{
	keys.insert(keys.begin(), "PFCOUNT");
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PFMERGE(const std::string &destkey,
								const std::string &sourcekey)
{
	append("PFMERGE %s %s", destkey.c_str(), sourcekey.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::PFMERGE(
	const std::string &destkey,
	const std::initializer_list<std::string> &sourcekeys)
{
	return PFMERGE(destkey, std::vector<std::string>(sourcekeys));
}

SubRedisValue SubRedis::PFMERGE(const std::string &destkey,
								std::vector<std::string> sourcekeys)
{
	sourcekeys.insert(sourcekeys.begin(), destkey);
	sourcekeys.insert(sourcekeys.begin(), "PFMERGE");
	append(sourcekeys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::GEOADD(const std::string &key, double longitude,
							   double latitude, const std::string &member)
{
	append("GEOADD %s %f %f %s", key.c_str(), longitude, latitude,
		   member.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::GEOHASH(const std::string &key,
								const std::string &member)
{
	append("GEOHASH %s %s", key.c_str(), member.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::GEOHASH(
	const std::string &key, const std::initializer_list<std::string> &members)
{
	return GEOHASH(key, std::vector<std::string>(members));
}

SubRedisValue SubRedis::GEOHASH(const std::string &key,
								std::vector<std::string> members)
{
	members.insert(members.begin(), key);
	members.insert(members.begin(), "GEOHASH");
	append(members);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::GEOPOS(const std::string &key,
							   const std::string &member)
{
	append("GEOPOS %s %s", key.c_str(), member.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::GEOPOS(
	const std::string &key, const std::initializer_list<std::string> &members)
{
	return GEOPOS(key, std::vector<std::string>(members));
}

SubRedisValue SubRedis::GEOPOS(const std::string &key,
							   std::vector<std::string> members)
{
	members.insert(members.begin(), key);
	members.insert(members.begin(), "GEOPOS");
	append(members);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::GEODIST(const std::string &key,
								const std::string &member1,
								const std::string &member2)
{
	append("GEODIST %s %s %s", key.c_str(), member1.c_str(), member2.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::GEODIST(const std::string &key,
								const std::string &member1,
								const std::string &member2,
								const std::string &unit)
{
	append("GEODIST %s %s %s %s", key.c_str(), member1.c_str(), member2.c_str(),
		   unit.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BGREWRITEAOF()
{
	append("BGREWRITEAOF");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BGSAVE()
{
	append("BGSAVE");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::CLIENT_ID()
{
	append("CLIENT ID");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::CLIENT_LIST()
{
	append("CLIENT LIST");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::CLIENT_LIST(const std::string &type)
{
	append("CLIENT LIST TYPE %s", type.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::CLIENT_GETNAME()
{
	append("CLIENT GETNAME");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::CLIENT_PAUSE(long timeout)
{
	append("CLIENT PAUSE %ld", timeout);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::CLIENT_REPLY(const std::string &arg)
{
	append("CLIENT REPLY %s", arg.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::CLIENT_SETNAME(const std::string &connection_name)
{
	append("CLIENT SETNAME %s", connection_name.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::CLIENT_UNBLOCK(long client_id)
{
	append("CLIENT UNBLOCK %ld", client_id);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::CLIENT_UNBLOCK_TIMEOUT(long client_id)
{
	append("CLIENT UNBLOCK %ld TIMEOUT", client_id);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::CLIENT_UNBLOCK_ERROR(long client_id)
{
	append("CLIENT UNBLOCK %ld ERROR", client_id);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::COMMAND()
{
	append("COMMAND");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::COMMAND_COUNT()
{
	append("COMMAND COUNT");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::COMMAND_INFO(const std::string &command_name)
{
	append("COMMAND INFO %s", command_name.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::COMMAND_INFO(
	const std::initializer_list<std::string> &command_names)
{
	return COMMAND_INFO(std::vector<std::string>(command_names));
}

SubRedisValue SubRedis::COMMAND_INFO(std::vector<std::string> command_names)
{
	command_names.insert(command_names.begin(), "INFO");
	command_names.insert(command_names.begin(), "COMMAND");
	append(command_names);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::CONFIG_GET(const std::string &parameter)
{
	append("CONFIG GET %s", parameter.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::CONFIG_REWRITE()
{
	append("CONFIG REWRITE");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::CONFIG_SET(const std::string &parameter,
								   const std::string &value)
{
	append("CONFIG SET %s %s", parameter.c_str(), value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::CONFIG_RESETSTAT()
{
	append("CONFIG RESETSTAT");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::DBSIZE()
{
	append("DBSIZE");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::DEBUG_OBJECT(const std::string &key)
{
	append("DEBUG OBJECT %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::DEBUG_SEGFAULT()
{
	append("DEBUG SEGFAULT");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::FLUSHALL()
{
	append("FLUSHALL");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::FLUSHALL_ASYNC()
{
	append("FLUSHALL ASYNC");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::FLUSHDB()
{
	append("FLUSHDB");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::FLUSHDB_ASYNC()
{
	append("FLUSHDB ASYNC");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::INFO()
{
	append("INFO");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::INFO(const std::string &section)
{
	append("INFO %s", section.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::LASTSAVE()
{
	append("LASTSAVE");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MEMORY_DOCTOR()
{
	append("MEMORY DOCTOR");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MEMORY_HELP()
{
	append("MEMORY HELP");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MEMORY_MALLOC_STATS()
{
	append("MEMORY MALLOC-STATS");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MEMORY_PURGE()
{
	append("MEMORY PURGE");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MEMORY_STATS()
{
	append("MEMORY STATS");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MEMORY_USAGE(const std::string &key)
{
	append("MEMORY USAGE %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MEMORY_USAGE(const std::string &key, long count)
{
	append("MEMORY USAGE %s SAMPLES %ld", key.c_str(), count);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::MONITOR()
{
	append("MONITOR");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ROLE()
{
	append("ROLE");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SAVE()
{
	append("SAVE");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SHUTDOWN()
{
	append("SHUTDOWN");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SHUTDOWN(bool save)
{
	auto cmd = std::string("SHUTDOWN ") + (save ? "SAVE" : "NOSAVE");
	append(cmd.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SLAVEOF(const std::string &host, int port)
{
	append("SLAVEOF %s %ld", host.c_str(), port);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::REPLICAOF(const std::string &host, int port)
{
	append("REPLICAOF %s %ld", host.c_str(), port);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SLOWLOG(const std::string &subcommand)
{
	append("SLOWLOG %s", subcommand.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SLOWLOG(const std::string &subcommand,
								const std::string &arguement)

{
	append("SLOWLOG %s %s", subcommand.c_str(), arguement.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::TIME()
{
	append("TIME");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HDEL(const std::string &key, const std::string &field)
{
	append("HDEL %s %s", key.c_str(), field.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HDEL(const std::string &key,
							 const std::initializer_list<std::string> &fields)
{
	return HDEL(key, std::vector<std::string>(fields));
}

SubRedisValue SubRedis::HDEL(const std::string &key,
							 std::vector<std::string> fields)
{
	fields.insert(fields.begin(), key);
	fields.insert(fields.begin(), "HDEL");
	append(fields);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HEXISTS(const std::string &key,
								const std::string &field)
{
	append("HEXISTS %s %s", key.c_str(), field.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HGET(const std::string &key, const std::string &field)
{
	append("HGET %s %s", key.c_str(), field.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HGETALL(const std::string &key)
{
	append("HGETALL %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HINCRBY(const std::string &key,
								const std::string &field, long increment)
{
	append("HINCRBY %s %s %ld", key.c_str(), field.c_str(), increment);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HINCRBYFLOAT(const std::string &key,
									 const std::string &field, double increment)
{
	append("HINCRBYFLOAT %s %s %f", key.c_str(), field.c_str(), increment);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HKEYS(const std::string &key)
{
	append("HKEYS %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HLEN(const std::string &key)
{
	append("HLEN %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HMGET(const std::string &key, const std::string &field)
{
	append("HMGET %s %s", key.c_str(), field.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HMGET(const std::string &key,
							  const std::initializer_list<std::string> &fields)
{
	return HMGET(key, std::vector<std::string>(fields));
}

SubRedisValue SubRedis::HMGET(const std::string &key,
							  std::vector<std::string> fields)
{
	fields.insert(fields.begin(), key);
	fields.insert(fields.begin(), "HMGET");
	append(fields);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HMSET(const std::string &key, const std::string &field,
							  const std::string &value)
{
	append("HMSET %s %s %s", key.c_str(), field.c_str(), value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HMSET(const std::string &key,
							  const std::map<std::string, std::string> &map)
{
	appendMap({"HMSET", key}, map);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HSET(const std::string &key, const std::string &field,
							 const std::string &value)
{
	append("HSET %s %s %s", key.c_str(), field.c_str(), value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HSETNX(const std::string &key, const std::string &field,
							   const std::string &value)
{
	append("HSETNX %s %s %s", key.c_str(), field.c_str(), value.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HSTRLEN(const std::string &key,
								const std::string &field)
{
	append("HSTRLEN %s %s", key.c_str(), field.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HVALS(const std::string &key)
{
	append("HVALS %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HSCAN(const std::string &key, long cursor)
{
	append("HSCAN %s %ld", key.c_str(), cursor);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HSCAN(const std::string &key, long cursor,
							  const std::string &pattern)
{
	append("HSCAN %s %ld MATCH %s", key.c_str(), cursor, pattern.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HSCAN(const std::string &key, long cursor, long count)
{
	append("HSCAN %s %ld COUNT %ld", key.c_str(), cursor, count);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::HSCAN(const std::string &key, long cursor,
							  const std::string &pattern, long count)
{
	append("HSCAN %s %ld MATCH %s COUNT %ld", key.c_str(), cursor,
		   pattern.c_str(), count);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::EVAL(const std::string &script, long numkeys,
							 const std::string &key, const std::string &arg)
{
	append("EVAL %s %ld %s %s", script.c_str(), numkeys, key.c_str(),
		   arg.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::EVAL(const std::string &script, long numkeys,
							 const std::initializer_list<std::string> &keys,
							 const std::initializer_list<std::string> &args)
{
	return EVAL(script, numkeys, std::vector<std::string>(keys),
				std::vector<std::string>(args));
}

SubRedisValue SubRedis::EVAL(const std::string &script, long numkeys,
							 const std::vector<std::string> &keys,
							 const std::vector<std::string> &args)
{
	std::vector<std::string> V;
	V.push_back("EVAL");
	V.push_back(script);
	V.push_back(std::to_string(numkeys));
	V.insert(V.end(), keys.begin(), keys.end());
	V.insert(V.end(), args.begin(), args.end());

	append(V);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::EVALSHA(const std::string &sha1, long numkeys,
								const std::string &key, const std::string &arg)
{
	append("EVALSHA %s %ld %s %s", sha1.c_str(), numkeys, key.c_str(),
		   arg.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::EVALSHA(const std::string &sha1, long numkeys,
								const std::initializer_list<std::string> &keys,
								const std::initializer_list<std::string> &args)
{
	return EVALSHA(sha1, numkeys, std::vector<std::string>(keys),
				   std::vector<std::string>(args));
}

SubRedisValue SubRedis::EVALSHA(const std::string &sha1, long numkeys,
								const std::vector<std::string> &keys,
								const std::vector<std::string> &args)
{
	std::vector<std::string> V;
	V.push_back("EVALSHA");
	V.push_back(sha1);
	V.push_back(std::to_string(numkeys));
	V.insert(V.end(), keys.begin(), keys.end());
	V.insert(V.end(), args.begin(), args.end());

	append(V);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SCRIPT_DEBUG(const std::string &arg)
{
	append("SCRIPT DEBUG %s", arg.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SCRIPT_EXISTS(const std::string &sha1)
{
	append("SCRIPT EXISTS %s", sha1.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SCRIPT_EXISTS(
	const std::initializer_list<std::string> &sha1s)
{
	return SCRIPT_EXISTS(std::vector<std::string>(sha1s));
}

SubRedisValue SubRedis::SCRIPT_EXISTS(std::vector<std::string> sha1s)
{
	sha1s.insert(sha1s.begin(), "EXISTS");
	sha1s.insert(sha1s.begin(), "SCRIPT");
	append(sha1s);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SCRIPT_FLUSH()
{
	append("SCRIPT FLUSH");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SCRIPT_KILL()
{
	append("SCRIPT KILL");
	return ifCommandGetReply();
}

SubRedisValue SubRedis::SCRIPT_LOAD(const std::string &script)
{
	append("SCRIPT LOAD %s", script);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BZPOPMIN(const std::string &key, long timeout)
{
	append("BZPOPMIN %s %ld", key.c_str(), timeout);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BZPOPMIN(const std::initializer_list<std::string> &keys,
								 long timeout)
{
	return BZPOPMIN(std::vector<std::string>(keys), timeout);
}

SubRedisValue SubRedis::BZPOPMIN(std::vector<std::string> keys, long timeout)
{
	keys.insert(keys.begin(), "BZPOPMIN");
	keys.push_back(std::to_string(timeout));
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BZPOPMAX(const std::string &key, long timeout)
{
	append("BZPOPMAX %s %ld", key.c_str(), timeout);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::BZPOPMAX(const std::initializer_list<std::string> &keys,
								 long timeout)
{
	return BZPOPMAX(std::vector<std::string>(keys), timeout);
}

SubRedisValue SubRedis::BZPOPMAX(std::vector<std::string> keys, long timeout)
{
	keys.insert(keys.begin(), "BZPOPMAX");
	keys.push_back(std::to_string(timeout));
	append(keys);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZADD(const std::string &key, long score,
							 const std::string &member)
{
	append("ZADD %s %ld %s", key.c_str(), score, member.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZCARD(const std::string &key)
{
	append("ZCARD %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZCOUNT(const std::string &key, long min, long max)
{
	append("ZCOUNT %s %ld %ld", key.c_str(), min, max);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZINCRBY(const std::string &key, long increment,
								const std::string &member)
{
	append("ZINCRBY %s %ld %s", key.c_str(), increment, member.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZPOPMAX(const std::string &key)

{
	append("ZPOPMAX %s", key.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZPOPMAX(const std::string &key, long count)

{
	append("ZPOPMAX %s %ld", key.c_str(), count);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZPOPMIN(const std::string &key, long count)

{
	append("ZPOPMIN %s %ld", key.c_str(), count);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZRANGE(const std::string &key, long start, long stop)
{
	append("ZRANGE %s %ld %ld", key.c_str(), start, stop);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZRANGE_WITHSCORES(const std::string &key, long start,
										  long stop)
{
	append("ZRANGE %s %ld %ld WITHSCORES", key.c_str(), start, stop);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZRANK(const std::string &key, const std::string &member)
{
	append("ZRANK %s %s", key.c_str(), member.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZREM(const std::string &key, const std::string &member)
{
	append("ZREM %s %s", key.c_str(), member.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZREM(const std::string &key,
							 const std::initializer_list<std::string> &members)
{
	return ZREM(key, std::vector<std::string>(members));
}

SubRedisValue SubRedis::ZREM(const std::string &key,
							 std::vector<std::string> members)
{
	members.insert(members.begin(), key);
	members.insert(members.begin(), "ZREM");
	append(members);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZREMRANGEBYRANK(const std::string &key, long start,
										long stop)
{
	append("ZREMRANGEBYRANK %s %ld %ld", key.c_str(), start, stop);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZREMRANGEBYSCORE(const std::string &key, long min,
										 long max)
{
	append("ZREMRANGEBYSCORE %s %ld %ld", key.c_str(), min, max);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZREVRANGE(const std::string &key, long start, long stop)
{
	append("ZREVRANGE %s %ld %ld", key.c_str(), start, stop);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZREVRANGE_WITHSCORES(const std::string &key, long start,
											 long stop)
{
	append("ZREVRANGE %s %ld %ld WITHSCORES", key.c_str(), start, stop);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZREVRANK(const std::string &key,
								 const std::string &member)
{
	append("ZREVRANK %s %s", key.c_str(), member.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZSCORE(const std::string &key,
							   const std::string &member)
{
	append("ZSCORE %s %s", key.c_str(), member.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZSCAN(const std::string &key, long cursor)
{
	append("ZSCAN %s %ld", key.c_str(), cursor);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZSCAN(const std::string &key, long cursor,
							  const std::string &pattern)
{
	append("ZSCAN %s %ld MATCH %s", key.c_str(), cursor, pattern.c_str());
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZSCAN(const std::string &key, long cursor, long count)
{
	append("ZSCAN %s %ld COUNT %ld", key.c_str(), cursor, count);
	return ifCommandGetReply();
}

SubRedisValue SubRedis::ZSCAN(const std::string &key, long cursor,
							  const std::string &pattern, long count)
{
	append("ZSCAN %s %ld MATCH %s COUNT %ld", key.c_str(), cursor,
		   pattern.c_str(), count);
	return ifCommandGetReply();
}
