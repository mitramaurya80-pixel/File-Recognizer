# File Organizer (local workspace)

This repository contains C source files for a small project in `/home/dhanangya/.Project/file organizer`.

Files
- `command_exe.c`
- `recognizer.c`
- `tem.c`

Quick build & run

Change to the project directory (path contains a space, so keep it quoted):

```sh
cd "/home/dhanangya/.Project/file organizer"
```

Compile (recommended flags):

```sh
gcc -Wall -Wextra -Werror -g -o main command_exe.c recognizer.c tem.c
```

Run:

```sh
./main
```

Notes
- `main` program name is used as the output binary in examples. Adjust the source files to include a `main()` if needed.
- This README was generated automatically; tell me if you want a different project description or license.
