#pragma once

#ifndef TICKER_HPP
#define TICKER_HPP
#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include <mutex>
#include <chrono>

// if u want to change the time scale change it here!
#define DEFAULT_TIME_TYPE_TICKER std::chrono::milliseconds

namespace Resta
{
    class Ticker
    {
    protected:
        /// @brief For timeline control so we will be able to stop and start the methood
        bool m_Running = false;
        bool m_Force_Stop_Flag = false;

        /// @brief the minimum time between ticks
        DEFAULT_TIME_TYPE_TICKER interval = DEFAULT_TIME_TYPE_TICKER(2);

        /// @brief The time past since the last tick started
        DEFAULT_TIME_TYPE_TICKER m_delta_time = DEFAULT_TIME_TYPE_TICKER(0);

        /// @brief That's the main clock thread!
        virtual void Clock();

    private:
        /// @brief Clock is the main thread here it will run on the queue of items
        std::unique_ptr<std::thread> m_clock;

        // List of function to run in every tick
        std::vector<void (*)(DEFAULT_TIME_TYPE_TICKER)> m_functions_list;
        std::mutex m_function_list_mutex;

    public:
        /// @brief default construtctor that will create a clock without a minimal time per tick
        Ticker();

        /// @brief Constructor that will create the object with minimal time per tick
        /// @param t_minimal_time_per_tick paramater that will hold the time minimal times between ticks
        Ticker(DEFAULT_TIME_TYPE_TICKER t_minimal_time_per_tick);

        // destructor will crush the clock thread
        ~Ticker();

        // ======== Timeline Methoods ========

        /// @brief will make the current ticker rotation his last
        virtual void Stop();

        /// @brief Will start the ticker thread
        virtual void Start();

        /// @brief Will make the ticker to stop immidetily buy crashing the thread (Not recommanded!)
        virtual void ForceStop();

        // ===================================

        // ==== control list methoods ====

        /// @brief Adding new function to the function queue
        /// @param func Function pointer to the new function
        /// @attention function need to be in this standart: void <function name>(time_t deltatime)
        /// ? Where "deltatime" is the time gap from last running
        void AddFunction(void (*t_func)(DEFAULT_TIME_TYPE_TICKER));

        /// @brief Will search for function with the same ptr in the list and try to remove it
        /// @param t_func Function to search
        /// @warning If function hasn't found throw exception
        /// @version Unstable
        void RemoveFunction(void (*t_func)(DEFAULT_TIME_TYPE_TICKER));

        /// @brief Removing function using his index the list
        /// @param index index of element to remove
        void RemoveFunction(const int index);

        /// @brief Returning the minimal time between ticks
        /// @return std::time_t type that represent the minimal time between ticks
        virtual DEFAULT_TIME_TYPE_TICKER GetInterval() const noexcept;

        /// @brief Returning if Clock Still running
        /// @return Bool type that represent the status of the clock
        virtual bool GetTickerStatus() const noexcept;

        void SetInterval(DEFAULT_TIME_TYPE_TICKER time_per_tick) noexcept;
    };

    
Ticker::Ticker()
{
    if (std::thread::hardware_concurrency() <= 0)
    {
        std::cerr << "Warning: Concurrent threads supported is 0 or lower" << std::endl;
    }
}

Ticker::Ticker(DEFAULT_TIME_TYPE_TICKER t_minimal_time_per_tick)
{
    interval = t_minimal_time_per_tick;
}

Ticker::~Ticker()
{
    ForceStop();
}

void Ticker::Stop()
{
    m_Running = false;
    if (m_clock->joinable())
        m_clock->join();
}

void Ticker::Start()
{
    m_Running = true;
    m_clock = std::make_unique<std::thread>(&Ticker::Clock, this);
}

void Ticker::ForceStop()
{
    std::thread *clock = m_clock.release();
    m_Running = false;
    m_Force_Stop_Flag = false;

    if (clock->joinable())
        clock->join();

    delete clock;
}

void Ticker::Clock()
{
    std::chrono::steady_clock::time_point t_point;
    DEFAULT_TIME_TYPE_TICKER delay_timer;

    while (m_Running && !m_Force_Stop_Flag)
    {
        // m_delta_time = std::chrono::duration_cast<DEFAULT_TIME_TYPE_TICKER>(std::chrono::high_resolution_clock::now() - t_point);
        t_point = interval + std::chrono::steady_clock::now();
        // getting all the function ptrs into the list
        while (!m_function_list_mutex.try_lock())
        {
            // checking if force stop flag is up
            if (m_Force_Stop_Flag)
                return;
        }
        for (auto func_ptr : m_functions_list)
        {
            func_ptr(m_delta_time);
        }
        m_function_list_mutex.unlock();

        // getting the amount of time that has passed since the loop started
        std::this_thread::sleep_until(t_point);
    }
}

void Ticker::AddFunction(void (*t_func)(DEFAULT_TIME_TYPE_TICKER))
{
    m_function_list_mutex.lock();
    m_functions_list.push_back(t_func);
    m_function_list_mutex.unlock();
}

void Ticker::RemoveFunction(void (*t_func)(DEFAULT_TIME_TYPE_TICKER))
{
    std::vector<void (*)(DEFAULT_TIME_TYPE_TICKER)>::iterator func_vec_itr = m_functions_list.begin();
    m_function_list_mutex.lock();
    while (func_vec_itr != m_functions_list.end())
    {
        if (*func_vec_itr == t_func)
        {
            m_functions_list.erase(func_vec_itr);
        }
    }
    m_function_list_mutex.unlock();
    throw std::out_of_range("the function hasn't been found in the list");
}

void Ticker::RemoveFunction(const int t_index)
{
    std::vector<void (*)(DEFAULT_TIME_TYPE_TICKER)>::iterator func_vec_itr = m_functions_list.begin();

    m_function_list_mutex.lock();
    if (t_index >= m_functions_list.size())
    {
        m_function_list_mutex.unlock();
        throw std::out_of_range("Index out of range");
    }

    func_vec_itr += t_index;
    m_functions_list.erase(func_vec_itr);
    m_function_list_mutex.unlock();
}

DEFAULT_TIME_TYPE_TICKER Ticker::GetInterval() const noexcept
{
    return interval;
}

bool Ticker::GetTickerStatus() const noexcept
{
    return m_Running;
}

void Ticker::SetInterval(DEFAULT_TIME_TYPE_TICKER time_per_tick) noexcept
{
    this->interval = time_per_tick;
}

}
#endif