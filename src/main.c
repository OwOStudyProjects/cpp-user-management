#include <stdio.h>
#include "user.h"
#include "file_io.h"
#include "menu.h"

int main() {
    load_users();
    show_menu();
    return 0;
}
