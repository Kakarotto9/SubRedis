#include <subredis/subsaferedis.h>
#include <iostream>

using namespace std;

int main()
{
	SubSafeRedis R;
	SubRedisErrorStruct S;

    bool success = R.connect("127.0.0.1", 6379, &S);
    if (!success) cout << S.errorStr << endl;

    auto reply = R.command(&S, "SET foo bar");
    if (reply.isInvalid()) cout << S.errorStr << endl;
    cout << reply << endl;

    R.disconnect();
}
