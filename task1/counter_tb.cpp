#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env) {
    int i; // Count number of clock cycle
    int clk; // module clock signal

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vcounter* top = new Vcounter; // instantiate counter module as Vcounter (DUT)
    // init trace dump
    Verilated::traceEverOn(true); // turn on signal tracing and tell Verilator to dump waveform data to counter.vcd
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");

    // initialize simulation inputs (top = top-level entity, only top-level signals are visible)
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    // run simulation for many clock cycles
    for (i=0; i<300; i++){

        // dump variables into VCD file and toggle clock
        for (clk=0; clk<2; clk++){
            tfp->dump (2*i+clk);       // unit is in ps
            top->clk = !top->clk;
            top->eval ();
        }
        top->rst = (i<2) | (i == 20);
        top->en = (i>4) && (i<=13 | i>=17);
        if (Verilated::gotFinish()) exit(0);
    }

    tfp->close();
    exit(0);
}
