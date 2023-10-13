#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i; // Count number of clock cycle
    int clk; // module clock signal

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vtop* top = new Vtop;
    // init trace dump
    Verilated::traceEverOn(true); // turn on signal tracing and tell Verilator to dump waveform data to counter.vcd
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");

    // init Vbuddy
    if (vbdOpen() != 1) return(-1);
    vbdHeader("Lab 1: Counter");
    vbdSetMode(1);

    // initialize simulation inputs (top = top-level entity, only top-level signals are visible)
    top->clk = 1;
    top->rst = 1;
    top->en = 0;
    top->v = vbdValue();

    // run simulation for many clock cycles
    for (i=0; i<1000; i++){

        // dump variables into VCD file and toggle clock
        for (clk=0; clk<2; clk++){
            tfp->dump (2*i+clk);       // unit is in ps
            top->clk = !top->clk;
            top->eval ();
        }

        // ++++ Send count value to Vbuddy
        vbdHex(4, (int(top->bcd) >> 8) & 0xF);
        vbdHex(3, (int(top->bcd) >> 4) & 0xF);
        vbdHex(2, int(top->bcd) & 0xF);

        vbdCycle(i+1);
        // vbdPlot(int(top->count), 0, 255);
        // ---- end of Vbuddy output section

        top->rst = (i<2);
        // top->en = (i>4) && (i<=13 | i>=17);
        top->en = vbdFlag();
        top->v = vbdValue();

        if (Verilated::gotFinish()) exit(0);
    }

    vbdClose();     // ++++
    tfp->close();
    exit(0);
}
