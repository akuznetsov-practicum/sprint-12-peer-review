#!/usr/bin/env python3

import argparse
import random

max_readers = 10 ** 5
max_pages = 10 ** 3
max_requests = 10 ** 6
max_read_step = 50
action_threshold = 0.35

readers = dict()

def GetReader(cmdargs):
    while(True):
        user_id = int(random.random() * cmdargs.readers) + 1
        page_read = int(random.random() * cmdargs.step) + 1
        action = random.random()

        if action > cmdargs.threshold:
            already_read_pages = readers.get(user_id, 0)

            if already_read_pages + page_read <= cmdargs.pages:
                readers[user_id] = already_read_pages + page_read

                return(action, user_id, already_read_pages + page_read)
        else:
            return(action, user_id, 0)

def generate(cmdargs):
    print(f"{cmdargs.requests}")

    for i in range(0, cmdargs.requests):
        (action, user_id, page_no) = GetReader(cmdargs)

        if action > cmdargs.threshold:
            print(f"READ {user_id} {page_no}")
        else:
            print(f"CHEER {user_id}")

def main():
    cmdargparser = argparse.ArgumentParser("testgen")

    cmdargparser.add_argument("requests", nargs="?", help="Requests number (default: %(default)i)", type=int, default=max_requests)
    cmdargparser.add_argument("readers", nargs="?", help="Number of readers (default: %(default)i)", type=int, default=max_readers)
    cmdargparser.add_argument("pages", nargs="?", help="Max page numbers (default: %(default)i)", type=int, default=max_pages)
    cmdargparser.add_argument("step", nargs="?", help="Maximum read step, pages (default: %(default)i)", type=int, default=max_read_step)
    cmdargparser.add_argument("threshold", nargs="?", help="Action threshold (default: %(default)f)", type=float, default=action_threshold)

    cmdargs = cmdargparser.parse_args()

    generate(cmdargs)

if __name__ == "__main__":
    main()
