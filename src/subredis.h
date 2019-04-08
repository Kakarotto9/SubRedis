#ifndef SUBREDIS_H
#define SUBREDIS_H

#include "subbaseredis.h"


//这个类是redis客户端的同步api。要查看异步api 请访问CxxAsyncRedis类。
//命令使用command（）函数，如果失败，你可以得到 错误（error（）和errorStr（）显式
//还可以使用append（）和getReply（）函数进行流水线操作。

class SubRedis : public SubBaseRedis
{

public:
	enum Mode
	{
		ModeAppend,
		ModeCommand
	};

	SubRedisValue ifCommandGetReply();

private:
	Mode m_mode = ModeCommand;

	void appendMap(const std::vector<std::string> &strs,
				   const std::map<std::string, std::string> &stringMap);

public:
	using SubBaseRedis::SubBaseRedis;

	Mode mode() const;

	// 设置 Apeed 或者command 模式,如果在commadn模式，返回应答值，如果在append模式，返回无效值
	void setMode(const Mode &mode);

	// Connection Section
	SubRedisValue AUTH(const std::string &password);
	SubRedisValue ECHO(const std::string &message);
	SubRedisValue PING();
	SubRedisValue PING(const std::string &message);
	SubRedisValue QUIT();
	SubRedisValue SELECT(long index);
	SubRedisValue SWAPDB(long db1, long db2);
	// Connection Section

	// Keys Section
	SubRedisValue DEL(const std::string &key);
	SubRedisValue DEL(std::vector<std::string> keys);
	SubRedisValue DUMP(const std::string &key);
	SubRedisValue EXISTS(const std::string &key);
	SubRedisValue EXISTS(const std::initializer_list<std::string> &keys);
	SubRedisValue EXISTS(std::vector<std::string> keys);
	SubRedisValue EXPIRE(const std::string &key, long seconds);
	SubRedisValue EXPIREAT(const std::string &key, long timestamp);
	SubRedisValue KEYS(const std::string &pattern);
	//	Left out MIGRATE
	SubRedisValue MOVE(const std::string &key, long db);
	SubRedisValue OBJECT(const std::string &subcommand);
	SubRedisValue OBJECT(const std::string &subcommand,
						 const std::string &arguement);
	SubRedisValue OBJECT(const std::string &subcommand,
						 const std::initializer_list<std::string> &arguements);
	SubRedisValue OBJECT(const std::string &subcommand,
						 std::vector<std::string> arguements);
	SubRedisValue PERSIST(const std::string &key);
	SubRedisValue PEXPIRE(const std::string &key, long milliseconds);
	SubRedisValue PEXPIREAT(const std::string &key,
							long milliseconds_timestamp);
	SubRedisValue PTTL(const std::string &key);
	SubRedisValue RANDOMKEY();
	SubRedisValue RENAME(const std::string &key, const std::string &newkey);
	SubRedisValue RENAMENX(const std::string &key, const std::string &newkey);
	SubRedisValue RESTORE(const std::string &key, long ttl,
						  const std::string &serialized_value);
	SubRedisValue RESTORE_REPLACE(const std::string &key, long ttl,
								  const std::string &serialized_value);
	// Left out SORT

	SubRedisValue TOUCH(const std::string &key);
	SubRedisValue TOUCH(const std::initializer_list<std::string> &keys);
	SubRedisValue TOUCH(std::vector<std::string> keys);
	SubRedisValue TTL(const std::string &key);
	SubRedisValue TYPE(const std::string &key);
	SubRedisValue UNLINK(const std::string &key);
	SubRedisValue UNLINK(const std::initializer_list<std::string> &keys);
	SubRedisValue UNLINK(std::vector<std::string> keys);
	SubRedisValue WAIT(long numreplicas, long timeout);
	SubRedisValue SCAN(long cursor);
	SubRedisValue SCAN(long cursor, const std::string &pattern);
	SubRedisValue SCAN(long cursor, long count);
	SubRedisValue SCAN(long cursor, const std::string &pattern, long count);
	// Keys Section

	// List Section
	SubRedisValue BLPOP(const std::string &key, long timeout);
	SubRedisValue BLPOP(const std::initializer_list<std::string> &keys,
						long timeout);
	SubRedisValue BLPOP(std::vector<std::string> keys, long timeout);
	SubRedisValue BRPOP(const std::string &key, long timeout);
	SubRedisValue BRPOP(const std::initializer_list<std::string> &keys,
						long timeout);
	SubRedisValue BRPOP(std::vector<std::string> keys, long timeout);
	SubRedisValue BRPOPLPUSH(const std::string source,
							 const std::string &destination, long timeout);
	SubRedisValue LINDEX(const std::string &key, long index);
	SubRedisValue LINSERT(const std::string &key, bool before,
						  const std::string &pivot, const std::string &value);
	SubRedisValue LLEN(const std::string &key);
	SubRedisValue LPOP(const std::string &key);
	SubRedisValue LPUSH(const std::string &key, const std::string &value);
	SubRedisValue LPUSH(const std::string &key,
						const std::initializer_list<std::string> &values);
	SubRedisValue LPUSH(const std::string &key,
						std::vector<std::string> values);
	SubRedisValue LPUSHX(const std::string &key, const std::string &value);
	SubRedisValue LRANGE(const std::string &key, long start, long stop);
	SubRedisValue LREM(const std::string &key, long count,
					   const std::string &value);
	SubRedisValue LSET(const std::string &key, long index,
					   const std::string &value);
	SubRedisValue LTRIM(const std::string &key, long start, long stop);
	SubRedisValue RPOP(const std::string &key);
	SubRedisValue RPOPLPUSH(const std::string &source,
							const std::string &destination);
	SubRedisValue RPUSH(const std::string &key, const std::string &value);
	SubRedisValue RPUSH(const std::string &key,
						const std::initializer_list<std::string> &values);
	SubRedisValue RPUSH(const std::string &key,
						std::vector<std::string> values);
	SubRedisValue RPUSHX(const std::string &key, const std::string &value);
	// List Section

	// Pub/Sub Section
	SubRedisValue PSUBSCRIBE(const std::string &pattern);
	SubRedisValue PSUBSCRIBE(
		const std::initializer_list<std::string> &patterns);
	SubRedisValue PSUBSCRIBE(std::vector<std::string> patterns);
	SubRedisValue PUBSUB(const std::string &subcommand);
	SubRedisValue PUBSUB(const std::string &subcommand,
						 const std::string &arguement);
	SubRedisValue PUBSUB(const std::string &subcommand,
						 const std::initializer_list<std::string> &arguements);
	SubRedisValue PUBSUB(const std::string &subcommand,
						 std::vector<std::string> arguements);
	SubRedisValue PUBLISH(const std::string &channel,
						  const std::string &message);
	SubRedisValue PUNSUBSCRIBE();
	SubRedisValue PUNSUBSCRIBE(const std::string &pattern);
	SubRedisValue PUNSUBSCRIBE(
		const std::initializer_list<std::string> &patterns);
	SubRedisValue PUNSUBSCRIBE(std::vector<std::string> patterns);
	SubRedisValue SUBSCRIBE(const std::string &channel);
	SubRedisValue SUBSCRIBE(const std::initializer_list<std::string> &channels);
	SubRedisValue SUBSCRIBE(std::vector<std::string> channels);
	SubRedisValue UNSUBSCRIBE();
	SubRedisValue UNSUBSCRIBE(const std::string &channel);
	SubRedisValue UNSUBSCRIBE(
		const std::initializer_list<std::string> &channels);
	SubRedisValue UNSUBSCRIBE(std::vector<std::string> channels);
	// Pub/Sub Section

	// Set Section
	SubRedisValue SADD(const std::string &key, const std::string &member);
	SubRedisValue SADD(const std::string &key,
					   const std::initializer_list<std::string> &members);
	SubRedisValue SADD(const std::string &key,
					   std::vector<std::string> members);
	SubRedisValue SCARD(const std::string &key);
	SubRedisValue SDIFF(const std::string &key);
	SubRedisValue SDIFF(const std::initializer_list<std::string> &keys);
	SubRedisValue SDIFF(std::vector<std::string> keys);
	SubRedisValue SDIFFSTORE(const std::string &destination,
							 const std::string &key);
	SubRedisValue SDIFFSTORE(const std::string &destination,
							 const std::initializer_list<std::string> &keys);
	SubRedisValue SDIFFSTORE(const std::string &destination,
							 std::vector<std::string> keys);
	SubRedisValue SINTER(const std::string &key);
	SubRedisValue SINTER(const std::initializer_list<std::string> &keys);
	SubRedisValue SINTER(std::vector<std::string> keys);
	SubRedisValue SINTERSTORE(const std::string &destination,
							  const std::string &key);
	SubRedisValue SINTERSTORE(const std::string &destination,
							  const std::initializer_list<std::string> &keys);
	SubRedisValue SINTERSTORE(const std::string &destination,
							  std::vector<std::string> keys);
	SubRedisValue SISMEMBER(const std::string &key, const std::string &member);
	SubRedisValue SMEMBERS(const std::string &key);
	SubRedisValue SMOVE(const std::string &source,
						const std::string &destination,
						const std::string &member);
	SubRedisValue SPOP(const std::string &key);
	SubRedisValue SPOP(const std::string &key, long count);
	SubRedisValue SRANDMEMBER(const std::string &key);
	SubRedisValue SRANDMEMBER(const std::string &key, long count);
	SubRedisValue SREM(const std::string &key, const std::string &member);
	SubRedisValue SREM(const std::string &key,
					   const std::initializer_list<std::string> &members);
	SubRedisValue SREM(const std::string &key,
					   std::vector<std::string> members);
	SubRedisValue SUNION(const std::string &key);
	SubRedisValue SUNION(const std::initializer_list<std::string> &keys);
	SubRedisValue SUNION(std::vector<std::string> keys);
	SubRedisValue SUNIONSTORE(const std::string &destination,
							  const std::string &key);
	SubRedisValue SUNIONSTORE(const std::string &destination,
							  const std::initializer_list<std::string> &keys);
	SubRedisValue SUNIONSTORE(const std::string &destination,
							  std::vector<std::string> keys);
	SubRedisValue SSCAN(const std::string &key, long cursor);
	SubRedisValue SSCAN(const std::string &key, long cursor,
						const std::string &pattern);
	SubRedisValue SSCAN(const std::string &key, long cursor, long count);
	SubRedisValue SSCAN(const std::string &key, long cursor,
						const std::string &pattern, long count);
	// Set Section

	// Transaction Section
	SubRedisValue DISCARD();
	SubRedisValue EXEC();
	SubRedisValue MULTI();
	SubRedisValue UNWATCH();
	SubRedisValue WATCH(const std::string &key);
	SubRedisValue WATCH(const std::initializer_list<std::string> &keys);
	SubRedisValue WATCH(std::vector<std::string> keys);
	// Transaction Section

	// String Section
	SubRedisValue APPEND(const std::string &key, const std::string &value);
	SubRedisValue BITCOUNT(const std::string &key);
	SubRedisValue BITCOUNT(const std::string &key, long start, long end);
	// Left out BITFIELD
	SubRedisValue BITOP(const std::string &operation,
						const std::string &destkey, const std::string &key);
	SubRedisValue BITOP(const std::string &operation,
						const std::string &destkey,
						const std::initializer_list<std::string> &keys);
	SubRedisValue BITOP(const std::string &operation,
						const std::string &destkey,
						std::vector<std::string> keys);
	SubRedisValue BITPOS(const std::string &key, long bit);
	SubRedisValue BITPOS(const std::string &key, long bit, long start);
	SubRedisValue BITPOS(const std::string &key, long bit, long start,
						 long end);
	SubRedisValue DECR(const std::string &key);
	SubRedisValue DECRBY(const std::string &key, long decrement);
	SubRedisValue GET(const std::string &key);
	SubRedisValue GETBIT(const std::string &key, long offset);
	SubRedisValue GETRANGE(const std::string &key, long start, long end);
	SubRedisValue GETSET(const std::string &key, const std::string &value);
	SubRedisValue INCR(const std::string &key);
	SubRedisValue INCRBY(const std::string &key, long increment);
	SubRedisValue INCRBYFLOAT(const std::string &key, double increment);
	SubRedisValue MGET(const std::string &key);
	SubRedisValue MGET(const std::initializer_list<std::string> &keys);
	SubRedisValue MGET(std::vector<std::string> keys);
	SubRedisValue MSET(const std::string &key, const std::string &value);
	SubRedisValue MSET(const std::map<std::string, std::string> &map);
	SubRedisValue MSETNX(const std::string &key, const std::string &value);
	SubRedisValue MSETNX(const std::map<std::string, std::string> &map);
	SubRedisValue PSETEX(const std::string &key, long milliseconds,
						 const std::string &value);
	SubRedisValue SET(const std::string &key, const std::string &value);
	// left out SET args
	SubRedisValue SETBIT(const std::string &key, long offset, bool value);
	SubRedisValue SETEX(const std::string &key, long seconds,
						const std::string &value);
	SubRedisValue SETNX(const std::string &key, const std::string &value);
	SubRedisValue SETRANGE(const std::string &key, long offset,
						   const std::string &value);
	SubRedisValue STRLEN(const std::string &key);
	// String Section

	// HyperLogLog Section
	SubRedisValue PFADD(const std::string &key, const std::string &element);
	SubRedisValue PFADD(const std::string &key,
						const std::initializer_list<std::string> &elements);
	SubRedisValue PFADD(const std::string &key,
						std::vector<std::string> elements);
	SubRedisValue PFCOUNT(const std::string &key);
	SubRedisValue PFCOUNT(const std::initializer_list<std::string> &keys);
	SubRedisValue PFCOUNT(std::vector<std::string> keys);
	SubRedisValue PFMERGE(const std::string &destkey,
						  const std::string &sourcekey);
	SubRedisValue PFMERGE(const std::string &destkey,
						  const std::initializer_list<std::string> &sourcekeys);
	SubRedisValue PFMERGE(const std::string &destkey,
						  std::vector<std::string> sourcekeys);
	// HyperLogLog Section

	// Geo Section
	SubRedisValue GEOADD(const std::string &key, double longitude,
						 double latitude, const std::string &member);
	// Left out GEOADD args
	SubRedisValue GEOHASH(const std::string &key, const std::string &member);
	SubRedisValue GEOHASH(const std::string &key,
						  const std::initializer_list<std::string> &members);
	SubRedisValue GEOHASH(const std::string &key,
						  std::vector<std::string> members);
	SubRedisValue GEOPOS(const std::string &key, const std::string &member);
	SubRedisValue GEOPOS(const std::string &key,
						 const std::initializer_list<std::string> &members);
	SubRedisValue GEOPOS(const std::string &key,
						 std::vector<std::string> members);
	SubRedisValue GEODIST(const std::string &key, const std::string &member1,
						  const std::string &member2);
	SubRedisValue GEODIST(const std::string &key, const std::string &member1,
						  const std::string &member2, const std::string &unit);
	// Left out GEORADIUS
	// Left out GEORADIUSBYMEMBER
	// Geo Section

	// Server Section
	SubRedisValue BGREWRITEAOF();
	SubRedisValue BGSAVE();
	SubRedisValue CLIENT_ID();
	// Left out CLIENT_KILL
	SubRedisValue CLIENT_LIST();
	SubRedisValue CLIENT_LIST(const std::string &type);
	SubRedisValue CLIENT_GETNAME();
	SubRedisValue CLIENT_PAUSE(long timeout);
	SubRedisValue CLIENT_REPLY(
		const std::string &arg);  // 给出OFF时，永久阻止
	SubRedisValue CLIENT_SETNAME(const std::string &connection_name);
	SubRedisValue CLIENT_UNBLOCK(long client_id);
	SubRedisValue CLIENT_UNBLOCK_TIMEOUT(long client_id);
	SubRedisValue CLIENT_UNBLOCK_ERROR(long client_id);
	SubRedisValue COMMAND();
	SubRedisValue COMMAND_COUNT();
	// left out COMMAND_GETKEYS
	SubRedisValue COMMAND_INFO(const std::string &command_name);
	SubRedisValue COMMAND_INFO(
		const std::initializer_list<std::string> &command_names);
	SubRedisValue COMMAND_INFO(std::vector<std::string> command_names);
	SubRedisValue CONFIG_GET(const std::string &parameter);
	SubRedisValue CONFIG_REWRITE();
	SubRedisValue CONFIG_SET(const std::string &parameter,
							 const std::string &value);
	SubRedisValue CONFIG_RESETSTAT();
	SubRedisValue DBSIZE();
	SubRedisValue DEBUG_OBJECT(const std::string &key);
	SubRedisValue DEBUG_SEGFAULT();
	SubRedisValue FLUSHALL();
	SubRedisValue FLUSHALL_ASYNC();
	SubRedisValue FLUSHDB();
	SubRedisValue FLUSHDB_ASYNC();
	SubRedisValue INFO();
	SubRedisValue INFO(const std::string &section);
	SubRedisValue LASTSAVE();
	SubRedisValue MEMORY_DOCTOR();
	SubRedisValue MEMORY_HELP();
	SubRedisValue MEMORY_MALLOC_STATS();
	SubRedisValue MEMORY_PURGE();
	SubRedisValue MEMORY_STATS();
	SubRedisValue MEMORY_USAGE(const std::string &key);
	SubRedisValue MEMORY_USAGE(const std::string &key, long count);
	SubRedisValue MONITOR();
	SubRedisValue ROLE();
	SubRedisValue SAVE();
	SubRedisValue SHUTDOWN();
	SubRedisValue SHUTDOWN(bool save);
	SubRedisValue SLAVEOF(const std::string &host, int port);
	SubRedisValue REPLICAOF(const std::string &host, int port);
	SubRedisValue SLOWLOG(const std::string &subcommand);
	SubRedisValue SLOWLOG(const std::string &subcommand,
						  const std::string &arguement);
	// left out SYNC();
	SubRedisValue TIME();
	// Server Section

	// Hashes Section
	SubRedisValue HDEL(const std::string &key, const std::string &field);
	SubRedisValue HDEL(const std::string &key,
					   const std::initializer_list<std::string> &fields);
	SubRedisValue HDEL(const std::string &key, std::vector<std::string> fields);
	SubRedisValue HEXISTS(const std::string &key, const std::string &field);
	SubRedisValue HGET(const std::string &key, const std::string &field);
	SubRedisValue HGETALL(const std::string &key);
	SubRedisValue HINCRBY(const std::string &key, const std::string &field,
						  long increment);
	SubRedisValue HINCRBYFLOAT(const std::string &key, const std::string &field,
							   double increment);
	SubRedisValue HKEYS(const std::string &key);
	SubRedisValue HLEN(const std::string &key);
	SubRedisValue HMGET(const std::string &key, const std::string &field);
	SubRedisValue HMGET(const std::string &key,
						const std::initializer_list<std::string> &fields);
	SubRedisValue HMGET(const std::string &key,
						std::vector<std::string> fields);
	SubRedisValue HMSET(const std::string &key, const std::string &field,
						const std::string &value);
	SubRedisValue HMSET(const std::string &key,
						const std::map<std::string, std::string> &map);
	SubRedisValue HSET(const std::string &key, const std::string &field,
					   const std::string &value);
	SubRedisValue HSETNX(const std::string &key, const std::string &field,
						 const std::string &value);
	SubRedisValue HSTRLEN(const std::string &key, const std::string &field);
	SubRedisValue HVALS(const std::string &key);
	SubRedisValue HSCAN(const std::string &key, long cursor);
	SubRedisValue HSCAN(const std::string &key, long cursor,
						const std::string &pattern);
	SubRedisValue HSCAN(const std::string &key, long cursor, long count);
	SubRedisValue HSCAN(const std::string &key, long cursor,
						const std::string &pattern, long count);
	// Hashes Section

	// Script Section
	SubRedisValue EVAL(const std::string &script, long numkeys,
					   const std::string &key, const std::string &arg);
	SubRedisValue EVAL(const std::string &script, long numkeys,
					   const std::initializer_list<std::string> &keys,
					   const std::initializer_list<std::string> &args);
	SubRedisValue EVAL(const std::string &script, long numkeys,
					   const std::vector<std::string> &keys,
					   const std::vector<std::string> &args);
	SubRedisValue EVALSHA(const std::string &sha1, long numkeys,
						  const std::string &key, const std::string &arg);
	SubRedisValue EVALSHA(const std::string &sha1, long numkeys,
						  const std::initializer_list<std::string> &keys,
						  const std::initializer_list<std::string> &args);
	SubRedisValue EVALSHA(const std::string &sha1, long numkeys,
						  const std::vector<std::string> &keys,
						  const std::vector<std::string> &args);
	SubRedisValue SCRIPT_DEBUG(const std::string &arg);
	SubRedisValue SCRIPT_EXISTS(const std::string &sha1);
	SubRedisValue SCRIPT_EXISTS(
		const std::initializer_list<std::string> &sha1s);
	SubRedisValue SCRIPT_EXISTS(std::vector<std::string> sha1s);
	SubRedisValue SCRIPT_FLUSH();
	SubRedisValue SCRIPT_KILL();
	SubRedisValue SCRIPT_LOAD(const std::string &script);
	// Script Section

	// Sorted Set Section
	SubRedisValue BZPOPMIN(const std::string &key, long timeout);
	SubRedisValue BZPOPMIN(const std::initializer_list<std::string> &keys,
						   long timeout);
	SubRedisValue BZPOPMIN(std::vector<std::string> keys, long timeout);
	SubRedisValue BZPOPMAX(const std::string &key, long timeout);
	SubRedisValue BZPOPMAX(const std::initializer_list<std::string> &keys,
						   long timeout);
	SubRedisValue BZPOPMAX(std::vector<std::string> keys, long timeout);
	SubRedisValue ZADD(const std::string &key, long score,
					   const std::string &member);
	// Left out ZADD args
	SubRedisValue ZCARD(const std::string &key);
	SubRedisValue ZCOUNT(const std::string &key, long min, long max);
	SubRedisValue ZINCRBY(const std::string &key, long increment,
						  const std::string &member);
	// Left out ZINTERSTORE
	// left out ZLEXCOUNT
	SubRedisValue ZPOPMAX(const std::string &key);
	SubRedisValue ZPOPMAX(const std::string &key, long count);
	SubRedisValue ZPOPMIN(const std::string &key, long count);
	SubRedisValue ZRANGE(const std::string &key, long start, long stop);
	SubRedisValue ZRANGE_WITHSCORES(const std::string &key, long start,
									long stop);
	// left out ZRANGEBYLEX
	// left out ZREVRANGEBYLEX
	// left out ZRANGEBYSCORE
	SubRedisValue ZRANK(const std::string &key, const std::string &member);
	SubRedisValue ZREM(const std::string &key, const std::string &member);
	SubRedisValue ZREM(const std::string &key,
					   const std::initializer_list<std::string> &members);
	SubRedisValue ZREM(const std::string &key,
					   std::vector<std::string> members);
	// left out ZREMRANGEBYLEX
	SubRedisValue ZREMRANGEBYRANK(const std::string &key, long start,
								  long stop);
	SubRedisValue ZREMRANGEBYSCORE(const std::string &key, long min, long max);
	SubRedisValue ZREVRANGE(const std::string &key, long start, long stop);
	SubRedisValue ZREVRANGE_WITHSCORES(const std::string &key, long start,
									   long stop);
	// lfet out ZREVRANGEBYSCORE
	SubRedisValue ZREVRANK(const std::string &key, const std::string &member);
	SubRedisValue ZSCORE(const std::string &key, const std::string &member);
	SubRedisValue ZSCAN(const std::string &key, long cursor);
	SubRedisValue ZSCAN(const std::string &key, long cursor,
						const std::string &pattern);
	SubRedisValue ZSCAN(const std::string &key, long cursor, long count);
	SubRedisValue ZSCAN(const std::string &key, long cursor,
						const std::string &pattern, long count);
};

#endif  // SUBREDIS_H
