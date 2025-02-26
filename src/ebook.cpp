#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

class EBook {
private:
    std::vector<int> reader;
    std::vector<int> page;
    int num_of_readers;

public:
    static const size_t max_readers = 100'000;
    static const size_t max_pages = 1'000;

    EBook()
        : reader(max_readers + 1u, -1)
        , page(max_pages + 1u, 0)
        , num_of_readers(0)
        {}

    void SetPage(const int user_id, const int page_no) {
        const int reader_prev_page = reader[user_id];

        // Check if it is a first update for the reader
        if(reader_prev_page < 0) {
            ++num_of_readers;
        }

        // Update read pages counters
        for(int i = reader_prev_page + 1; i <= page_no; ++i) {
            ++page[i];
        }

        // Save reader's last page
        reader[user_id] = page_no;
    }

    double GetCheer(const int user_id) {
        // Check if there are no readers yet or the user has not started to read yet
        if(num_of_readers == 0 || reader[user_id] < 0) {
            return 0.0;
        }

        // Check if the reader is the only reader
        if(num_of_readers == 1) {
            return 1.0;
        }

        return static_cast<double>(num_of_readers - page[reader[user_id]])
            / static_cast<double>(num_of_readers - 1);
    }
};

void ProcessCommands(std::istream& in) {
    EBook ebook;

    int num_commands = 0;
    in >> num_commands;

    for(int i = 0; i < num_commands; ++i) {
        std::string command;
        int user_id = 0;
        int page_no = 0;

        in >> command >> user_id;

        if(command == "READ") {
            in >> page_no;

            ebook.SetPage(user_id, page_no);
        }
        else if(command == "CHEER") {
            std::cout << std::setprecision(6) << ebook.GetCheer(user_id) << std::endl;
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
