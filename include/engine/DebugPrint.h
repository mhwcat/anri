#ifndef ANRI_DEBUG_PRINT_H
#define ANRI_DEBUG_PRINT_H

#ifdef ANRI_DEBUG
#define ANRI_DE if(1)
#else
#define ANRI_DE if(0)
#endif

void debugPrint(const char* format, ...);

#endif //ANRI_DEBUGPRINT_H
