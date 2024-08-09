## C++ Implementation of TCP Redis Server
This is an implementation of a simple version of Redis in-memory database using C++. It serves Redis via TCP socket to accept connections on the custom Redis port 6379. 
The server parses RESP formatted input and aims to support plain in-memory operations:
  - [X] PING
  - [X] SET 
  - [X] GET
  - [X] HSET
  - [X] HGET
  - [X] DEL
  - [X] HDEL

### Requirements and Running the Code:
The code is compiled using clang and current flags require C++ STD=17 standard. A Makefile has been provided to ease compilation. 
Generate local `bin` and `build` folders under the top level directory if missing. These are used from the Makefile to hold binaries and executables.
  - Use `make clean` to remove all compile binaries and executable so that the next compilation is done from scratch
  - Compile the code using `make all`. This dumps object files under `./build` and executables under `./bin`
  - Run the code using `make run`. This targets the executable under `./bin`

### Testing the server

You can either use the `redis-cli` to send commands to the C++ TCP server or the provided Python file. If you use the Python file, ensure the commands are formatted using the RESP serialization protocol. A few example strings have been provided for your reference in `test.py`.

- If you choose to use the `test.py` script, run the script by typing `python3 test.py` and then enter RESP-compliant commands:
  - For example, to send: `set name denis`, type `*3\r\n$3\r\nset\r\n$4\r\nname\r\n$5\r\ndenis\r\n`.
  
- If you choose to use `redis-cli`, first install it for your OS. Then launch the CLI from a shell by typing `redis-cli`. You can then type in commands like so:
  - Example set command to set key `name` with value `denis`: `set name denis`.
