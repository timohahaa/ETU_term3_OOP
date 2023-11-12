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

extern const QChar separator;

#endif // COMMON_H
