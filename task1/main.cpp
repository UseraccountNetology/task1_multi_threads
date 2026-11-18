#include <iostream>
#include <thread>
#include <atomic>


//часть первая
using namespace std;

///
/// \brief value
///
std::atomic<int> value{0};

///
/// \brief Client_Add
/// \param count
///
void Client_Add(int count)
{
    for(int i=1;i<count;i++)
    {
        value+=i;
    }

}

///
/// \brief work_client
/// \param count
///
void work_client(int count)
{
    for(int i=1;i<count;i++)
    {
        this_thread::sleep_for(2s);
        value-=1;
    }
}


///
/// \brief main
/// \return
///
int main()
{

    //
    const int clients = 10;

    //
    std::thread client_thread(Client_Add,clients);

    //
    std::thread work_thread(work_client,clients);

    //
    client_thread.join();

    //
    work_thread.join();

    //
    std::cout<<value<<std::endl;

    //
    return 0;
}
