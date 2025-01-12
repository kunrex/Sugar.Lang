#ifndef SINGLETON_SERVICE_H
#define SINGLETON_SERVICE_H

namespace Services
{
    template <class TSingleton>
    class SingletonService
    {
        protected:
            SingletonService();
            virtual ~SingletonService();

        public:
            static TSingleton& Instance();
            void DestroyInstance() const;

            SingletonService(const SingletonService&) = delete;
            SingletonService& operator=(const SingletonService&) = delete;
            SingletonService(SingletonService&&) = delete;
            SingletonService& operator=(SingletonService&&) = delete;
    };
}

#endif
