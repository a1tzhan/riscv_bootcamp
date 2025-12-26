// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vp_encoder.h for the primary calling header

#include "Vp_encoder.h"
#include "Vp_encoder__Syms.h"

//==========

VL_CTOR_IMP(Vp_encoder) {
    Vp_encoder__Syms* __restrict vlSymsp = __VlSymsp = new Vp_encoder__Syms(this, name());
    Vp_encoder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vp_encoder::__Vconfigure(Vp_encoder__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

Vp_encoder::~Vp_encoder() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vp_encoder::_eval_initial(Vp_encoder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vp_encoder::_eval_initial\n"); );
    Vp_encoder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vp_encoder::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vp_encoder::final\n"); );
    // Variables
    Vp_encoder__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vp_encoder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vp_encoder::_eval_settle(Vp_encoder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vp_encoder::_eval_settle\n"); );
    Vp_encoder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vp_encoder::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vp_encoder::_ctor_var_reset\n"); );
    // Body
    in1 = VL_RAND_RESET_I(1);
    in2 = VL_RAND_RESET_I(1);
    in3 = VL_RAND_RESET_I(1);
    in4 = VL_RAND_RESET_I(1);
    in5 = VL_RAND_RESET_I(1);
    in6 = VL_RAND_RESET_I(1);
    in7 = VL_RAND_RESET_I(1);
    in8 = VL_RAND_RESET_I(1);
    in9 = VL_RAND_RESET_I(1);
    out = VL_RAND_RESET_I(4);
}
