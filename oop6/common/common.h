#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum message {
    DETERMINAND_REQ = 1,
    RANK_REQ,
    TRANSPOSE_REQ,
    DETERMINAND_RESP,
    RANK_RESP,
    TRANSPOSE_RESP,
};

enum type {
    TYPE_FLOAT = 1,
    TYPE_COMPLEX,
    TYPE_RATIONAL,
};

extern const QChar separator;

#endif // COMMON_H
