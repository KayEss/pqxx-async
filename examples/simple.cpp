#include <felspar/io/warden.poll.hpp>
#include <pqxx/connection>

#include <iostream>


namespace {
    felspar::coro::task<pqxx::connection> do_connect(felspar::io::warden &ward) {
        std::cout << "Starting connection process..." << std::endl;
        pqxx::connecting cn;
        while (not cn.done()) {
            cn.process();
            if (cn.wait_to_read()) {
                std::cout << "Waiting for read..." << std::endl;
                co_await ward.read_ready(cn.sock());
            } else if (cn.wait_to_write()) {
                std::cout << "Waiting for write..." << std::endl;
                co_await ward.write_ready(cn.sock());
            }
        }
        std::cout << "Connected" << std::endl;
        co_return std::move(cn).produce();
    }


    felspar::coro::task<void> co_main(felspar::io::warden &ward) {
        auto cnx = co_await do_connect(ward);
    }
}


int main() {
    try {
        felspar::io::poll_warden ward;
        ward.run(co_main);
        return 0;
    } catch (std::exception const &e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
        return 1;
    }
}
