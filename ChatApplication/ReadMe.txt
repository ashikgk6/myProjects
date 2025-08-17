Changes Made:

Client Side:
-Added username field to TCPClient class
-Added setUsername() and getUsername() methods
-Modified connectToServer() to send username as the first message
-Added username prompt in the client run function

Server Side:
-Added a map to store client usernames
-Modified handleClient() to expect username as the first message
-Updated logging to show usernames with messages
-Added proper cleanup when clients disconnect

Protocol Change:
-Clients now send "USERNAME:username" as their first message
-Server expects this format to identify clients

How It Works Now:

When a client starts:
-It prompts for a username
-Connects to the server and sends the username first
-Then proceeds with normal messaging

The server:
-Receives the username first and stores it
-Displays messages with the username prefix
-Includes username in responses
-All communication now shows which user sent each message.

The client will now ask for a username before connecting, and all messages will be displayed with the username both on client and server sides.