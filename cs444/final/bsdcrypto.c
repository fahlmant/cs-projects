#include <opencrypto/cryptodev.h>

    //DRIVER SIDE SETUP
    //Recieves a device id
    device_id = crypto_get_driverid(0)
    //Registers a crypto algorithm
    data_value = crypto_register(device_id, ALG_ID, MAX_OPERATOR_BITS, ALG_FLAGS)


    //Begins a new sessions with the algorithm and the device
    session_id = newsession(data_value, device_id)

    //Handle work in here
    
    //Ends session thats refered to by session_id
    freesession(data_value, session_id)

    //Unregister support for an algroithm
    crypto_unregister(device_id, ALG_ID)
