#include "password_validator.h"

/*
•At least 8 characters long
•At least one uppercase letter
•At least one lowercase letter
•At least one digit
•At least one special character (@#$%ˆ&*)
•Must differ from current password
*/


/*
 * using a bit flag to determine if all conditions are met
 * status = 00000000
 * status |= 0x01 == 00000000 | 00000001
 * status |= 0x02 == 00000000 | 00000010
 * status |= 0x04 == 00000000 | 00000100
 * status |= 0x08 == 00000000 | 00001000
 * status |= 0x10 == 00000000 | 00010000 hexadecimal 10 is 16
 * status == 0x1F == 00000000 | 00011111 all flags set => valid
*/
PwStatus validate_password(const char *new_pw, const char *curr_pw) {
    char status = 0;
    int i = 0;
    while (new_pw[i]) {
        if (i >= 8 && status == 0x1F) {
            return VALID;
        }
        if (!(status & 0x01) && new_pw[i] >= 'a' && new_pw[i] <= 'z') {
            status |= 0x01;
        } else if (!(status & 0x02) && new_pw[i] >= 'A' && new_pw[i] <= 'Z') {
            status |= 0x02;
        } else if (!(status & 0x04) && new_pw[i] >= '0' && new_pw[i] <= '9') {
            status |= 0x04;
        } else if (!(status & 0x08) && new_pw[i] == '@' || new_pw[i] == '#' || new_pw[i] == '$'
        || new_pw[i] == '%' || new_pw[i] == '^' || new_pw[i] == '&' || new_pw[i] == '*') {
            status |= 0x08;
        }
        if (!(status & 0x10) && curr_pw[i] && new_pw[i] != curr_pw[i]) {
            status |= 0x10;
        }
        i++;
    }
    return (INVALID);
}

#if TEST
#include <stdio.h>
int main(void) {
    const char *pwd = "#Mcipolla123";
    const char *new_pwd = "#Mcipplla123";

    printf("%s\n", validate_password(new_pwd, pwd) == VALID ? "valid" : "not valid");
}
#endif