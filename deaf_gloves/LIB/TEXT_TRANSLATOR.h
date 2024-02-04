#ifndef _TEXT_TRANSLATOR_H_
#define _TEXT_TRANSLATOR_H_
#include "STD_TYPES.h"

struct DictionaryEntry {
    u8 fingerCombination;
    u8* word;
};

u8* lookupWord(u8 fingerState, struct DictionaryEntry* dictionary, u8 dictionarySize);
u8* lookupWord(u8 fingerState, struct DictionaryEntry* dictionary, u8 dictionarySize) {

    for (int i = 0; i < dictionarySize; ++i) {

        if (dictionary[i].fingerCombination == fingerState) {
            return dictionary[i].word;
        }
    }
    return "Unknown"; // Return a default word for unknown combinations
}
#endif
