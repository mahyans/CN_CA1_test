#ifndef DEFINE_HEADER
#define DEFINE_HEADER

#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <dirent.h>
#include <cstdio>
#include <string>


#define SUCCESSFUL_ADD "104: Successfully added."
#define SUCCESSFUL_MODIFY "105: Successfully modefied."
#define SUCCESSFUL_DELETE "106: Successfully deleted."
#define ROOM_NOT_FOUND "101: The desired room was not found"
#define RESERVATIONN_NOT_FOUND "102: Your reservation was not found"
#define NOT_ENOUGH_MONEY "108: Your account balance is not enough"
#define ROMM_IS_FULL "109: The room capacity is full"
#define SUCCESSFUL "110: Successfully done."
#define ROOM_ALREADY_EXISTS "111: This room already exists."
#define SUCCESSFUL_LOGOUT "201: User logged out successfully."
#define SUCCESSFUL_LOGIN "230: User logged in."
#define SUCCESSFUL_SIGNUP "231: User successfully signed up."
#define ENTER_USER_DATA "311: User signed up. Enter your password, purse, phone and address."
#define SUCCESSFUL_CHANGE "312: Information was changed successfully."
#define INVALID_VAL "401: Invalid value!"
#define ACCESS_DENIED "403: Access denied!"
#define INVALID_CAPACITY "412: Invalid capacity value!"
#define SUCCESSFUL_LEAVING "413: Successfully leaving."
#define INVALID_USERNAME_PASS "430: Invalid username or password."
#define USER_ALREADY_EXIST "451: User already existed!"
#define BAD_COMMANDS "503: Bad sequence of commands."
#define BAD_ARGUMENT "500: BAD arguments."

#define SIGN_IN_COMMAND "signin"
#define SET_TIME_COMMAND "setTime"
#define PASS_DAY_COMMAND "passDay"
#define ROOM_COMMAND "room"
#define CAPACITY_COMMAND "capacity"
#define REMOVE_COMMAND "remove"
#define SIGN_UP_COMMAND "signup"
#define CANCLE_COMMAND "cancle"
#define BOOK_COMMAND "book"
#define ADD_COMMAND "add"
#define MODIFY_COMMAND "modify"
#define USER_DATA "userData"

#define VIEW_USER_INFO "1"
#define VIEW_ALL_USERS "2"
#define VIEW_ROOMS_INFO "3"
#define BOOKING "4"
#define CANCELING "5"
#define PASSDAY "6"
#define EDIT_INFO "7"
#define LEAVING_ROOM "8"
#define VIEW_ALL_ROOMS "9"
#define LOGOUT "0"


#define MAIN_PAGE "1. View user information\n2. View all users\n3. View rooms information\n4. Booking\n5. Canceling\n6. Pass day\n7.Edit information\n8.Leaving room\n9. Rooms\n0. Logout"
#define BUFFER_SIZE 1024
#define LOG_FILE_NAME "/configuration/log.txt"
#define SUCCESSFUL_QUIT "221: Successful Quit."
#define CANT_OPEN_DATA_CONNECTION "425: Can't open data connection."
#define SYNTAX_ERROR "501: Syntax error in parameters or arguments."
#define SUCCESSFUL_DOWNLOAD "226: Successful Download."

#define ERROR "500: Error"
#define LIST_TRANSFER_DONE "226: List transfer done."
#define FILE_UNAVAILABLE "550: File unavailable."
#define NEED_TO_LOGOUT "430: You need to log out first."
#define USERNAME_OK "331: User name ok, need password."
#define ALREADY_LOGGED_IN "430: User already logged in."
#define INVALID_LOGIN "430: Invalid username or password."

#define BAD_SEQUENCE "503: Bad sequence of commands."
#define SHOULD_LOGIN "332: Need account for login."

#define USER_COMMAND "user"
#define PASS_COMMAND "pass"
#define PWD_COMMAND "pwd"
#define MKD_COMMAND "mkd"
#define DELE_COMMAND "dele"
#define LS_COMMAND "ls"
#define CWD_COMMAND "cwd"
#define RENAME_COMMAND "rename"
#define RETR_COMMAND "retr"
#define HELP_COMMAND "help"
#define QUIT_COMMAND "quit"

#define CONFIG_FILE "configuration/config.json"
#define ROOMS_INFO_FILE "configuration/RoomsInfo.json"
#define USERS_INFO_FILE "configuration/UsersInfo.json"
#define COMMAND_PORT "commandChannelPort"
#define HOST "hostName"

#define COMMAND_CHANNEL_PORT "commandChannelPort"
#define DATA_CHANNEL_PORT "dataChannelPort"
#define CONFIG_ADMIN_FILES "files"
#define CONFIG_USER "user"
#define CONFIG_PASSWORD "password"
#define CONFIG_IS_ADMIN "admin"
#define CONFIG_SIZE "size"




#endif