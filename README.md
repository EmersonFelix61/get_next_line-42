*This project has been created as part of the 42 curriculum by emda-sil.*

# get_next_line

## Description

`get_next_line` is a C function that reads and returns one line at a time from a file descriptor.


Repeated calls to `get_next_line(fd)` allow a file, standard input, or another valid file descriptor to be read progressively without loading the entire content at once.

The function returns:

- the next line read from the file descriptor;
- `NULL` when there is nothing else to read;
- `NULL` if an error occurs.

When a line ends with a newline character, the returned string includes the `\n`. If the file ends without a final newline, the last returned line does not include one.

## Function Prototype

```c
char	*get_next_line(int fd);
```

## Compilation

The project can be compiled by defining `BUFFER_SIZE` during compilation:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
	get_next_line.c get_next_line_utils.c main.c
```

Example using the bonus files:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
	get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

`BUFFER_SIZE` defines how many bytes are read at each call to `read`.

If `BUFFER_SIZE` is not defined during compilation, the header defines a default value:

```c
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
```

The function should also be tested with different buffer sizes, for example:

```bash
-D BUFFER_SIZE=1
-D BUFFER_SIZE=42
-D BUFFER_SIZE=9999
```

## Usage Example

A simple test program can be written like this:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

Compile it with:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
	get_next_line.c get_next_line_utils.c main.c
```

Then run:

```bash
./a.out
```

## Algorithm Explanation

The implementation is based on a persistent storage strategy using a `static` variable called `stash`.

A normal local variable disappears when a function returns. A static variable keeps its value between function calls, which makes it useful for storing content that was read but not returned yet.

The algorithm is divided into three main steps:

### 1. Read into the stash

The function reads from the file descriptor into a temporary buffer of size `BUFFER_SIZE`.

The content read from the file descriptor is joined to the current stash. This continues until either:

- a newline character is found in the stash;
- `read` reaches the end of the file;
- `read` returns an error.

This avoids reading the whole file at once. The function reads only as much as needed to return the next line.

### 2. Extract the next line

After the stash contains either a full line or the final part of the file, the function creates a new allocated string containing the next line.

If a newline character is found, the returned line includes it.

If no newline character is found, the returned line contains everything left in the stash.

### 3. Clean the stash

After extracting the line, the stash is updated.

If there is content after the newline, that remaining content is duplicated into a new stash and saved for the next call.

If there is nothing left after the newline, the stash is freed and reset to `NULL`.

This prevents already returned content from being returned again and keeps only the unread remainder.

## Mandatory Technical Choices

### Single static stash

The mandatory version uses:

```c
static char	*stash;
```

This is enough for reading from one file descriptor at a time.

## Bonus Explanation

The bonus version supports multiple file descriptors at the same time.

Instead of a single pointer, it uses:

```c
static char	*stash[1024];
```

Each file descriptor has its own stash:

```c
stash[fd]
```

This allows calls such as:

```c
get_next_line(fd1);
get_next_line(fd2);
get_next_line(fd1);
get_next_line(fd3);
```

without mixing the unread content from different file descriptors.

The core algorithm remains the same as the mandatory version:

1. read into the stash for the current file descriptor;
2. extract one line;
3. clean only the stash related to that file descriptor.

## Resources

Classic references used or useful for this project:

- `man 2 read`
- `man 3 malloc`
- `man 3 free`
- `man 3 open`
- 42 subject: Get Next Line
- C documentation about file descriptors
- C documentation about static variables
- C documentation about dynamic memory allocation
- Book: "Linguagem C", Luis Damas

## AI Usage

AI was used as a learning and review assistant, not as a blind replacement for personal reasoning.

It was used for:

- clarifying the expected behavior from the subject;
- discussing edge cases;
- reviewing the algorithm structure;
- helping explain the role of the static stash;
