// Include the header file to get access to the MicroPython API
#include "py/dynruntime.h"

// Helper function to compute velocidad
STATIC mp_int_t velocidad_helper(mp_int_t x) {
    mp_int_t duty_cycle = (x - 0) * (100 - 0) / (255 - 0) + 0;
    return 29400 * ((float)duty_cycle / 100);
}

// This is the function which will be called from Python, as getrpm(x)
STATIC mp_obj_t getrpm(mp_obj_t x_obj) {
    // Extract the integer from the MicroPython input object
    mp_int_t dutycycle = mp_obj_get_int(x_obj);
    // Calculate the velocity
    mp_int_t result = velocidad_helper(dutycycle);
    // Convert the result to a MicroPython integer object and return it
    return mp_obj_new_int(result);
}
// Define a Python reference to the function above
STATIC MP_DEFINE_CONST_FUN_OBJ_1(getrpm_obj, getrpm);

// This is the entry point and is called when the module is imported
mp_obj_t mpy_init(mp_obj_fun_bc_t *self, size_t n_args, size_t n_kw, mp_obj_t *args) {
    // This must be first, it sets up the globals dict and other things
    MP_DYNRUNTIME_INIT_ENTRY

    // Make the function available in the module's namespace
    mp_store_global(MP_QSTR_getrpm, MP_OBJ_FROM_PTR(&getrpm_obj));

    // This must be last, it restores the globals dict
    MP_DYNRUNTIME_INIT_EXIT
}