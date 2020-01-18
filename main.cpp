#include <iostream>
#include "Boot.h"

using namespace std;

int main(int argc, char* argv[]) {
    int port = stoi(argv[1]);
    auto* m = new boot::Main();
    m->main(port);
    return 0;
}
