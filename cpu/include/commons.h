//
// Created by utnso on 4/21/24.
//

#ifndef CPU_COMMONS_H
#define CPU_COMMONS_H

#include <commons/log.h>
#include <commons/string.h>
#include <commons/config.h>
#include <bits/types.h>

typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;

typedef t_config Config;
typedef t_log Logger;
typedef pthread_t Hilo;

#endif //CPU_COMMONS_H
