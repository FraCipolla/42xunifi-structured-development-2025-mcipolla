#include "password_validator.h"

#include <string.h>
#include <stddef.h>

static int min(int x, int y, int z)
{
    if (x < y && x < z)
        return x;
    else if (y < x && y < z)
        return y;
    else
        return z;
}

static int minDis(const char* s1, char* s2, int n, int m)
{
    int dp[n + 1][m + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0) {
                dp[i][j] = j;
            }
            else if (j == 0) {
                dp[i][j] = i;
            }
            else if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = 1
                           + min(dp[i - 1][j], dp[i][j - 1],
                                 dp[i - 1][j - 1]);
            }
        }
    }
    return dp[n][m];
}

/*
 * using a bit flag to determine if all conditions are met
 * status = 00000000
 * status |= 0x01 == 00000000 | 00000001
 * status |= 0x02 == 00000000 | 00000010
 * status |= 0x04 == 00000000 | 00000100
 * status |= 0x08 == 00000000 | 00001000
 * status |= 0x10 == 00000000 | 00010000 hexadecimal 10 is 16
 * status == 0x1F == 00000000 | 00011111 all flags set => valid
 * perform a simple recursive edit distance calculation on last 3 passwords
*/

static size_t ft_strlen(const char *s) {
    char *cpy = (char *)s;
    while (*cpy) cpy++;
    return cpy - s;
}

PwStatus validate_password(const char *new_pw, PasswordHistory *history) {
    char flag = 0;
    int i = 0;
    while (new_pw[i]) {
        if (i >= 8 && flag == 0xF) {
            int i = 0;
            while (i < 3) {
                int distance = minDis(new_pw, history[i].s, ft_strlen(new_pw), ft_strlen(history[i].s));
                if (distance == 0) {
                    return INVALID_WEAK;
                } else if (distance == 1) {
                    return INVALID_SIMILAR;
                }
                i++;
            }
            strncpy(history[0].s, history[1].s, ft_strlen(history[1].s));
            strncpy(history[1].s, history[2].s, ft_strlen(history[2].s));
            strncpy(history[2].s, new_pw, ft_strlen(new_pw));
            return VALID;
        }
        if (!(flag & 0x01) && new_pw[i] >= 'a' && new_pw[i] <= 'z') {
            flag |= 0x01;
        } else if (!(flag & 0x02) && new_pw[i] >= 'A' && new_pw[i] <= 'Z') {
            flag |= 0x02;
        } else if (!(flag & 0x04) && new_pw[i] >= '0' && new_pw[i] <= '9') {
            flag |= 0x04;
        } else if (!(flag & 0x08) && new_pw[i] == '@' || new_pw[i] == '#' || new_pw[i] == '$'
        || new_pw[i] == '%' || new_pw[i] == '^' || new_pw[i] == '&' || new_pw[i] == '*') {
            flag |= 0x08;
        }
        i++;
    }
    return (INVALID_WEAK);
}


#if TEST
#include <stdio.h>
int main(void) {
    PasswordHistory history[3];
    strncpy(history[0].s, "#Mcipolasdla123", ft_strlen("#Mcipolasdla123") + 1);
    strncpy(history[1].s, "$Mcgijsnao6940", ft_strlen("$Mcgijsnao6940") + 1);
    strncpy(history[2].s, "#Mcipolla123", ft_strlen("#Mcipolla123") + 1);
    
    const char *new_pwd = "#Mcipasdolla124";

    PwStatus status = validate_password(new_pwd, history);
    printf("%s\n", status == VALID ? "valid" : status == INVALID_SIMILAR ? "invalid similar" : "invalid weak");
}
#endif