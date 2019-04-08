#include <subredis/subredis.h>
#include <iostream>

using namespace std;

int main()
{
	SubRedis R;
    bool success = R.connect("127.0.0.1", 6379);
    if (!success) cout << R.errorStr() << endl;

    R.command("SET foo bar");

    // a formatted string command
    R.command("SET %s %s", "foo", "bar");

    // a vector of strings command
    R.command({"SET", "foo", "bar"});

    // a command using the helper functions
    R.SET("foo", "bar");

    auto reply = R.command("GET foo");
    cout << reply << endl;

    R.disconnect();
}
