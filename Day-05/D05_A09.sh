#!/bin/bash

# Function to find users logged in and their login times
logged_in_users() {
    if who | grep -q .; then
        echo "Users logged into the system with login time:"
        who | awk '{print "User: "$1", Login Time: "$3" "$4}'
    else
        echo "No users are currently logged into the system."
    fi
}

logged_in_users
