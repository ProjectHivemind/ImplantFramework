#ifndef DEBUGGING_H
#define DEBUGGING_H
#include <iostream>
#include <iomanip>

#define LEVEL_INFO 0x01
#define LEVEL_WARN 0x02
#define LEVEL_ERROR 0x04
#define LEVEL_DEBUG 0x08
#define LEVEL_ALL 0xFF

// ONLY EDIT THESE VALUES
/**
 * @brief Mask for what level of debug statements to print
 */
#define DEBUG_MASK LEVEL_ALL
/**
 * @brief Disable or enable debugging all together
 */
#define DEBUGGING true
// ^^^^^^^^^^^^^^^^^^^^^^

#if DEBUGGING
#define PRINT_STATEMENT(level, index, m, loc) loc << std::left << std::setw(10) << __TIME__ << std::setw(7) << level \
                                          << std::setw(40) << file.substr(index) + ":" + __func__ + ": "  \
                                          << m << std::endl;  \

/**
 * @brief Debug statement, first arg is what to print, and second is the level this statement is at.
 */
#define DEBUG(x, level) do {                                \
  if((level) & (DEBUG_MASK)) {                                \
    std::string file = __FILE__;                            \
    size_t index;                                           \
    for (index = file.size(); index > 0; index--)           \
    {                                                       \
      if (file[index - 1] == '\\' || file[index - 1] == '/')\
        break;                                              \
    }                                                       \
    switch(level){                                          \
        case LEVEL_INFO:                                    \
          PRINT_STATEMENT("INFO:", index, x, std::cout)     \
          break;                                            \
        case LEVEL_WARN:                                    \
          PRINT_STATEMENT("WARN:", index, x, std::cout)     \
          break;                                            \
        case LEVEL_ERROR:                                   \
          PRINT_STATEMENT("ERROR:", index, x, std::cout)    \
          break;                                            \
        case LEVEL_DEBUG:                                   \
          PRINT_STATEMENT("DEBUG:", index, x, std::cout)    \
          break;                                            \
    }                                                       \
  }                                                         \
} while (0)
#else
#define DEBUG(x, l) (0)
#endif
#endif
