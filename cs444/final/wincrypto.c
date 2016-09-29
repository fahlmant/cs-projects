#include <wincrypt.h>      // CryptoAPI definitions
#define MS_DEF_PROV       "Microsoft Base Cryptographic Provider v1.0"
#define PROV_RSA_FULL     1
#define CRYPT_NEWKEYSET   0x8

BOOL bResult;
HCRYPTPROC hProv;


bResult = CryptAcquireContext(
            &hProv,            // Variable to hold returned handle.
            NULL,              
            MS_DEF_PROV,       //Using the built in CSP   
            PROV_RSA_FULL,     //Using RSA
            CRYPT_NEWKEYSET);  //The documentation says this will initialize the database               

//Once the handle is acquired, do the work here

// Release handle once we're done with it
CryptReleaseContext(hProv);
