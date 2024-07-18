#include "./rethrow.h"
#include <stdexcept>

const std::set<std::string> db_conn::blacklist_ = {"hsmith"};

auto db_conn::try_connect(const std::string &uname, const std::string &pword) -> void {
    ++n_attempts_;

    if (blacklist_.contains(uname)) {
        throw std::domain_error( uname + "is not allowed to login.");
    }

    if (n_attempts_ % 2 == 0) {
        throw std::runtime_error("HeLp ;_; c0mpu73R c@ann0T c0mPut3 0w0");
    }

    if (pword.length() >= 8) {
        active_ = true;
    }
}

auto db_conn::is_active() const -> bool {
    return active_;
}

auto make_connection(db_conn &db, const std::string &uname, const std::string &pword) -> void {
    try {
        db.try_connect(uname, pword);
    } catch (std::exception& e) {
        throw std::string(e.what());
    }
}

