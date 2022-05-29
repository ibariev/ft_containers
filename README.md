# ft_containers
Implementation of C++ STL containers
The objective of this project is to implement a few container types of the C++ standard template library. Read **ft_containers.pdf** file to understand the task.

The following containers were implemented:
* **vector**
* **map**
* **stack**
Their code is placed in **containers** folder.
There are also some tests for these containers (see **test** folder). You can produce two binaries that run the same tests: one with my containers
only, and the other one with the STL containers. For example, use the following commands in the root of repository:
```bash
clang++ -Wall -Wextra -Werror -std=c++98 test/myvector.cpp
clang++ -Wall -Wextra -Werror -std=c++98 test/stdvector.cpp
```
Compare outputs and performance / timing.
