#include <iostream>
#include <mutex>
#include <cstdlib>

template <typename T>
struct DefaultCreationPolicy
{
    static T *Create()
    {
        return new T();
    }
    static void Destroy(T *p)
    {
        delete p;
    }
};

template <typename T>
struct DefaultLifetimePolicy
{
    static void ScheduleDestruction(T *, void (*pFun)())
    {
        std::atexit(pFun);
    }
    static void OnDeadReference()
    {
    }
};

template <typename T>
struct SingleThreaded
{
    class Lock
    {
    public:
        Lock() {}
        ~Lock() {}
    };
};

template <typename T>
struct MultiThreaded
{
    class Lock
    {
    public:
        Lock()
        {
            mutex_.lock();
        }
        ~Lock()
        {
            mutex_.unlock();
        }

    private:
        static std::mutex mutex_;
    };
};

template <typename T>
std::mutex MultiThreaded<T>::Lock::mutex_;

template <typename T,
          template <typename> class CreationPolicy = DefaultCreationPolicy,
          template <typename> class LifetimePolicy = DefaultLifetimePolicy,
          template <typename> class ThreadingModel = SingleThreaded>
class SingletonHolder
{
public:
    static T &Instance()
    {
        if (!pInstance_)
        {
            typename ThreadingModel<T>::Lock guard;
            if (!pInstance_)
            {
                if (destroyed_)
                {
                    LifetimePolicy<T>::OnDeadReference();
                    destroyed_ = false;
                }
                pInstance_ = CreationPolicy<T>::Create();
                LifetimePolicy<T>::ScheduleDestruction(pInstance_, &DestroySingleton);
            }
        }
        return *pInstance_;
    }

private:
    static void DestroySingleton()
    {
        CreationPolicy<T>::Destroy(pInstance_);
        pInstance_ = nullptr;
        destroyed_ = true;
    }

    static T *pInstance_;
    static bool destroyed_;
};

template <typename T, template <typename> class CP, template <typename> class LP, template <typename> class TM>
T *SingletonHolder<T, CP, LP, TM>::pInstance_ = nullptr;

template <typename T, template <typename> class CP, template <typename> class LP, template <typename> class TM>
bool SingletonHolder<T, CP, LP, TM>::destroyed_ = false;

class MyClass
{
public:
    void SayHello()
    {
        std::cout << "Hello from Singleton!\n";
    }
};

typedef SingletonHolder<MyClass, DefaultCreationPolicy, DefaultLifetimePolicy, MultiThreaded> MySingleton;

int main()
{
    MyClass &instance = MySingleton::Instance();
    instance.SayHello();
    return 0;
}