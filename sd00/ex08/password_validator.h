#ifndef PASSWORD_VALIDATOR_H
#define PASSWORD_VALIDATOR_H

typedef enum {
    VALID,
    INVALID_WEAK,
    INVALID_SIMILAR
}   PwStatus;

typedef struct s_pwd {
    char            s[64];
}   PasswordHistory;

PwStatus password_distance(const char *new_pw, const char *curr_pw);

PwStatus validate_password(const char *new_pw, PasswordHistory *history);

#endif