#include <iostream>
#include <csignal>

class SignalHandler {
public:
    static SignalHandler& instance()
    {
        static SignalHandler sh;
        return sh;
    }

    bool goodSig() const
    {
        return sig_ == 0;
    }

private:

    SignalHandler()
    {
        std::signal(SIGINT, SignalHandler::sigHandler);
    }

    static void sigHandler(int signal)
    {
        if (signal == SIGINT) {
            std::cout << "SIGINT occurred" << std::endl;
        }
        sig_ = signal;
    }

private:
    static volatile std::sig_atomic_t sig_;
};

volatile std::sig_atomic_t SignalHandler::sig_ = 0;

int main()
{
   auto i = SignalHandler::instance();
   std::cout << std::boolalpha << i.goodSig() << std::endl;
   std::raise(SIGINT);
   std::cout << std::boolalpha << i.goodSig() << std::endl;
}
