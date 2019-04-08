# SubRedis
This is a C++11 library written on top of hiredis library. It is fast and makes it easier to use Redis in C++ with C++ data types. This library supports synchronous, asynchronous and thread-safe APIs and most of the Redis commands as helper functions for SubRedis class.

This project's dependencies are only hiredis and the STL library

# Installation
This project uses CMake. so the installation process is easy.

First you have to install hiredis. You can install hiredis from source. Some package managers also contain hiredis's development package. For example on Ubuntu:

``` shell
sudo apt install libhiredis-dev
```

Then you have to download SubRedis's source code and do the following inside the source dir:

``` shell
mkdir build
cd build
cmake ..
make
sudo make install
```

And that is it.


# Usage
Here are some examples of how to use this library.

## Synchronous API
### Connecting
This is a simple code that connects to a Redis server running on localhost:

``` c++
SubRedis R;
bool success = R.connect("127.0.0.1", 6379);
if (!success) cout << R.errorStr() << endl;
```

In case connect returns false you can check the error with R.error() and R.errorStr() functions.

### Commanding
There are two command functions. One takes a format string and other arguements and formats the string with it. Please note that you can not pass std::string as a format arguement. You can pass a char sequence instead. it you want to pass std::string you can use the second command function that takes a vector of strings and constructs the command with it. You can see examples of both here:

``` c++
// a command
R.command("SET foo bar");

// a formatted string command
R.command("SET %s %s", "foo", "bar");

// a vector of strings command
R.command({"SET", "foo", "bar"});

// a command using the helper functions
R.SET("foo", "bar");

auto reply = R.command("GET foo");
cout << reply << endl;

// if you are using std::string
std::string key = "foo";
std::string value = "bar";

// format function
R.command("SET", key.c_str(), value.c_str());

// string list function
R.command({"SET", key, value});
```

### Return Values
All of the returned values are of type SubRedisValue class. this class holds different types of replies:

``` c++
auto reply = R.command("GET foo");
if (reply.isString())
    cout << reply.string() << endl;
```

Type of replies can be Null when the reply is nil and Invalid when there is a client error or when you are using the helper functions in ModeAppend.

### Pipelining
You can also do pipelining with append() and getReply() functions:

``` c++
R.append("SET foo bar");
R.append("GET foo");

cout << R.getReply() << endl;
cout << R.getReply() << endl;
```

You can also use helper functions in append mode:

``` c++
R.setMode(SubRedis::ModeAppend);

R.SET("foo", "bar");
R.GET("foo");

cout << R.getReply() << endl;
cout << R.getReply() << endl;
```

## Asynchronous API
### Connecting
This is an example of connecting asynchronously to Redis with SubAsyncRedis class:

``` c++
SubAsyncRedis R;

R.setConnectCallBack([&R](bool success) {
	if (!success) cout << R.errorStr() << endl;
});

R.connect("127.0.0.1", 6379);
```

### Commanding
You can run commands asynchronously and set the callback function to capture the result:

``` c++
auto callback = [](const SubRedisValue &V) { cout << V << endl; };
R.command(callback, "SET foo bar");
```

### Disconnecting
You can disconnect asynchronously from Redis server with disconnect() function:
``` c++
R.setDisconnectCallBack([&R](bool success) {
	if (!success) cout << R.errorStr() << endl;
});

R.disconnect();
```

## Thread Safe API
You can also connect and run commands across multiple threads with SubSafeRedis class. One of the differences between SubRedis and SubSafeRedis APIs are that you can pass SubRedisErrorStruct to SubSafeRedis's command and connect function to capture the error.

### Connecting
You can use the connect function of SubSafeRedis class to connect to Redis server:

``` c++
SubSafeRedis R;
SubRedisErrorStruct S;

bool success = R.connect("127.0.0.1", 6379, &S);
if (!success) cout << S.errorStr << endl;
```

### Commanding
You can use the command function of SubSafeRedis class to command to Redis server:

``` c++
SubRedisErrorStruct S;
auto reply = R.command(&S, "SET foo bar");
cout << reply << endl;
```

### Disconnecting
You can use the disconnect function of SubSafeRedis class to disconnect from Redis server:

``` c++
R.disconnect();
```

You can see [examples](examples) directory for full examples.

、、