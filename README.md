# About The Project
![screenshot](https://www.onsip.com/hs-fs/hub/516769/file-3082154394-png/blog-files/adiumui.png)

This is IRC-Server written on C++ language using standart of RFC1459. This allows you to connect to the server by netcat or any instant messaging client that supports multiple IM networks (Adium for example)

# Getting started
## Installation ⚙️
1. Clone the repo
```
git clone https://github.com/divinepet/irc_server
```
2. Compile the project
```
make
```
3. Launch the server passing Port and Password for the server as a parameters
```
./ircserv 8000 1234
```
# Usage
## Connection 🔌
Now, you need to connect to the server. You can use <b>netcat</b> passing the server-ip and port in arguments like: nc localhost 8000</br>
If you are using Adium, you need to choose Irc-Server, create new client and fill out all the fields of the server settings
## Registration 🔑
With nc client you should write three comamnds: </br>PASS \<server password\></br>NICK \<your nickname\></br>USER \<name\> \<host\> \<servername\> \<realname\> (this values can be anything, it doesn't matter).
## Messaging ✉️
To write someone a message, use command PRIVMSG <receiver> <message>.</br><b>⚠️ Important:</b> if you want to send more than 1 word to client, use <b>:</b> before the message. For example:</br>
PRIVMSG john :hello there!</br>
Other commands and usage can be find by the link:
https://datatracker.ietf.org/doc/html/rfc1459
