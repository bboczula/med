#ifndef C_COMMON_STRUCTURES_H
#define C_COMMON_STRUCTURES_H
struct CCommandMetadata
{
    bool isBeginScopePresent;
    int beginScope;
    bool isEndScopePresent;
    int endScope;
    bool isMnemonicPresent;
    int mnemonic;
};
#endif
