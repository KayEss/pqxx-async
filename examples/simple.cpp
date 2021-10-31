#include <felspar/poll/executor.hpp>
#include <pqxx/connection>

#include <iostream>


namespace {
    felspar::coro::task<pqxx::connection>
            do_connect(felspar::poll::executor &exec) {
        std::cout << "Starting connection process..." << std::endl;
        pqxx::connecting cn;
        while (not cn.done()) {
            cn.process();
            if (cn.wait_to_read()) {
                std::cout << "Waiting for read..." << std::endl;
                co_await exec.read(cn.sock());
            } else if (cn.wait_to_write()) {
                std::cout << "Waiting for write..." << std::endl;
                co_await exec.write(cn.sock());
            }
        }
        std::cout << "Connected" << std::endl;
        co_return cn.produce();
    }


    felspar::coro::task<void> co_main(felspar::poll::executor &exec) {
        auto cnx = co_await do_connect(exec);
    }
}


int main() {
    try {
        felspar::poll::executor exec;
        exec.run(co_main);
        return 0;
    } catch (std::exception const &e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
        return 1;
    }
}
