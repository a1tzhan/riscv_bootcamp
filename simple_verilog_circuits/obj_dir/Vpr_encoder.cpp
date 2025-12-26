// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpr_encoder.h for the primary calling header

#include "Vpr_encoder.h"
#include "Vpr_encoder__Syms.h"

//==========

void Vpr_encoder::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vpr_encoder::eval\n"); );
    Vpr_encoder__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vpr_encoder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("rtl/pr_encoder.v", 1, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vpr_encoder::_eval_initial_loop(Vpr_encoder__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("rtl/pr_encoder.v", 1, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vpr_encoder::_combo__TOP__1(Vpr_encoder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpr_encoder::_combo__TOP__1\n"); );
    Vpr_encoder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->out = (((((((((IData)(vlTOPp->in9) | (IData)(vlTOPp->in8)) 
                         | (IData)(vlTOPp->in7)) | (IData)(vlTOPp->in6)) 
                       | (IData)(vlTOPp->in5)) | (IData)(vlTOPp->in4)) 
                     | (IData)(vlTOPp->in3)) | (IData)(vlTOPp->in2))
                    ? ((IData)(vlTOPp->in9) ? 9U : 
                       ((IData)(vlTOPp->in8) ? 8U : 
                        ((IData)(vlTOPp->in7) ? 7U : 
                         ((IData)(vlTOPp->in6) ? 6U
                           : ((IData)(vlTOPp->in5) ? 5U
                               : ((IData)(vlTOPp->in4)
                                   ? 4U : ((IData)(vlTOPp->in3)
                                            ? 3U : 2U)))))))
                    : ((IData)(vlTOPp->in1) ? 1U : 0U));
}

void Vpr_encoder::_eval(Vpr_encoder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpr_encoder::_eval\n"); );
    Vpr_encoder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

VL_INLINE_OPT QData Vpr_encoder::_change_request(Vpr_encoder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpr_encoder::_change_request\n"); );
    Vpr_encoder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vpr_encoder::_change_request_1(Vpr_encoder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpr_encoder::_change_request_1\n"); );
    Vpr_encoder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vpr_encoder::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpr_encoder::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((in1 & 0xfeU))) {
        Verilated::overWidthError("in1");}
    if (VL_UNLIKELY((in2 & 0xfeU))) {
        Verilated::overWidthError("in2");}
    if (VL_UNLIKELY((in3 & 0xfeU))) {
        Verilated::overWidthError("in3");}
    if (VL_UNLIKELY((in4 & 0xfeU))) {
        Verilated::overWidthError("in4");}
    if (VL_UNLIKELY((in5 & 0xfeU))) {
        Verilated::overWidthError("in5");}
    if (VL_UNLIKELY((in6 & 0xfeU))) {
        Verilated::overWidthError("in6");}
    if (VL_UNLIKELY((in7 & 0xfeU))) {
        Verilated::overWidthError("in7");}
    if (VL_UNLIKELY((in8 & 0xfeU))) {
        Verilated::overWidthError("in8");}
    if (VL_UNLIKELY((in9 & 0xfeU))) {
        Verilated::overWidthError("in9");}
}
#endif  // VL_DEBUG
