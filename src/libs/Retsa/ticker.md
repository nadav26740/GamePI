# ticker.hpp Documentation

This file defines the `Ticker` class in the `Resta` namespace, which provides a timeline control mechanism for executing functions at regular intervals using a dedicated thread.

---

## Time Scale

- **Time Unit:** The ticker uses `std::chrono::milliseconds` as its default time unit.
- **Macro:** `DEFAULT_TIME_TYPE_TICKER` sets the time scale for all ticker operations.

---

## Class: `Resta::Ticker`

### Purpose

Manages a clock thread that repeatedly executes a list of functions at a specified interval. Useful for game loops, periodic updates, or timed events.

---

### Key Members

- **m_Running:** Indicates if the ticker is currently running.
- **m_Force_Stop_Flag:** Used to forcefully stop the ticker thread.
- **interval:** Minimum time between ticks (default: 2 milliseconds).
- **m_delta_time:** Time elapsed since the last tick.
- **m_clock:** Unique pointer to the clock thread.
- **m_functions_list:** List of function pointers to execute each tick.
- **m_function_list_mutex:** Mutex for thread-safe access to the function list.

---

### Main Methods

#### Timeline Control

- **Start():** Starts the ticker thread.
- **Stop():** Stops the ticker gracefully.
- **ForceStop():** Forcefully stops the ticker thread (not recommended).

#### Function List Management

- **AddFunction(void (*)(DEFAULT_TIME_TYPE_TICKER)):** Adds a function to the tick queue.  
  *Function signature must be:* `void func(DEFAULT_TIME_TYPE_TICKER deltatime)`
- **RemoveFunction(void (*)(DEFAULT_TIME_TYPE_TICKER)):** Removes a function by pointer. Throws if not found.
- **RemoveFunction(int index):** Removes a function by index. Throws if out of range.

#### Interval & Status

- **GetInterval():** Returns the minimal time between ticks.
- **GetTickerStatus():** Returns whether the ticker is running.
- **SetInterval(DEFAULT_TIME_TYPE_TICKER):** Sets the tick interval.

---

### Threading

- The ticker runs its own thread (`m_clock`) and uses a mutex to protect the function list.
- Functions are executed in each tick, and the thread sleeps until the next scheduled tick.

---

### Usage Notes

- **Thread Safety:** All modifications to the function list are mutex-protected.
- **Function Signature:** Functions added must accept a single parameter of type `DEFAULT_TIME_TYPE_TICKER`.
- **Destruction:** The destructor forcefully stops the ticker thread.

---

### Example Usage

```cpp
Resta::Ticker ticker;
ticker.AddFunction(myTickFunction);
ticker.Start();
// ...
ticker.Stop();
```

---

### Warnings & Recommendations

- **ForceStop:** Not recommended; use `Stop()` for graceful shutdown.
- **RemoveFunction:** Throws exceptions if the function or index is not found.
- **Thread Support:** Warns if hardware concurrency is zero or less.

---

## License

No license information is provided in this file.

---

*This documentation is auto-generated from code comments and structure in ticker.hpp.*