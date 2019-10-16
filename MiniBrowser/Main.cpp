#include "BrowserMain.h"
#include "TestingMain.h"

int main() {
    bool shouldRunTests = false;

    if (shouldRunTests) {
        testingMain();
    } else {
        browserMain();
    }
}
