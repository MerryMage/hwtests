#include <3ds.h>

#include "output.h"
#include "tests/test.h"
#include "tests/fs/fs.h"
#include "tests/cpu/cputests.h"
#include "tests/kernel/kernel.h"
#include "tests/gpu/gpu.h"

int main(int argc, char** argv)
{

    gfxInitDefault();
    InitOutput();

    consoleClear();

    Print("Press A to begin...\n");

    // unsigned int test_counter = 0; // Moving it here causes this app to refuse to boot at all.

    while (aptMainLoop()) {
        gfxFlushBuffers();
        gfxSwapBuffers();

        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) {
            break;
        } else if (kDown & KEY_A) {
            consoleClear();

            unsigned int test_counter = 0; // This configuration works, but obviously only test 0 would run.

            TestCaller tests[] = {
                FS::TestAll,
                CPU::Integer::TestAll,
                CPU::Memory::TestAll,
                Kernel::TestAll,
                GPU::TestAll
            };

            if (test_counter < (sizeof(tests) / sizeof(tests[0]))) {
                tests[test_counter]();
                test_counter++;
            } else {
                break;
            }

            Log("\n");
            Print("Press A to continue...\n");
        }

        gspWaitForVBlank();
    }

    consoleClear();

    gfxExit();
    DeinitOutput();

    return 0;
}
