# TCP Chat Application (Eclipse Project)

A multi-client chat application with thread pooling, implemented in C++ using TCP sockets and Eclipse IDE.

## Project Structure

- **client/** - Client implementation
  - `client.cpp` - Client source code
  - `client.h` - Client header file
- **server/** - Server implementation
  - `server.cpp` - Server source code
  - `server.h` - Server header file
- **common/** - Shared utilities
  - `socket_utils.cpp` - Socket wrapper implementation
  - `socket_utils.h` - Socket wrapper interface
  - `thread_pool.cpp` - Thread pool implementation
  - `thread_pool.h` - Thread pool interface
- **src/**
  - `ChatApplication.cpp` - Main application entry point
- Eclipse project files
  - `.project`
  - `.cproject`


## Key Features

- Multi-client server with configurable thread pool
- Username identification for clients
- Object-oriented design with clean separation
- Eclipse IDE project ready
- Cross-platform (Windows/Linux/macOS)

## Eclipse Setup Instructions

1. **Import Project**:
   - Open Eclipse IDE
   - File → Import → Git → Projects from Git
   - Select "Clone URI" and enter your repository URL
   - Finish the import wizard

2. **Configure Build Settings**:
   - Right-click project → Properties
   - C/C++ Build → Settings:
     - Tool Settings → GCC C++ Compiler → Includes
       - Add all include paths (`client/`, `server/`, `common/`)
     - GCC C++ Linker → Libraries → Add `-pthread`

3. **Build Project**:
   - Project → Build Project (Ctrl+B)
   - Executable will be generated in Debug/Release folder

## How to Run

1. **Start Server**:
   - Run the application
   - Choose option 1 (Server)
   - Server will start on port 8080

2. **Start Client**:
   - Run the application in another instance
   - Choose option 2 (Client)
   - Enter your username when prompted
   - Start chatting!

## Example Usage

**Server Console:**
Server started on port 8080 with thread pool
Client 127.0.0.1 connected as Alice
Alice (127.0.0.1): Hello everyone!


**Client Console:**
Enter your username: Alice
Connected to server 127.0.0.1:8080 as Alice
Enter message: Hello everyone!
Server response: Alice> Hello everyone!


## Implementation Notes

- Main entry point: `src/ChatApplication.cpp`
- Thread pool size configurable in server constructor
- First client message must be `USERNAME:<username>`
- Eclipse project files (`.project`, `.cproject`) included

## Dependencies

- C++11 compatible compiler
- Eclipse IDE with C/C++ Development Tools (CDT)
- pthread library (automatically linked in Eclipse)
