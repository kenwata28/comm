#include "IconDisplayer.h"
#include <windows.h>
#include <time.h>
class ThreadData
{
public:
    ThreadData() : idis{nullptr}, interval{100} {}

    IconDisplayer *idis;
    int interval;

private:
};

DWORD WINAPI DisplayRunning(LPVOID input_data)
{
    auto data = static_cast<ThreadData *>(input_data);

    while (true)
    {
        data->idis->Notify();
        Sleep(data->interval); // change event by event
    }
}
