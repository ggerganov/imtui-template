#!/bin/bash

rm raw-all

# list of log URLs:
urls=(
    https://freenode.logbot.info/rust-embedded/20210217/raw
    https://freenode.logbot.info/gitlab/20210423/raw
    https://freenode.logbot.info/gitlab/20210202/raw
)

for url in "${urls[@]}" ; do
    wget $url -O raw > /dev/null 2>&1
    cat raw >> raw-all
done

# message format (one per line):
# 21:52:26 <username> but maybe that's too much?

echo "#pragma once"
echo ""
echo "#include <string>"
echo "#include <vector>"
echo ""
echo "struct Log {"
echo "    std::string username;"
echo "    std::string text;"
echo "};"
echo ""
echo "const std::vector<Log> kLogs = {"

cat raw-all | grep "^[0-9][0-9]:[0-9][0-9]:[0-9][0-9] <" | while read line; do
    username=$(echo $line | cut -d '<' -f 2 | cut -d '>' -f 1)
    msg=$(echo $line | sed -e 's/^[0-9][0-9]:[0-9][0-9]:[0-9][0-9] <.*> //' | sed -e 's/[a-zA-z0-9_]*: //')
    echo "    { \"$username\", R\"foo($msg)foo\" },"
done

echo "};"
