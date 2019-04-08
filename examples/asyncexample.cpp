#include <subredis/subasyncredis.h>
#include <hiredis/adapters/libev.h>
#include <iostream>

using namespace std;

int main()
{
	signal(SIGPIPE, SIG_IGN);

	SubAsyncRedis R;

	R.setConnectCallBack([&R](bool success) {
		cout << success << endl;
		if (!success) cout << R.errorStr() << endl;
	});

	R.connect("127.0.0.1", 6379);

	redisLibevAttach(EV_DEFAULT_ R.context());

	auto callback = [&R](const SubRedisValue &V) {
		R.disconnect();
		cout << V << endl;
	};
	R.command(callback, "SET foo bar");

	R.setDisconnectCallBack([&R](bool success) {
		cout << success << endl;
		if (!success) cout << R.errorStr() << endl;
	});

	ev_loop(EV_DEFAULT_ 0);
	return 0;
}
