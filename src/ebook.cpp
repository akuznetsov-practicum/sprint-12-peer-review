#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

const size_t max_readers = 100'000;
const size_t max_pages = 1'000;

struct Context {
    std::vector<int> reader;
    std::vector<int> page;
    int num_of_readers;

    Context(const int max_readers, const int max_pages)
        : reader(max_readers + 1u, -1)
        , page(max_pages + 1u, 0)
        , num_of_readers(0)
        {}
};

template<typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& v) {
    size_t n = 0;

    for(typename std::vector<T>::const_iterator i = v.begin(); i != v.end(); ++i) {
        o << " " << n << ":" << *i;
        ++n;
    }

    return o;
}

void SetPage(Context& ctx, const int user_id, const int page_no) {
    const int reader_prev_page = ctx.reader[user_id];

    // Check if it is a first update for the reader
    if(reader_prev_page < 0) {
        ++ctx.num_of_readers;
    }

    // Update read pages counters
    for(int i = reader_prev_page + 1; i <= page_no; ++i) {
        ++ctx.page[i];
    }

    // Save reader's last page
    ctx.reader[user_id] = page_no;
}

double GetCheer(Context& ctx, const int user_id) {
    if(ctx.num_of_readers == 0 || ctx.reader[user_id] < 0) {
        // There are no readers yet or the user has not started to read yet
        return 0.0;
    }

    if(ctx.num_of_readers == 1) {
        // The reader is the only reader
        return 1.0;
    }

    const int users_no_read_till_page = ctx.page[ctx.reader[user_id]];

    return static_cast<double>(ctx.num_of_readers - users_no_read_till_page)
        / static_cast<double>(ctx.num_of_readers - 1);
}

void ProcessCommands(std::istream& in) {
    Context ctx(max_readers, max_pages);

    int num_commands = 0;
    in >> num_commands;

    for(int i = 0; i < num_commands; ++i) {
        std::string command;
        int user_id = 0;
        int page_no = 0;

        in >> command >> user_id;

        if(command == "READ") {
            in >> page_no;

            SetPage(ctx, user_id, page_no);
        }
        else if(command == "CHEER") {
            std::cout << std::setprecision(6) << GetCheer(ctx, user_id) << std::endl;
        }
        else {
            std::cout << "ERROR: Unknown command [" << command << "]" << std::endl;
        }
    }
}

int main() {
    ProcessCommands(std::cin);

    return 0;
}
