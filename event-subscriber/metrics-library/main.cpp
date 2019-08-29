
#include "Metrics.hpp"
#include <sys/time.h>

int main()
{
    hdbpp_metrics::EventRecorder r("log.txt");

    r.init();

    struct timeval tv{};
    gettimeofday(&tv, nullptr);

    std::chrono::milliseconds timespan(1000);
    std::this_thread::sleep_for(timespan);

    std::cout << tv.tv_sec << " " << tv.tv_usec << std::endl;
    std::cout << hdbpp_metrics::MetricsUtils::timevalToMicroSec(tv.tv_sec, tv.tv_usec) << std::endl;

    r.recordEvent("hello", hdbpp_metrics::MetricsUtils::nowInMiliSec(), "sdsds", 1000);
    r.recordEvent("hello", hdbpp_metrics::MetricsUtils::nowInMiliSec());
    r.recordEvent("hello", hdbpp_metrics::MetricsUtils::timevalToMiliSec(tv.tv_sec, tv.tv_usec));
    r.recordEvent("bye");



    std::this_thread::sleep_for(timespan);

    r.destroy();

    return 0;
}