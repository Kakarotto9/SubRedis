#include <subredis/subredis.h>
#include <iostream>

using namespace std;

int main()
{
	SubRedis R;
    bool success = R.connect("127.0.0.1", 6379);
    if (!success) cout << R.errorStr() << endl;

    R.append("SET foo bar");
    R.append("GET foo");

    cout << R.getReply() << endl;
    cout << R.getReply() << endl;

	R.setMode(SubRedis::ModeAppend);

    R.SET("foo", "bar");
    R.GET("foo");

    cout << R.getReply() << endl;
    cout << R.getReply() << endl;

    R.disconnect();
}
