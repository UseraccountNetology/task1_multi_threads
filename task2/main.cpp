#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <random>
#include <chrono>
#include <ctime>
#include <functional>
#include <map>

using namespace std;

//массив потоков
int *massive_thread = new int[1,2,4,8,16];

//массив данных
int *massive_data = new int[1'000,10'000,100'000,1'000'000];

//
struct vector_point{

    vector_point(int x_,int y_):x(x_),y(y_){};

    int x;
    int y;

};

//результат работы программы
struct Result
{
    Result(int number_thread_,int massive_data_,double time_):number_thread(number_thread_),massive_data(massive_data_),time(time_){};

    //номер потока
    int number_thread=0;

    //массив записей
    int massive_data;

    //время
    double time;
};



//рандомная генерация данных привязанных ко времени
int generate_data()
{
    std::time_t t = std::time(nullptr);

    unsigned seed = static_cast<unsigned>(t);

    std::mt19937 merser(seed);


    std::uniform_int_distribution<int> dist(1,20);

    //
    return dist(merser);
}

//сумма векторов
void sum_vector(std::vector<vector_point> vector_list)
{
    int  x=0;
    int  y =0;

    //
    for(int i=0;i<vector_list.size();i++)
    {
        x += vector_list[i].x;
        y += vector_list[i].y;
    }
}



//добавление данных в массив
///
/// \brief input_data_massive
/// \param value количество данных
/// \return
///
std::vector<vector_point> input_data_massive(int value)
{
    std::vector<vector_point> vector_points;

    //
    for(int i=0;i<value;i++)
    {
        //
        vector_points.emplace_back(vector_point(generate_data(),generate_data()));
    }

    //
    return vector_points;

}

//создание массива потоков
std::vector<std::thread> generate_vector_list(int count/*количество*/,
                                              std::function<void(std::vector<vector_point>)> func/**/,
                                              std::vector<vector_point> list_vector)
{
    std::vector<std::thread> list;


    for(int i=0;i<count;i++)
    {
        list.push_back(std::thread(func,list_vector));
    }

    //
    return list;
}

//реализация массива массива threads
void massive_threads(std::vector<std::thread> list)
{

    for(int i=0;i<list.size();i++)
    {
        list[i].join();
    }
}

//отображение данных
void show_data(int number_thread /*номер потока*/,
               std::vector<int> massive_data/*массив записей*/,
               std::vector<double> time /*время*/)
{

    std::cout<<"\t"<<massive_data[0]<<"\t"<<massive_data[1]<<"\t"<<
        massive_data[2]<<"\t"<<massive_data[3]<<endl;

    std::cout<<number_thread<<"потоков"<<time[0]<<"s"<<"\t"<<
        time[1]<<"\t"<<"s"<<time[2]<<"s"<<"\t"<<time[3]<<"s"<<"\t"<<endl;

}

//принимает данные для теста принимает одно
Result test(int number_data)
{
    //начало
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<vector_point> vector_list_points;

    auto vector_points_list_0 = input_data_massive(massive_data[value]);

    //список векторов
    auto thread_list= generate_vector_list(massive_thread[0],sum_vector,vector_points_list_0);

    //join векторов
    massive_threads(thread_list);

    //конец
    auto end = std::chrono::high_resolution_clock::now();

    //от начала до конца
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    //
    return Result(massive_thread[0],massive_data[value],duration.count());
}




//точка входа в программу
int main()
{

    //переделать данные
    auto value = test(0);


    //отобразить данные
    show_data(value);




    //
    delete [] massive_data;
    delete [] massive_thread;

    //
    return 0;
}
