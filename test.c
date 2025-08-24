#include <windows.h>
#include <bcrypt.h>
#include <stdio.h>

int main() {
    UCHAR buffer[16];
    NTSTATUS status = BCryptGenRandom(NULL, buffer, sizeof(buffer), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    if (status != 0) {
        printf("BCryptGenRandom failed: 0x%08X\n", status);
        return 1;
    }

    printf("Random bytes: ");
    for (int i = 0; i < sizeof(buffer); i++) {
        printf("%02X ", buffer[i]);
    }
    printf("\n");

    return 0;
}