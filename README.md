![](img/logo_128.png)
# clam
The MeetiX shell.

# Build, install & run
To build the project use this command:
```
make build
```

To install the binaries use this command (NOT AVAILABLE YET):
```
make install
```

To run the program just run it through your shell.

# Dependencies
This program has no external dependencies, which means that it just relies on the C standard library. However, to fully work it needs some OS-dependent functions, which means that during the compilation time it will download the necessary libraries and link them.

# Roadmap
 - [x] input parsing (including strings)
 - [x] replacing variable names with their values
 - [x] `echo` builtin command
 - [x] `set` builtin command
 - [x] `exit` builtin command
 - [ ] `pwd` builtin command (needs to be tested)
 - [ ] `cd` builtin command (needs to be tested)
 - [ ] launching programs that are not builtin commands (OS-dependent behaviour)
 - [ ] getting the user which is running the shell (OS-dependent behaviour)
