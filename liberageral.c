#include <sys/stat.h>

int
main( int argc, char const *argv[])
{
    if (argc == 2) {
        chmod( argv[1], 0777);
        return 0;
    }

    return 1;
}
